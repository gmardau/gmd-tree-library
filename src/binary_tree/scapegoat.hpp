// gmd-tree-library - C++ - Scapegoat tree

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

#ifndef _GMD_BINARY_TREE_SCAPEGOAT_
#define _GMD_BINARY_TREE_SCAPEGOAT_

template <typename Key, typename Value, typename Info, bool SetMap, bool Threaded>
struct binary_tree_node<tree_scapegoat, Key, Value, Info, SetMap, Threaded>
: public binary_tree_node_base<binary_tree_node<tree_scapegoat, Key, Value, Info, SetMap, Threaded>,
                               Key, Value, Info, SetMap, Threaded>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <typename, typename, typename, typename, bool> friend struct binary_tree_node_superbase;
	template <binary_tree_type, typename, typename, typename, bool, bool> friend struct binary_tree_node;
	template <bool, typename, bool> friend struct binary_tree_traversor;
	friend struct binary_tree_iteration;

	private:
	using _Node  = binary_tree_node<tree_scapegoat, Key, Value, Info, SetMap, Threaded>;
	using _Base  = binary_tree_node_base<_Node, Key, Value, Info, SetMap, Threaded>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr binary_tree_type _Tree = tree_scapegoat;
	static constexpr bool _SetMap = SetMap, _Threaded = Threaded;

	/* === Variables === */
	private:
	::__gnu_cxx::__aligned_membuf<Info> _info;
	/* === Variables === */

	/* === Constructor & Destructor === */
	private:
	binary_tree_node (_Base *up) : _Base(up) {}
	template <bool _ = Threaded, typename = ::std::enable_if_t<_>>
	binary_tree_node (_Base *up, _Base *prev, _Base *next) : _Base(up, prev, next) {}
	template <typename Node_Other>
	binary_tree_node (_Base *up, Node_Other *) : _Base(up) {}
	/* === Constructor & Destructor === */

	/* === Reset === */
	private:
	inline void reset () {}
	/* === Reset === */

	/* === Print === */
	private:
	inline void print () const {}
	/* === Print === */
};

template <typename Node, bool Multi, typename Comparator, typename Allocator>
struct binary_tree_subbase<tree_scapegoat, Node, Multi, Comparator, Allocator>
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


	/* === Variables === */
	private:
	constexpr static double _factor = 0.575, _factor_opt = 1 / ::std::log(1 / _factor);
	size_t _max_size = 0;
	/* === Variables === */


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


	/* === Copy (override) === */
	public:
	binary_tree_subbase (const binary_tree_subbase &other)
		: _Base(other),       _max_size(other._max_size) {}
	binary_tree_subbase (const binary_tree_subbase &other, const Comparator &c)
		: _Base(other, c),    _max_size(other._max_size) {}
	binary_tree_subbase (const binary_tree_subbase &other,                      const Allocator &a)
		: _Base(other,    a), _max_size(other._max_size) {}
	binary_tree_subbase (const binary_tree_subbase &other, const Comparator &c, const Allocator &a)
		: _Base(other, c, a), _max_size(other._max_size) {}
	/* === Copy (override) === */


	/* === Move (override) === */
	public:
	binary_tree_subbase (binary_tree_subbase &&other)
		: _Base(::std::move(other)),       _max_size(other._max_size) { other._max_size = 0; }
	binary_tree_subbase (binary_tree_subbase &&other, const Comparator &c)
		: _Base(::std::move(other), c),    _max_size(other._max_size) { other._max_size = 0; }
	binary_tree_subbase (binary_tree_subbase &&other,                      const Allocator &a)
		: _Base(::std::move(other),    a), _max_size(other._max_size) { other._max_size = 0; }
	binary_tree_subbase (binary_tree_subbase &&other, const Comparator &c, const Allocator &a)
		: _Base(::std::move(other), c, a), _max_size(other._max_size) { other._max_size = 0; }
	/* === Move (override) === */


	/* === Initializer List === */
	public:
	binary_tree_subbase (const ::std::initializer_list<typename Node::_Info> &il, const Comparator &c = Comparator(),
					     const Allocator &a = Allocator()) : _Base(c, a) { _Base::insert(il); }

	binary_tree_subbase (const ::std::initializer_list<typename Node::_Info> &il,
					     const Allocator &a)               : _Base(   a) { _Base::insert(il); }
	/* === Initializer List === */
	/* ##################### Constructor & Destructor ###################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* #################### Assign operator (override) ##################### */
	/* === Copy === */
	public:
	binary_tree_subbase &operator= (const binary_tree_subbase &other) = default;
	template <binary_tree_type Tree_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, binary_tree_subbase &>
	operator= (const binary_tree_subbase<Tree_Other, Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ _Base::operator=(other); _max_size = other._max_size; return *this; }
	/* === Copy === */


	/* === Move === */
	binary_tree_subbase &operator= (binary_tree_subbase &&other)
	{ _Base::operator=(::std::move(other)); _max_size = other._max_size; other._max_size = 0; return *this; }
	template <binary_tree_type Tree_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, binary_tree_subbase &>
	operator= (binary_tree_subbase<Tree_Other, Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &&other)
	{ _Base::operator=(::std::move(other)); _max_size = other._max_size; other._max_size = 0; return *this; }
	/* === Move === */
	/* #################### Assign operator (override) ##################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################# Modifiers ############################# */
	/* === Insert === */
	private:
	template <typename Arg>
	::std::pair<_Node *, bool>
	_insert_ (Arg &&info)
	{
		int side = 0; size_t depth, size;
		_Node *node = _place(side, _Node::key(::std::forward<Arg>(info)), depth);
		if(!Multi && side == -1) { if(_Base::_size > _max_size) _max_size = _Base::_size; return {node, false}; }
		node = _Base::_insert_place_bottom(side, node, ::std::forward<Arg>(info));
		if(depth > (::std::log(_Base::_size) * _factor_opt) + 1) {
			_Node *scapegoat = _scapegoat(node, size); _rebalance(scapegoat, size); }
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
		int side = 0; size_t depth, size;
		_Node *place = _place(side, **node, depth);
		if(!Multi && side == -1) { if(_Base::_size > _max_size) _max_size = _Base::_size; return {place, false}; }
		_Base::_emplace_place_bottom(side, place, node);
		if(depth > (::std::log(_Base::_size) * _factor_opt) + 1) {
			_Node *scapegoat = _scapegoat(node, size); _rebalance(scapegoat, size); }
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
		_Node *replacement;
		if(node->_down[0] == nullptr && node->_down[1] == nullptr) {
			_Base::_remove_leaf(node, del); }
		else {
			if(node->_down[0] != nullptr) {
				replacement = _Iteration::_<0>(node);
				_Base::_cut_node(replacement, replacement->_down[0]); }
			else {
				replacement = _Iteration::_<1>(node);
				_Base::_cut_node(replacement, replacement->_down[1]); }
			_Base::_replace_node(node, replacement, del); }
		if(_Base::_size > 0 && _Base::_size <= _max_size * _factor)
			_rebalance(_Base::_head._up, _Base::_size);
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
		if(_Base::_head._up == nullptr) { side = 0; depth = 1; return &(_Base::_head); }
		_Node *node = _Base::_head._up, *save = nullptr;
		for(depth = 2; ; ++depth) {
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
		if(_Base::_head._up == nullptr) { side = 0; depth = 1; return &(_Base::_head); }
		depth = 2;
		for(_Node *node = _Base::_head._up; ; ++depth) {
			side = !_Base::_comparator(key, **node);
			if(side) { if(node->_down[1]) node = node->_down[1]; else return node; }
			else     { if(node->_down[0]) node = node->_down[0]; else return node; } }
	}
	/* === Place === */


	/* === Scapegoat === */
	private:
	_Node *
	_scapegoat (_Node *node, size_t &size)
	{
		size_t node_size = 1;
		for(_Node *parent = node->_up; ; node = parent, parent = node->_up, node_size = size) {
			size = node_size + _calc_size(parent->_down[node == parent->_down[0]]) + 1;
			if(node_size > size * _factor) return parent;
		}
	}
	/* === Scapegoat === */


	/* === Rebalance === */
	private:
	void
	_rebalance (_Node *node, size_t size)
	{
		size_t position = 0;
		_Node **nodes = (_Node **) ::std::malloc(size * sizeof(_Node *));
		_flatten(nodes, position, node);
		if(node->_up == &(_Base::_head))  _Base::_head._up = _rebuild(nodes, 0, size-1, &(_Base::_head));
		else node->_up->_down[node == node->_up->_down[1]] = _rebuild(nodes, 0, size-1, node->_up);
		::std::free(nodes);
		_max_size = _Base::_size;
	}

	private:
	void
	_flatten (_Node **nodes, size_t &position, _Node *node)
	{
		if(node->_down[0] != nullptr) _flatten(nodes, position, node->_down[0]);
		nodes[position] = node; ++position;
		if(node->_down[1] != nullptr) _flatten(nodes, position, node->_down[1]);
	}

	private:
	_Node *
	_rebuild (_Node **nodes, size_t p1, size_t p2, _Node *parent)
	{
		size_t p = (p1 + p2) / 2;
		nodes[p]->_up = parent;
		nodes[p]->_down[0] = p != p1 ? _rebuild(nodes, p1, p-1, nodes[p]) : nullptr;
		nodes[p]->_down[1] = p != p2 ? _rebuild(nodes, p+1, p2, nodes[p]) : nullptr;
		return nodes[p];
	}
	/* === Rebalance === */


	/* === Size === */
	private:
	size_t
	_calc_size (_Node *node)
	{ if(node == nullptr) return 0; return _calc_size(node->_down[0]) + _calc_size(node->_down[1]) + 1; }
	/* === Size === */
};

#endif
