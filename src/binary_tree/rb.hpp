// gmd-tree-library - C++ - Red-Black tree

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

#ifndef _GMD_BINARY_TREE_RB_
#define _GMD_BINARY_TREE_RB_

template <typename Key, typename Value, typename Info, bool SetMap, bool Threaded>
struct binary_tree_node<tree_rb, Key, Value, Info, SetMap, Threaded>
: public binary_tree_node_base<binary_tree_node<tree_rb, Key, Value, Info, SetMap, Threaded>,
                               Key, Value, Info, SetMap, Threaded>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <typename, typename, typename, typename, bool> friend struct binary_tree_node_superbase;
	template <binary_tree_type, typename, typename, typename, bool, bool> friend struct binary_tree_node;
	template <bool, typename, bool> friend struct binary_tree_traversor;
	friend struct binary_tree_iteration;

	private:
	using _Node  = binary_tree_node<tree_rb, Key, Value, Info, SetMap, Threaded>;
	using _Base  = binary_tree_node_base<_Node, Key, Value, Info, SetMap, Threaded>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr binary_tree_type _Tree = tree_rb;
	static constexpr bool _SetMap = SetMap, _Threaded = Threaded;

	/* === Variables === */
	private:
	::__gnu_cxx::__aligned_membuf<Info> _info;
	bool _colour = 1;
	/* === Variables === */

	/* === Constructor & Destructor === */
	private:
	binary_tree_node (_Base *up) : _Base(up) {}
	template <bool _ = Threaded, typename = ::std::enable_if_t<_>>
	binary_tree_node (_Base *up, _Base *prev, _Base *next) : _Base(up, prev, next) {}
	template <typename Node_Other, typename =::std::enable_if_t<_Tree == Node_Other::_Tree>>
	binary_tree_node (_Base *up, Node_Other *other) : _Base(up), _colour(other->_colour) {}
	template <typename Node_Other, typename =::std::enable_if_t<_Tree != Node_Other::_Tree>, typename = void>
	binary_tree_node (_Base *up, Node_Other *) : _Base(up) {}
	/* === Constructor & Destructor === */

	/* === Reset === */
	private:
	inline void reset () { _colour = 1; }
	/* === Reset === */

	/* === Print === */
	private:
	inline void print () const { if(_colour == 0) printf("\x1B[90mB\x1B[0m "); else printf("\x1B[91mR\x1B[0m "); }
	/* === Print === */
};

template <typename Node, bool Multi, typename Comparator, typename Allocator>
struct binary_tree_subbase<tree_rb, Node, Multi, Comparator, Allocator>
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
	static inline bool &_colour (_Node *node) { return node->cast()->_colour; }
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
		bool side, colour = _colour(node);
		_Node *parent, *replacement;
		if(node->_down[0] == nullptr && node->_down[1] == nullptr) {
			parent = node->_up;
			if(parent == &(_Base::_head)) _Base::_remove_leaf(node, del);
			else {
				side = node == parent->_down[1];
				_Base::_remove_leaf(node, del);
				_balance_erase(parent, side, colour); } }
		else {
			if(node->_down[0] != nullptr) {
				side = 1; replacement = _Iteration::_<0>(node);
				_Base::_cut_node(replacement, replacement->_down[0]);
			} else {
				side = 0; replacement = _Iteration::_<1>(node);
				_Base::_cut_node(replacement, replacement->_down[1]);
			}
			if(node == replacement->_up) { parent = replacement; side ^= 1; }
			else                           parent = replacement->_up;
			colour = _colour(replacement);
			_colour(replacement) = _colour(node);
			_Base::_replace_node(node, replacement, del);
			_balance_erase(parent, side, colour); }
	}
	/* === Erase === */
	/* ############################# Modifiers ############################# */
	/* ##################################################################### */


	/* === Balancing === */
	private:
	void
	_balance_insert (_Node *node)
	{
		_Node *parent = node->_up, *uncle, *grandparent;
		for( ; ; node = grandparent, parent = node->_up) {
			if(parent == &(_Base::_head)) { _colour(node) = 0; return; }
			if(_colour(parent) == 0) return;
			grandparent = parent->_up;
			uncle = grandparent->_down[parent == grandparent->_down[0]];
			if(uncle == nullptr || _colour(uncle) == 0) break;
			_colour(parent) = 0; _colour(uncle) = 0;
			_colour(grandparent) = 1;
		}
		if(parent == grandparent->_down[0]) {
			if(node == parent->_down[1]) {
				   _Base::_rotate_left_right(grandparent, parent, node); _colour(node) = 0; }
			else { _Base::_rotate_right     (grandparent, parent);     _colour(parent) = 0; } }
		else {
			if(node == parent->_down[0]) {
				   _Base::_rotate_right_left(grandparent, parent, node); _colour(node) = 0; }
			else { _Base::_rotate_left      (grandparent, parent);     _colour(parent) = 0; } }
		_colour(grandparent) = 1;

		// while(node != _Base::_root && _colour(node->_up) == 1) {
		// 	_Node *grandparent = node->_up->_up;
		// 	if(node->_up == grandparent->_down[0]) {
		// 		_Node *uncle = grandparent->_down[1];
		// 		if(uncle != nullptr && _colour(uncle) == 1) {
		// 			_colour(node->_up) = 0; _colour(uncle) = 0;
		// 			_colour(grandparent) = 1;
		// 			node = grandparent;
		// 		} else {
		// 			if(node == node->_up->_down[1]) {
		// 				   _Base::_rotate_left_right(grandparent);      _colour(node) = 0; }
		// 			else { _Base::_rotate_right     (grandparent); _colour(node->_up) = 0; }
		// 			_colour(grandparent) = 1; return; }
		// 	} else {
		// 		_Node *uncle = grandparent->_down[0];
		// 		if(uncle != nullptr && _colour(uncle) == 1) {
		// 			_colour(node->_up) = 0; _colour(uncle) = 0;
		// 			_colour(grandparent) = 1;
		// 			node = grandparent;
		// 		} else {
		// 			if(node == node->_up->_down[0]) {
		// 				   _Base::_rotate_right_left(grandparent);      _colour(node) = 0; }
		// 			else { _Base::_rotate_left      (grandparent); _colour(node->_up) = 0; }
		// 			_colour(grandparent) = 1; return; }
		// 	}
		// }
		// _colour(_Base::_root) = 0;
	}

	private:
	void
	_balance_erase (_Node *parent, bool side, bool colour)
	{
		_Node *brother, *nephews[2];
		if(colour == 1) return;
		if(parent->_down[side] != nullptr) { _colour(parent->_down[side]) = 0; return; }
		for( ; ; side = parent == parent->_up->_down[1], parent = parent->_up) {
			brother = parent->_down[side^1]; nephews[0] = brother->_down[0]; nephews[1] = brother->_down[1];
			if(_colour(parent) == 0 && _colour(brother) == 0 && (nephews[0] == nullptr || _colour(nephews[0]) == 0)
			   && (nephews[1] == nullptr || _colour(nephews[1]) == 0)) {
				_colour(brother) = 1;
				if(parent->_up == &(_Base::_head)) return;
			} else break;
		}
		if(_colour(brother) == 1) {
			_colour(parent) = 1; _colour(brother) = 0;
			if(side == 0) _Base::_rotate_left (parent, brother);
			else          _Base::_rotate_right(parent, brother);
			brother = parent->_down[side^1]; nephews[0] = brother->_down[0]; nephews[1] = brother->_down[1];
		}
		if(/*_colour(parent) == 1 && _colour(brother) == 0 && */(nephews[0] == nullptr || _colour(nephews[0]) == 0)
		   && (nephews[1] == nullptr || _colour(nephews[1]) == 0)) {
			_colour(parent) = 0; _colour(brother) = 1; return;
		}
		     if(side == 0 && (nephews[1] == nullptr || _colour(nephews[1]) == 0))
			{ _colour(brother) = 1; _colour(nephews[0]) = 0;
			  _Base::_rotate_right(brother, nephews[0]); brother = nephews[0]; }
		else if(side == 1 && (nephews[0] == nullptr || _colour(nephews[0]) == 0))
			{ _colour(brother) = 1; _colour(nephews[1]) = 0;
			  _Base::_rotate_left (brother, nephews[1]); brother = nephews[1]; }
		_colour(brother) = _colour(parent); _colour(parent) = 0;
		if(side == 0) { _colour(brother->_down[1]) = 0; _Base::_rotate_left (parent, brother); }
		else          { _colour(brother->_down[0]) = 0; _Base::_rotate_right(parent, brother); }
	}
	/* === Balancing === */
};

#endif
