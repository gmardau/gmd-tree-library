#ifndef _GMD_BINARY_TREE_AVL_
#define _GMD_BINARY_TREE_AVL_

template <typename Key, typename Value, typename Info, bool SetMap, bool Threaded>
struct binary_tree_node<tree_avl, Key, Value, Info, SetMap, Threaded>
: public binary_tree_node_base<binary_tree_node<tree_avl, Key, Value, Info, SetMap, Threaded>,
                               Key, Value, Info, SetMap, Threaded>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <typename, typename, typename, typename, bool> friend struct binary_tree_node_superbase;
	template <binary_tree_type, typename, typename, typename, bool, bool> friend struct binary_tree_node;
	template <bool, typename, bool> friend struct binary_tree_traversor;
	friend struct binary_tree_iteration;

	private:
	using _Node  = binary_tree_node<tree_avl, Key, Value, Info, SetMap, Threaded>;
	using _Base  = binary_tree_node_base<_Node, Key, Value, Info, SetMap, Threaded>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr binary_tree_type _Tree = tree_avl;
	static constexpr bool _SetMap = SetMap, _Threaded = Threaded;

	/* === Variables === */
	private:
	::__gnu_cxx::__aligned_membuf<Info> _info;
	int _balance = 0;
	/* === Variables === */

	/* === Constructor & Destructor === */
	private:
	binary_tree_node (_Base *up) : _Base(up) {}
	template <bool _ = Threaded, typename = ::std::enable_if_t<_>>
	binary_tree_node (_Base *up, _Base *prev, _Base *next) : _Base(up, prev, next) {}
	template <typename Node_Other, typename = std::enable_if_t<_Tree == Node_Other::_Tree>>
	binary_tree_node (_Base *up, Node_Other *other) : _Base(up), _balance(other->_balance) {}
	template <typename Node_Other, typename = std::enable_if_t<_Tree != Node_Other::_Tree>, typename = void>
	binary_tree_node (_Base *up, Node_Other *) : _Base(up) {}
	/* === Constructor & Destructor === */

	/* === Reset === */
	private:
	inline void reset () { _balance = 0; }
	/* === Reset === */

	/* === Print === */
	private:
	inline void print () const { printf("\x1B[37m%s\x1B[0m ", _balance == 0 ? "\u2022" : (_balance > 0 ? "+" : "-")); }
	/* === Print === */
};

template <typename Node, bool Multi, typename Comparator, typename Allocator>
struct binary_tree_subbase<tree_avl, Node, Multi, Comparator, Allocator>
: public binary_tree_base<Node, Multi, Comparator, Allocator>
{
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
	static inline int &_balance (_Node *node) { return node->cast()->_balance; }
	/* === Helpers === */


	/* ##################################################################### */
	/* ######################### Virtual functions ######################### */
	/* === Insert === */
	private:
	::std::pair<_Node *, bool>
	_insert_ (const typename Node::_Info &info)
	{
		::std::pair<_Node *, bool> result = _Base::_insert_bottom(info);
		if(result.second) _balance_insert(result.first);
		return result;
	}

	private:
	::std::pair<_Node *, bool>
	_insert_ (typename Node::_Info &&info)
	{
		::std::pair<_Node *, bool> result = _Base::_insert_bottom(::std::move(info));
		if(result.second) _balance_insert(result.first);
		return result;
	}

	private:
	::std::pair<_Node *, bool>
	_insert_hint_ (_Node *hint, const typename Node::_Info &info)
	{
		::std::pair<_Node *, bool> result = _Base::_insert_hint_bottom(hint, info);
		if(result.second) _balance_insert(result.first);
		return result;
	}

	private:
	::std::pair<_Node *, bool>
	_insert_hint_ (_Node *hint, typename Node::_Info &&info)
	{
		::std::pair<_Node *, bool> result = _Base::_insert_hint_bottom(hint, ::std::move(info));
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
		if(node->_down[0] == nullptr && node->_down[1] == nullptr) {
			parent = node->_up;
			if(parent == &(_Base::_head)) _Base::_remove_leaf(node, del);
			else {
				side = node == parent->_down[1];
				_Base::_remove_leaf(node, del);
				_balance_erase(parent, side); } }
		else {
			if(_balance(node) < 0) {
				side = 1; replacement = _Iteration::_<0>(node);
				_Base::_cut_node(replacement, replacement->_down[0]); }
			else {
				side = 0; replacement = _Iteration::_<1>(node);
				_Base::_cut_node(replacement, replacement->_down[1]); }
			if(node == replacement->_up) { parent = replacement; side ^= 1; }
			else                           parent = replacement->_up;
			_balance(replacement) = _balance(node);
			_Base::_replace_node(node, replacement, del);
			_balance_erase(parent, side);
		}
	}
	/* === Erase === */
	/* ######################### Virtual functions ######################### */
	/* ##################################################################### */


	/* === Balancing === */
	protected:
	void
	_balance_insert (_Node *node)
	{
		for(_Node *parent = node->_up; parent != &(_Base::_head); node = parent, parent = node->_up) {
			if(node == parent->_down[0]) {
				if(_balance(parent) < 0) {
					if(_balance(node) > 0) _rotate_left_right(parent, node, node->_down[1]);
					else                        _rotate_right(parent, node); }
				else if(_balance(parent) > 0) { _balance(parent) =  0;   return; }
				else                          { _balance(parent) = -1; continue; } }
			else {
				if(_balance(parent) > 0) {
					if(_balance(node) < 0) _rotate_right_left(parent, node, node->_down[0]);
					else                         _rotate_left(parent, node); }
				else if(_balance(parent) < 0) { _balance(parent) = 0;   return; }
				else                          { _balance(parent) = 1; continue; } }
			return; }
	}

	protected:
	void
	_balance_erase (_Node *parent, bool side)
	{
		bool next_side = 0;
		int brother_balance;
		_Node *grandparent, *brother;
		for( ; parent != &(_Base::_head); side = next_side, parent = grandparent) {
			grandparent = parent->_up;
			if(grandparent != &(_Base::_head)) next_side = parent == grandparent->_down[1];
			if(side == 0) {
				if(_balance(parent) > 0) {
					brother = parent->_down[1]; brother_balance = _balance(brother);
					if(brother_balance < 0) _rotate_right_left(parent, brother, brother->_down[0]);
					else                          _rotate_left(parent, brother); }
				else if(_balance(parent) == 0) { _balance(parent) = 1;   return; }
				else                           { _balance(parent) = 0; continue; } }
			else {
				if(_balance(parent) < 0) {
					brother = parent->_down[0]; brother_balance = _balance(brother);
					if(brother_balance > 0) _rotate_left_right(parent, brother, brother->_down[1]);
					else                         _rotate_right(parent, brother); }
				else if(_balance(parent) == 0) { _balance(parent) = -1;   return; }
				else                           { _balance(parent) =  0; continue; } }
			if(brother_balance == 0) return; }
	}
	/* === Balancing === */


	/* === Node rotation === */
	protected:
	void
	_rotate_left (_Node *parent, _Node *son)
	{
		_Base::_rotate_left(parent, son);
		if(_balance(son) == 0) { _balance(parent) = 1; _balance(son) = -1; }
		else                   { _balance(parent) = 0; _balance(son) =  0; }
	}

	protected:
	void
	_rotate_right (_Node *parent, _Node *son)
	{
		_Base::_rotate_right(parent, son);
		if(_balance(son) == 0) { _balance(parent) = -1; _balance(son) = 1; }
		else                   { _balance(parent) =  0; _balance(son) = 0; }
	}

	protected:
	void
	_rotate_left_right (_Node *parent, _Node *son, _Node *grandson)
	{
		_Base::_rotate_left_right(parent, son, grandson);
		     if(_balance(grandson) < 0) { _balance(parent) = 1; _balance(son) =  0; }
		else if(_balance(grandson) > 0) { _balance(parent) = 0; _balance(son) = -1; }
		else                            { _balance(parent) = 0; _balance(son) =  0; }
		_balance(grandson) = 0;
	}

	protected:
	void
	_rotate_right_left (_Node *parent, _Node *son, _Node *grandson)
	{
		_Base::_rotate_right_left(parent, son, grandson);
		     if(_balance(grandson) < 0) { _balance(parent) =  0; _balance(son) = 1; }
		else if(_balance(grandson) > 0) { _balance(parent) = -1; _balance(son) = 0; }
		else                            { _balance(parent) =  0; _balance(son) = 0; }
		_balance(grandson) = 0;
	}
	/* === Node rotation === */
};

#endif
