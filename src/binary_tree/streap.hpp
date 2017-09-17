#ifndef _GMD_BINARY_TREE_STREAP_
#define _GMD_BINARY_TREE_STREAP_

template <typename Key, typename Value, typename Info, bool SetMap, bool Threaded>
struct binary_tree_node<tree_streap, Key, Value, Info, SetMap, Threaded>
: public binary_tree_node_base<binary_tree_node<tree_streap, Key, Value, Info, SetMap, Threaded>,
                               Key, Value, Info, SetMap, Threaded>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <typename, typename, typename, typename, bool> friend struct binary_tree_node_superbase;
	template <binary_tree_type, typename, typename, typename, bool, bool> friend struct binary_tree_node;
	template <bool, typename, bool> friend struct binary_tree_traversor;
	friend struct binary_tree_iteration;

	private:
	using _Node  = binary_tree_node<tree_streap, Key, Value, Info, SetMap, Threaded>;
	using _Base  = binary_tree_node_base<_Node, Key, Value, Info, SetMap, Threaded>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr binary_tree_type _Tree = tree_streap;
	static constexpr bool _SetMap = SetMap, _Threaded = Threaded;

	/* === Variables === */
	private:
	::__gnu_cxx::__aligned_membuf<Info> _info;
	size_t _key = 0;
	/* === Variables === */

	/* === Constructor & Destructor === */
	private:
	binary_tree_node (_Base *up) : _Base(up) {}
	template <bool _ = Threaded, typename = ::std::enable_if_t<_>>
	binary_tree_node (_Base *up, _Base *prev, _Base *next) : _Base(up, prev, next) {}
	template <typename Node_Other, typename = std::enable_if_t<_Tree == Node_Other::_Tree>>
	binary_tree_node (_Base *up, Node_Other *other) : _Base(up), _key(other->_key) {}
	template <typename Node_Other, typename = std::enable_if_t<_Tree != Node_Other::_Tree>, typename = void>
	binary_tree_node (_Base *up, Node_Other *) : _Base(up) {}
	/* === Constructor & Destructor === */

	/* === Reset === */
	private:
	inline void reset () {}
	/* === Reset === */

	/* === Print === */
	private:
	inline void print () const { printf("\x1B[37m%lu\x1B[0m ", _key); }
	/* === Print === */
};

template <typename Node, bool Multi, typename Comparator, typename Allocator>
struct binary_tree_subbase<tree_streap, Node, Multi, Comparator, Allocator>
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
	static inline size_t &_key (_Node *node) { return node->cast()->_key; }
	/* === Helpers === */


	/* ##################################################################### */
	/* ######################### Lookup (override) ######################### */
	/* === Count (override) === */
	public:
	template <typename Key>
	::std::enable_if_t<::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, size_t>
	count (const Key &key)
	{
		if(!Multi) {
			_Node *node = _Base::_find(key);
			if(node != &(_Base::_head)) { ++_key(node); _sift_up(node); return 1; } return 0; }
		else {
			size_t count = 0;
			_Node *lower = _Base::_lower_bound(key), *upper = _Base::_upper_bound(key);
			for( ; lower != upper; lower = _Iteration::_<1>(lower), ++count) { ++_key(lower); _sift_up(lower); }
			return count; }
	}
	/* === Count (override) === */


	/* === Contains (override) === */
	public:
	template <typename Key>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, bool>
	contains (const Key &key)
	{
		_Node *node = _Base::_find(key);
		if(node != &(_Base::_head)) { { ++_key(node); _sift_up(node); } return true; } return false;
	}
	/* === Contains (override) === */


	/* === Find (override) === */
	public:
	template <typename T = typename _Base::_Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && _Base::template _is_traversor_v<T>, T>
	find (const Key &key)
	{ _Node *node = _Base::_find(key); if(node != &(_Base::_head)) { ++_key(node); _sift_up(node); } return T(node); }
	/* === Find (override) === */


	/* === Find short (override) === */
	public:
	template <typename T = typename _Base::_Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && _Base::template _is_traversor_v<T>, T>
	find_short (const Key &key)
	{ _Node *node = _Base::_find_short(key); if(node != &(_Base::_head)) { ++_key(node); _sift_up(node); } return T(node); }
	/* === Find short (override) === */


	/* === Lower bound (override) === */
	public:
	template <typename T = typename _Base::_Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && _Base::template _is_traversor_v<T>, T>
	lower_bound (const Key &key)
	{ _Node *node = _Base::_lower_bound(key); if(node != &(_Base::_head)) { ++_key(node); _sift_up(node); } return T(node); }
	/* === Lower bound (override) === */


	/* === Upper bound (override) === */
	public:
	template <typename T = typename _Base::_Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && _Base::template _is_traversor_v<T>, T>
	upper_bound (const Key &key)
	{ _Node *node = _Base::_upper_bound(key); if(node != &(_Base::_head)) { ++_key(node); _sift_up(node); } return T(node); }
	/* === Upper bound (override) === */


	/* === Equal range (override) === */
	public:
	template <typename T = typename _Base::_Traversor, typename Key>
	::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && _Base::template _is_traversor_v<T>, ::std::pair<T, T>>
	equal_range (const Key &key)
	{
		_Node* lower = _Base::_lower_bound(key);
		if(lower == &(_Base::_head) || _Base::_comparator(key, **lower)) return ::std::pair<T, T>(T(lower), T(lower));
		if(!Multi) return ::std::pair<T, T>(T(lower), T(_Iteration::_<1>(lower)));
		_Node *upper = _Base::_upper_bound(key);
		for(_Node *node = lower; node != upper; node = _Iteration::_<1>(node)) { ++_key(node); _sift_up(node); }
		return ::std::pair<T, T>(T(lower), T(upper));
	}
	/* === Equal range (override) === */
	/* ######################### Lookup (override) ######################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ######################### Virtual functions ######################### */
	/* === Insert === */
	private:
	::std::pair<_Node *, bool>
	_insert_ (const typename Node::_Info &info)
	{
		::std::pair<_Node *, bool> result = _Base::_insert_bottom(info);
		++_key(result.first); _sift_up(result.first); return result;
	}

	private:
	::std::pair<_Node *, bool>
	_insert_ (typename Node::_Info &&info)
	{
		::std::pair<_Node *, bool> result = _Base::_insert_bottom(::std::move(info));
		++_key(result.first); _sift_up(result.first); return result;
	}

	private:
	::std::pair<_Node *, bool>
	_insert_hint_ (_Node *hint, const typename Node::_Info &info)
	{
		::std::pair<_Node *, bool> result = _Base::_insert_hint_bottom(hint, info);
		++_key(result.first); _sift_up(result.first); return result;
	}

	private:
	::std::pair<_Node *, bool>
	_insert_hint_ (_Node *hint, typename Node::_Info &&info)
	{
		::std::pair<_Node *, bool> result = _Base::_insert_hint_bottom(hint, ::std::move(info));
		++_key(result.first); _sift_up(result.first); return result;
	}
	/* === Insert === */


	/* === Emplace === */
	private:
	::std::pair<_Node *, bool>
	_emplace_ (_Node *node)
	{
		::std::pair<_Node *, bool> result = _Base::_emplace_bottom(node);
		++_key(result.first); _sift_up(result.first); return result;
	}

	private:
	::std::pair<_Node *, bool>
	_emplace_hint_ (_Node *hint, _Node *node)
	{
		::std::pair<_Node *, bool> result = _Base::_emplace_hint_bottom(hint, node);
		++_key(result.first); _sift_up(result.first); return result;
	}
	/* === Emplace === */


	/* === Erase === */
	private:
	void
	_erase_ (_Node *node, const bool del)
	{
		if(_sift_down(node) == 0) _Base::_remove_node(node, node->_down[0], del);
		else                      _Base::_remove_node(node, node->_down[1], del);
	}
	/* === Erase === */
	/* ######################### Virtual functions ######################### */
	/* ##################################################################### */


	/* === Sift === */
	private:
	void
	_sift_up (_Node *node)
	{
		for(_Node *parent = node->_up; parent != &(_Base::_head) && _key(parent) <= _key(node); parent = node->_up) {
			if(node == parent->_down[0]) _Base::_rotate_right(parent, node);
			else                         _Base::_rotate_left (parent, node);
		}
	}

	private:
	bool
	_sift_down (_Node *node)
	{
		while(node->_down[0] != nullptr) {
			if(node->_down[1] != nullptr) {
				if(_key(node->_down[0]) > _key(node->_down[1])) _Base::_rotate_right(node, node->_down[0]);
				else                                            _Base::_rotate_left (node, node->_down[1]);
			} else return 0; }
		return 1;
	}
	/* === Sift === */
};

#endif
