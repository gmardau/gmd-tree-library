#ifndef _GMD_BINARY_TREE_WB_
#define _GMD_BINARY_TREE_WB_

template <typename Key, typename Value, typename Info, bool SetMap, bool Threaded>
struct binary_tree_node<tree_wb, Key, Value, Info, SetMap, Threaded>
: public binary_tree_node_base<binary_tree_node<tree_wb, Key, Value, Info, SetMap, Threaded>,
                               Key, Value, Info, SetMap, Threaded>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <typename, typename, typename, typename, bool> friend struct binary_tree_node_superbase;
	template <binary_tree_type, typename, typename, typename, bool, bool> friend struct binary_tree_node;
	template <bool, typename, bool> friend struct binary_tree_traversor;
	friend struct binary_tree_iteration;

	private:
	using _Node  = binary_tree_node<tree_wb, Key, Value, Info, SetMap, Threaded>;
	using _Base  = binary_tree_node_base<_Node, Key, Value, Info, SetMap, Threaded>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr binary_tree_type _Tree = tree_wb;
	static constexpr bool _SetMap = SetMap, _Threaded = Threaded;

	/* === Variables === */
	private:
	::__gnu_cxx::__aligned_membuf<Info> _info;
	size_t _weight = 2;
	/* === Variables === */

	/* === Constructor & Destructor === */
	private:
	binary_tree_node (_Base *up) : _Base(up) {}
	template <bool _ = Threaded, typename = ::std::enable_if_t<_>>
	binary_tree_node (_Base *up, _Base *prev, _Base *next) : _Base(up, prev, next) {}
	template <typename Node_Other, typename =::std::enable_if_t<_Tree == Node_Other::_Tree>>
	binary_tree_node (_Base *up, Node_Other *other) : _Base(up), _weight(other->_weight) {}
	template <typename Node_Other, typename =::std::enable_if_t<_Tree != Node_Other::_Tree>, typename = void>
	binary_tree_node (_Base *up, Node_Other *) : _Base(up) {}
	/* === Constructor & Destructor === */

	/* === Reset === */
	private:
	inline void reset () { _weight = 2; }
	/* === Reset === */

	/* === Print === */
	private:
	inline void print () const { printf("\x1B[37m%lu\x1B[0m ", _weight); }
	/* === Print === */
};

template <typename Node, bool Multi, typename Comparator, typename Allocator>
struct binary_tree_subbase<tree_wb, Node, Multi, Comparator, Allocator>
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
	constexpr static double _factor = 0.25;
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
	static inline size_t &_weight (_Node *node) { return node->cast()->_weight; }
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
		bool side;
		_Node *parent, *replacement;
		if(node->_down[0] == nullptr && node->_down[1] == nullptr) {
			parent = node->_up;
			if(parent == &(_Base::_head)) _Base::_remove_leaf(node, del);
			else {
				side = node == parent->_down[1];
				_Base::_remove_leaf(node, del);
				_balance_erase(parent, parent->_down[side]); } }
		else {
			if(node->_down[0] != nullptr) {
				side = 1; replacement = _Iteration::_<0>(node);
				_Base::_cut_node(replacement, replacement->_down[0]); }
			else {
				side = 0; replacement = _Iteration::_<1>(node);
				_Base::_cut_node(replacement, replacement->_down[1]); }
			if(node == replacement->_up) { parent = replacement; side ^= 1; }
			else                           parent = replacement->_up;
			_weight(replacement) = _weight(node);
			_Base::_replace_node(node, replacement, del);
			_balance_erase(parent, parent->_down[side]); }
	}
	/* === Erase === */
	/* ############################# Modifiers ############################# */
	/* ##################################################################### */


	/* === Balancing === */
	private:
	void
	_balance_insert (_Node *node)
	{
		for(_Node *parent = node->_up; parent != &(_Base::_head); parent = node->_up) {
			++_weight(parent);
			if(_weight(parent) - _weight(node) < _factor * _weight(parent)) {
				if(node == parent->_down[0]) {
					if(node->_down[1] != nullptr && (node->_down[0] == nullptr ||
					   _weight(node->_down[1]) > _weight(node->_down[0]))) {
						_rotate_left_right(parent, node, node->_down[1]); node = node->_up; }
					else     _rotate_right(parent, node);
				} else {
					if(node->_down[0] != nullptr && (node->_down[1] == nullptr ||
					   _weight(node->_down[0]) > _weight(node->_down[1]))) {
						_rotate_right_left(parent, node, node->_down[0]); node = node->_up; }
					else      _rotate_left(parent, node);
				}
			} else node = parent;
		}
	}

	private:
	void
	_balance_erase (_Node *parent, _Node *node)
	{
		for( ; parent != &(_Base::_head); parent = node->_up) {
			--_weight(parent);
			if((node != nullptr ? _weight(node) : 1) < _factor * _weight(parent)) {
				/* If this is reached, it means that brother != nullptr */
				if(node == parent->_down[1]) {
					_Node *brother = parent->_down[0];
					if(brother->_down[1] != nullptr && (brother->_down[0] == nullptr ||
					   _weight(brother->_down[1]) > _weight(brother->_down[0]))) {
						_rotate_left_right(parent, brother, brother->_down[1]); node = brother->_up; }
					else   { _rotate_right(parent, brother);                    node = brother; }
				} else {
					_Node *brother = parent->_down[1];
					if(brother->_down[0] != nullptr && (brother->_down[1] == nullptr ||
					   _weight(brother->_down[0]) > _weight(brother->_down[1]))) {
						_rotate_right_left(parent, brother, brother->_down[0]); node = brother->_up; }
					else    { _rotate_left(parent, brother);                    node = brother; }
				}
			} else node = parent;
		}
	}
	/* === Balancing === */


	/* === Weight update === */
	private:
	void
	_update_weight (_Node *node)
	{
		_weight(node) = (node->_down[0] != nullptr ? _weight(node->_down[0]) : 1) +
		                (node->_down[1] != nullptr ? _weight(node->_down[1]) : 1);
	}
	/* === Weight update === */


	/* === Node rotation === */
	private:
	void
	_rotate_left (_Node *parent, _Node *son)
	{ _Base::_rotate_left(parent, son); _update_weight(parent); _update_weight(son); }

	private:
	void
	_rotate_right (_Node *parent, _Node *son)
	{ _Base::_rotate_right(parent, son); _update_weight(parent); _update_weight(son); }

	private:
	void
	_rotate_left_right (_Node *parent, _Node *son, _Node *grandson)
	{
		_Base::_rotate_left(son, grandson);
		_Base::_rotate_right(parent, grandson);
		_update_weight(parent); _update_weight(son); _update_weight(grandson);
	}

	private:
	void
	_rotate_right_left (_Node *parent, _Node *son, _Node *grandson)
	{
		_Base::_rotate_right(son, grandson);
		_Base::_rotate_left(parent, grandson);
		_update_weight(parent); _update_weight(son); _update_weight(grandson);
	}
	/* === Node rotation === */
};

#endif
