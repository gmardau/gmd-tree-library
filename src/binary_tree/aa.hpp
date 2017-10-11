// gmd-tree-library - C++ - Arne Andersson tree

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

#ifndef _GMD_BINARY_TREE_AA_
#define _GMD_BINARY_TREE_AA_

template <typename Key, typename Value, typename Info, bool SetMap, bool Threaded>
struct binary_tree_node<tree_aa, Key, Value, Info, SetMap, Threaded>
: public binary_tree_node_base<binary_tree_node<tree_aa, Key, Value, Info, SetMap, Threaded>,
                               Key, Value, Info, SetMap, Threaded>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <typename, typename, typename, typename, bool> friend struct binary_tree_node_superbase;
	template <binary_tree_type, typename, typename, typename, bool, bool> friend struct binary_tree_node;
	template <bool, typename, bool> friend struct binary_tree_traversor;
	friend struct binary_tree_iteration;

	private:
	using _Node  = binary_tree_node<tree_aa, Key, Value, Info, SetMap, Threaded>;
	using _Base  = binary_tree_node_base<_Node, Key, Value, Info, SetMap, Threaded>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr binary_tree_type _Tree = tree_aa;
	static constexpr bool _SetMap = SetMap, _Threaded = Threaded;

	/* === Variables === */
	private:
	::__gnu_cxx::__aligned_membuf<Info> _info;
	size_t _level = 0;
	/* === Variables === */

	/* === Constructor & Destructor === */
	private:
	binary_tree_node (_Base *up) : _Base(up) {}
	template <bool _ = Threaded, typename = ::std::enable_if_t<_>>
	binary_tree_node (_Base *up, _Base *prev, _Base *next) : _Base(up, prev, next) {}
	template <typename Node_Other, typename =::std::enable_if_t<_Tree == Node_Other::_Tree>>
	binary_tree_node (_Base *up, Node_Other *other) : _Base(up), _level(other->_level) {}
	template <typename Node_Other, typename =::std::enable_if_t<_Tree != Node_Other::_Tree>, typename = void>
	binary_tree_node (_Base *up, Node_Other *) : _Base(up) {}
	/* === Constructor & Destructor === */

	/* === Reset === */
	private:
	inline void reset () { _level = 0; }
	/* === Reset === */

	/* === Print === */
	private:
	inline void print () const { printf("\x1B[37m%lu\x1B[0m ", _level); }
	/* === Print === */
};

template <typename Node, bool Multi, typename Comparator, typename Allocator>
struct binary_tree_subbase<tree_aa, Node, Multi, Comparator, Allocator>
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
	static inline size_t &_level (_Node *node) { return node->cast()->_level; }
	/* === Helpers === */


	/* ##################################################################### */
	/* ############################# Modifiers ############################# */
	/* === Insert === */
	private:
	template <typename Arg>
	::std::pair<_Node *, bool>
	_insert_ (Arg &&info)
	{
		::std::pair<_Node *, bool> result = _Base::_insert_bottom(::std::forward<Arg>(info));
		if(result.second) _balance_insert(result.first);
		return result;
	}

	private:
	template <typename Arg>
	::std::pair<_Node *, bool>
	_insert_hint_ (_Node *hint, Arg &&info)
	{
		::std::pair<_Node *, bool> result = _Base::_insert_hint_bottom(hint, ::std::forward<Arg>(info));
		if(result.second) _balance_insert(result.first);
		return result;
	}
	/* === Insert === */


	/* === Emplace === */
	private:
	::std::pair<_Node *, bool>
	_emplace_ (_Node *node)
	{
		::std::pair<_Node *, bool> result = _Base::_emplace_bottom(node);
		if(result.second) _balance_insert(result.first);
		return result;
	}

	private:
	::std::pair<_Node *, bool>
	_emplace_hint_ (_Node *hint, _Node *node)
	{
		::std::pair<_Node *, bool> result = _Base::_emplace_hint_bottom(hint, node);
		if(result.second) _balance_insert(result.first);
		return result;
	}
	/* === Emplace === */


	/* === Erase === */
	private:
	void
	_erase_ (_Node *node, const bool del)
	{
		bool side = 0;
		_Node *parent, *replacement;
		if(node->_down[1] == nullptr) {
			parent = node->_up;
			if(parent == &(_Base::_head) || _level(parent) == _level(node)) _Base::_remove_leaf(node, del);
			if(parent != &(_Base::_head)) side = node == parent->_down[1];
			else { _Base::_remove_leaf(node, del); _balance_erase(parent, side); } }
		else {
			replacement = _Iteration::_<1>(node);
			_Base::_cut_node(replacement, replacement->_down[1]);
			if(_level(replacement->_up) == _level(replacement)) {
				_level(replacement) = _level(node);
				_Base::_replace_node(node, replacement, del); }
			else {
				if(node == replacement->_up) { parent = replacement; side ^= 1; }
				else                           parent = replacement->_up;
				_level(replacement) = _level(node);
				_Base::_replace_node(node, replacement, del); _balance_erase(parent, side); } }
	}
	/* === Erase === */
	/* ############################# Modifiers ############################# */
	/* ##################################################################### */


	/* === Balancing === */
	private:
	void
	_balance_insert (_Node *node)
	{
		for(_Node *parent = node->_up; parent != &(_Base::_head); node = parent, parent = node->_up) {
			if(parent->_down[0] == node && _level(node) == _level(parent)) {
				_skew(parent, node); ::std::swap(parent, node); }
			if(parent->_down[1] == node && node->_down[1] != nullptr && _level(parent) == _level(node->_down[1])) {
				_split(parent, node); parent = node; }
		}
	}

	private:
	void
	_balance_erase (_Node *parent, bool side)
	{
		for( ; parent != &(_Base::_head); parent = parent->_up) {
			if((parent->_down[side] == nullptr && _level(parent) > 0) ||
			   (parent->_down[side] != nullptr && _level(parent) - _level(parent->_down[side]) > 1)) {
				if(side == 0 && _level(parent->_down[1]) == _level(parent)) --(parent->_down[1]);
				--_level(parent);
				if(_skew_check(parent)) parent = parent->_up;
				if(parent->_down[1] != nullptr) _skew_check(parent->_down[1]);
				if(parent->_down[1]->_down[1] != nullptr) _skew_check(parent->_down[1]->_down[1]);
				if(_split_check(parent)) parent = parent->_up;
				if(parent->_down[1] != nullptr) _split_check(parent->_down[1]);
			}
			if(parent->_up != nullptr) side = parent == parent->_up->_down[1];
		}
	}
	/* === Balancing === */


	/* === Node rotation === */
	private:
	inline void
	_skew (_Node *parent, _Node *node)
	{ _Base::_rotate_right(parent, node); }

	private:
	bool
	_skew_check (_Node *parent)
	{
		_Node *node = parent->_down[0];
		if(node != nullptr && _level(node) == _level(parent)) { _skew(parent, node); return true; }
		return false;
	}

	private:
	void
	_split (_Node *parent, _Node *node)
	{ _Base::_rotate_left(parent, node); ++_level(node); }

	private:
	bool
	_split_check (_Node *parent)
	{
		_Node *node = parent->_down[1];
		if(node != nullptr && node->_down[1] != nullptr && _level(node->_down[1]) == _level(parent)) {
			_split(parent, node); return true; }
		return false;
	}
	/* === Node rotation === */
};

#endif
