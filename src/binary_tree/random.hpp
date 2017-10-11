// gmd-tree-library - C++ - Random tree

// Copyright (C) 2017 Gustavo Martins

// This file is part of the gmd-tree-library. This library is free
// software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this library.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _GMD_BINARY_TREE_RANDOM_
#define _GMD_BINARY_TREE_RANDOM_

template <typename Key, typename Value, typename Info, bool SetMap, bool Threaded>
struct binary_tree_node<tree_random, Key, Value, Info, SetMap, Threaded>
: public binary_tree_node_base<binary_tree_node<tree_random, Key, Value, Info, SetMap, Threaded>,
                               Key, Value, Info, SetMap, Threaded>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <typename, typename, typename, typename, bool> friend struct binary_tree_node_superbase;
	template <binary_tree_type, typename, typename, typename, bool, bool> friend struct binary_tree_node;
	template <bool, typename, bool> friend struct binary_tree_traversor;
	friend struct binary_tree_iteration;

	private:
	using _Node  = binary_tree_node<tree_random, Key, Value, Info, SetMap, Threaded>;
	using _Base  = binary_tree_node_base<_Node, Key, Value, Info, SetMap, Threaded>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr binary_tree_type _Tree = tree_random;
	static constexpr bool _SetMap = SetMap, _Threaded = Threaded;

	/* === Variables === */
	private:
	::__gnu_cxx::__aligned_membuf<Info> _info;
	size_t _size = 1;
	/* === Variables === */

	/* === Constructor & Destructor === */
	private:
	binary_tree_node (_Base *up) : _Base(up) {}
	template <bool _ = Threaded, typename = ::std::enable_if_t<_>>
	binary_tree_node (_Base *up, _Base *prev, _Base *next) : _Base(up, prev, next) {}
	template <typename Node_Other, typename =::std::enable_if_t<_Tree == Node_Other::_Tree>>
	binary_tree_node (_Base *up, Node_Other *other) : _Base(up), _size(other->_size) {}
	template <typename Node_Other, typename =::std::enable_if_t<_Tree != Node_Other::_Tree>, typename = void>
	binary_tree_node (_Base *up, Node_Other *) : _Base(up) {}
	/* === Constructor & Destructor === */

	/* === Reset === */
	private:
	inline void reset () { _size = 1; }
	/* === Reset === */

	/* === Print === */
	private:
	inline void print () const { printf("\x1B[37m%lu\x1B[0m ", _size); }
	/* === Print === */
};

template <typename Node, bool Multi, typename Comparator, typename Allocator>
struct binary_tree_subbase<tree_random, Node, Multi, Comparator, Allocator>
: public binary_tree_base<Node, Multi, Comparator, Allocator>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;

	private:
	using _Node      = typename Node::_Base;
	using _Base      = binary_tree_base<Node, Multi, Comparator, Allocator>;
	using _Iteration = binary_tree_iteration;

	public:
	using _Base::_Base;
	using _Base::operator=;


	/* ##################################################################### */
	/* ##################### Constructor & Destructor ###################### */
	/* === Range === */
	public:
	template <typename T1, typename T2>
	binary_tree_subbase (const T1 &first, const T2 &last, const Comparator &c = Comparator(), const Allocator &a = Allocator())
		: _Base(c, a) { _Base::insert(first, last); }

	template <typename T1, typename T2>
	binary_tree_subbase (const T1 &first, const T2 &last,                                     const Allocator &a)
		: _Base(   a) { _Base::insert(first, last); }
	/* === Range === */


	/* === Initializer List === */
	public:
	binary_tree_subbase (const ::std::initializer_list<typename Node::_Info> &il, const Comparator &c = Comparator(),
					     const Allocator &a = Allocator()) : _Base(c, a) { _Base::insert(il); }

	binary_tree_subbase (const ::std::initializer_list<typename Node::_Info> &il,
					     const Allocator &a)               : _Base(   a) { _Base::insert(il); }
	/* === Initializer List === */
	/* ##################### Constructor & Destructor ###################### */
	/* ##################################################################### */


	/* === Helpers === */
	private:
	static inline size_t &_size (_Node *node) { return node->cast()->_size; }
	/* === Helpers === */


	/* ##################################################################### */
	/* ############################# Modifiers ############################# */
	/* === Insert === */
	private:
	template <typename Arg>
	::std::pair<_Node *, bool>
	_insert_ (Arg &&info)
	{
		int side = 0; size_t depth;
		_Node *node = _place(side, _Node::key(::std::forward<Arg>(info)), depth);
		if(!Multi && side == -1) return {node, false};
		node = _Base::_insert_place_bottom(side, node, ::std::forward<Arg>(info));
		_balance_insert(node, depth);
		return {node, true};
	}

	private:
	template <typename Arg>
	inline ::std::pair<_Node *, bool>
	_insert_hint_ (_Node *, Arg &&info)
	{ return _insert_(::std::forward<Arg>(info)); }
	/* === Insert === */


	/* === Emplace === */
	private:
	::std::pair<_Node *, bool>
	_emplace_ (_Node *node)
	{
		int side = 0; size_t depth;
		_Node *place = _place(side, **node, depth);
		if(!Multi && side == -1) return {place, false};
		_Base::_emplace_place_bottom(side, place, node);
		_balance_insert(node, depth);
		return {node, true};
	}

	private:
	inline ::std::pair<_Node *, bool>
	_emplace_hint_ (_Node *, _Node *node)
	{ return _emplace_(node); }
	/* === Emplace === */


	/* === Erase === */
	private:
	void
	_erase_ (_Node *node, const bool del)
	{
		_balance_erase(node);
		if(_sift_down(node) == 0) _Base::_remove_node(node, node->_down[0], del);
		else                      _Base::_remove_node(node, node->_down[1], del);
	}
	/* === Erase === */
	/* ############################# Modifiers ############################# */
	/* ##################################################################### */


	/* === Place === */
	private:
	template <bool _ = !Multi, typename = ::std::enable_if_t<_>>
	_Node *
	_place (int &side, const typename Node::_Key &key, size_t &depth)
	{
		bool add = 0;
		if(_Base::_head._up == nullptr) { side = 0; depth = 0; return &(_Base::_head); }
		_Node *node = _Base::_head._up, *save = nullptr;
		double rand_number = _uniform_real_distribution(_random_generator);
		for(depth = 0; ; depth += add) {
			if(add == 0 && rand_number * (_size(node) + 1) < 1) { add = 1; depth = 1; }
			side = !_Base::_comparator(key, **node);
			if(side) { save = node; if(node->_down[1]) node = node->_down[1]; else break; }
			else     {              if(node->_down[0]) node = node->_down[0]; else break; } }
		if(save == nullptr) { side = 0; return node; }
		if(_Base::_comparator(**save, key)) return node;
		side = -1; return save;
	}

	private:
	template <bool _ = Multi, typename = ::std::enable_if_t<_>, typename = void>
	_Node *
	_place (int &side, const typename Node::_Key &key, size_t &depth)
	{
		bool add = 0;
		if(_Base::_head._up == nullptr) { side = 0; depth = 0; return &(_Base::_head); }
		double rand_number = _uniform_real_distribution(_random_generator); depth = 0;
		for(_Node *node = _Base::_head._up; ; depth += add) {
			if(add == 0 && rand_number * (_size(node) + 1) < 1) { add = 1; depth = 1; }
			side = !_Base::_comparator(key, **node);
			if(side) { if(node->_down[1]) node = node->_down[1]; else return node; }
			else     { if(node->_down[0]) node = node->_down[0]; else return node; } }
	}
	/* === Place === */


	/* === Balancing === */
	private:
	void
	_balance_insert (_Node *node, size_t depth)
	{
		_Node *parent = node->_up;
		for(size_t i = 0; i < depth; ++i, parent = node->_up) {
			if(node == parent->_down[0]) _Base::_rotate_right(parent, node);
			else                         _Base::_rotate_left (parent, node);
			_update_size(parent); }
		_update_size(node);
		for( ; parent != &(_Base::_head); parent = parent->_up) ++_size(parent);
	}

	private:
	void
	_balance_erase (_Node *node)
	{ for(_Node *parent = node->_up; parent != &(_Base::_head); parent = parent->_up) --_size(parent); }
	/* === Balancing === */


	/* === Sift === */
	private:
	bool
	_sift_down (_Node *node)
	{
		while(node->_down[0] != nullptr) {
			if(node->_down[1] != nullptr) {
				if(_size(node->_down[0]) > _size(node->_down[1])) _Base::_rotate_right(node, node->_down[0]);
				else                                              _Base::_rotate_left (node, node->_down[1]);
				_size(node->_up) = _size(node) - 1; _update_size(node);
			} else return 0; }
		return 1;
	}
	/* === Sift === */


	/* === Size update === */
	private:
	void
	_update_size (_Node *node)
	{
		_size(node) = (node->_down[0] != nullptr ? _size(node->_down[0]) : 0) +
		              (node->_down[1] != nullptr ? _size(node->_down[1]) : 0) + 1;
	}
	/* === Size update === */
};

#endif
