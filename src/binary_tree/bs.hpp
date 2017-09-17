#ifndef _GMD_BINARY_TREE_BS_
#define _GMD_BINARY_TREE_BS_

template <typename Key, typename Value, typename Info, bool SetMap, bool Threaded>
struct binary_tree_node<tree_bs, Key, Value, Info, SetMap, Threaded>
: public binary_tree_node_base<binary_tree_node<tree_bs, Key, Value, Info, SetMap, Threaded>,
                               Key, Value, Info, SetMap, Threaded>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <typename, typename, typename, typename, bool> friend struct binary_tree_node_superbase;
	template <binary_tree_type, typename, typename, typename, bool, bool> friend struct binary_tree_node;
	template <bool, typename, bool> friend struct binary_tree_traversor;
	friend struct binary_tree_iteration;

	private:
	using _Node  = binary_tree_node<tree_bs, Key, Value, Info, SetMap, Threaded>;
	using _Base  = binary_tree_node_base<_Node, Key, Value, Info, SetMap, Threaded>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr binary_tree_type _Tree = tree_bs;
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
struct binary_tree_subbase<tree_bs, Node, Multi, Comparator, Allocator>
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


	/* ##################################################################### */
	/* ######################### Virtual functions ######################### */
	/* === Insert === */
	private:
	::std::pair<_Node *, bool>
	_insert_ (const typename Node::_Info &info)
	{ return _Base::_insert_bottom(info); }

	private:
	::std::pair<_Node *, bool>
	_insert_ (typename Node::_Info &&info)
	{ return _Base::_insert_bottom(::std::move(info)); }

	private:
	::std::pair<_Node *, bool>
	_insert_hint_ (_Node *hint, const typename Node::_Info &info)
	{ return _Base::_insert_hint_bottom(hint, info); }

	private:
	::std::pair<_Node *, bool>
	_insert_hint_ (_Node *hint, typename Node::_Info &&info)
	{ return _Base::_insert_hint_bottom(hint, ::std::move(info)); }
	/* === Insert === */


	/* === Emplace === */
	private:
	::std::pair<_Node *, bool>
	_emplace_ (_Node *node)
	{ return _Base::_emplace_bottom(node); }

	private:
	::std::pair<_Node *, bool>
	_emplace_hint_ (_Node *hint, _Node *node)
	{ return _Base::_emplace_hint_bottom(hint, node); }
	/* === Emplace === */


	/* === Erase === */
	private:
	void
	_erase_ (_Node *node, const bool del)
	{
		if(node->_down[0] == nullptr && node->_down[1] == nullptr) _Base::_remove_leaf(node, del);
		else {
			_Node *replacement;
			if(node->_down[0] != nullptr) {
				replacement = _Iteration::_<0>(node);
				_Base::_cut_node(replacement, replacement->_down[0]); }
			else {
				replacement = _Iteration::_<1>(node);
				_Base::_cut_node(replacement, replacement->_down[1]); }
			_Base::_replace_node(node, replacement, del); }
	}
	/* === Erase === */
	/* ######################### Virtual functions ######################### */
	/* ##################################################################### */
};

#endif
