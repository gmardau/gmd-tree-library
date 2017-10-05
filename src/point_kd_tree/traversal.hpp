#ifndef _GMD_POINT_KD_TREE_TRAVERSAL_
#define _GMD_POINT_KD_TREE_TRAVERSAL_

struct point_kd_tree_iteration
{
	template <ushort, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
	template <bool, typename> friend struct point_kd_tree_traversor;

	private:
	template <bool Direction, typename Node>
	static Node *
	_ (Node *node)
	{
		if(node->_down[Direction] != nullptr) {
			if(node->_down[0] == node) return node;
			for(node = node->_down[Direction]; node->_down[Direction^1] != nullptr; node = node->_down[Direction^1]) {}
			return node; }
		else {
			Node *parent = node->_up;
			for( ; parent->_down[Direction] == node; node = parent, parent = parent->_up) {}
			return node->_down[Direction] == parent ? node : parent; }
	}

	private:
	template <bool Direction, typename Node>
	static const Node *
	_ (const Node *node)
	{
		if(node->_down[Direction] != nullptr) {
			if(node->_down[0] == node) return node;
			for(node = node->_down[Direction]; node->_down[Direction^1] != nullptr; node = node->_down[Direction^1]) {}
			return node; }
		else {
			const Node *parent = node->_up;
			for( ; parent->_down[Direction] == node; node = parent, parent = parent->_up) {}
			return node->_down[Direction] == parent ? node : parent; }
	}
};

template <bool Const, typename Node> struct point_kd_tree_range_iterator;

template <bool Const, typename Node>
struct point_kd_tree_traversor
{
	template <ushort, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
	template <bool, typename> friend struct point_kd_tree_traversor;
	template <bool, typename> friend struct point_kd_tree_range_iterator;

	private:
	using _Node       = ::std::conditional_t<Const, const typename Node::_Base, typename Node::_Base>;
	using _Info       = ::std::conditional_t<Const, const typename Node::_Info, typename Node::_Info>;
	using _Traversor  = point_kd_tree_traversor<Const, Node>;
	using _Iteration  = point_kd_tree_iteration;

	template <typename T> constexpr static bool _is_traversor_v = ::std::is_same_v<T, _Traversor> ||
		::std::is_same_v<T, point_kd_tree_traversor<Const^1, Node>>;

	public:
	using value_type = _Info;
	using reference  = _Info &;
	using pointer    = _Info *;
	using iterator_category = ::std::bidirectional_iterator_tag;
	using difference_type = ::std::ptrdiff_t;

	/* === Variables === */
	private:
	_Node *_node;
	inline _Node *node () const { return _node; }
	/* === Variables === */

	/* === Constructor & Destructor === */
	public:
	point_kd_tree_traversor (_Node *node = nullptr) : _node(node) {}
	point_kd_tree_traversor (const point_kd_tree_traversor<false, Node> &other) : _node(other._node) {}
	explicit point_kd_tree_traversor (const point_kd_tree_range_iterator<Const, Node> &other) : _node(other.node()) {}
	/* === Constructor & Destructor === */

	/* === Comparison === */
	public:
	inline bool operator() () const { return _node != nullptr; }

	template <bool Const_Other> inline bool
	operator== (const point_kd_tree_range_iterator<Const_Other, Node> &it) const { return node() == it.node(); }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	operator== (const T &tr) const { return _node == tr._node; }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	operator!= (const T &tr) const { return _node != tr._node; }
	/* === Comparison === */

	/* === Info === */
	public:
	inline _Info &operator*  () const { return  _node->info(); }
	inline _Info *operator-> () const { return &_node->info(); }
	/* === Info === */

	/* === Traversal === */
	public:
	inline _Traversor &operator-- ()    {                         _node = _Iteration::_<0>(_node); return *this; }
	inline _Traversor &operator++ ()    {                         _node = _Iteration::_<1>(_node); return *this; }
	inline _Traversor  operator-- (int) { _Traversor tmp = *this; _node = _Iteration::_<0>(_node); return tmp;   }
	inline _Traversor  operator++ (int) { _Traversor tmp = *this; _node = _Iteration::_<1>(_node); return tmp;   }

	inline _Traversor &go_up      () { _node = _node->_up;              return *this; }
	inline _Traversor &go_lesser  () { _node = _node->_down[0];         return *this; }
	inline _Traversor &go_greater () { _node = _node->_down[1];         return *this; }
	inline _Traversor &go_prev    () { _node = _Iteration::_<0>(_node); return *this; }
	inline _Traversor &go_next    () { _node = _Iteration::_<1>(_node); return *this; }

	inline _Traversor up      () const { return _Traversor(_node->_up);              }
	inline _Traversor lesser  () const { return _Traversor(_node->_down[0]);         }
	inline _Traversor greater () const { return _Traversor(_node->_down[1]);         }
	inline _Traversor prev    () const { return _Traversor(_Iteration::_<0>(_node)); }
	inline _Traversor next    () const { return _Traversor(_Iteration::_<1>(_node)); }
	/* === Traversal === */

	/* === Range === */
	public:
	::std::pair<_Traversor, _Traversor>
	range ()
	const
	{
		_Node *first = _node, *last = _node;
		while(first->_down[0] != nullptr) first = first->_down[0];
		while( last->_down[1] != nullptr)  last =  last->_down[1];
		return {_Traversor(first), _Traversor(last->_down[1])};
	}
	/* === Range === */
};

template <bool Const, typename Node>
struct point_kd_tree_range_iterator
{
	template <ushort, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
	template <bool, typename> friend struct point_kd_tree_traversor;
	template <bool, typename> friend struct point_kd_tree_range_iterator;

	private:
	using _Node       = ::std::conditional_t<Const, const typename Node::_Base, typename Node::_Base>;
	using _Info       = ::std::conditional_t<Const, const typename Node::_Info, typename Node::_Info>;
	using _Handle     = ::std::conditional_t<Const, _Node * const *, _Node **>;
	using _R_Iterator = point_kd_tree_range_iterator<Const, Node>;

	template <typename T> constexpr static bool _is_iterator_v = ::std::is_same_v<T, _R_Iterator> ||
		::std::is_same_v<T, point_kd_tree_range_iterator<Const^1, Node>>;

	public:
	using value_type = _Info;
	using reference  = _Info &;
	using pointer    = _Info *;
	using iterator_category = ::std::random_access_iterator_tag;
	using difference_type = ::std::ptrdiff_t;

	/* === Variables === */
	private:
	_Handle _handle;
	inline _Node *node () const { return *_handle; }
	/* === Variables === */

	/* === Constructor & Destructor === */
	public:
	point_kd_tree_range_iterator (_Handle handle = nullptr) : _handle(handle) {}
	point_kd_tree_range_iterator (const point_kd_tree_range_iterator<false, Node> &other) : _handle(other._handle) {}
	/* === Constructor & Destructor === */

	/* === Traversor === */
	public:
	inline point_kd_tree_traversor<Const, Node> traversor () const { return point_kd_tree_traversor<Const, Node>(this); }
	/* === Traversor === */

	/* === Comparison === */
	public:
	inline bool operator() () const { return _handle != nullptr; }

	template <bool Const_Other> inline bool
	operator== (const point_kd_tree_traversor<Const_Other, Node> &tr) const { return node() == tr.node(); }

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, bool>
	operator== (const T &it) const { return _handle == it._handle; }

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, bool>
	operator!= (const T &it) const { return _handle != it._handle; }

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, bool>
	operator<  (const T &it) const { return _handle <  it._handle; }

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, bool>
	operator>  (const T &it) const { return _handle >  it._handle; }

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, bool>
	operator<= (const T &it) const { return _handle <= it._handle; }

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, bool>
	operator>= (const T &it) const { return _handle >= it._handle; }
	/* === Comparison === */

	/* === Difference === */
	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, ::std::ptrdiff_t>
	operator-  (const T &it) const { return _handle -  it._handle; }
	/* === Difference === */

	/* === Info === */
	public:
	inline _Info &operator*  () const { return  (*_handle)->info(); }
	inline _Info *operator-> () const { return &(*_handle)->info(); }

	inline _Info &operator[] (::std::ptrdiff_t n) const { return _handle[n]->info(); }
	/* === Info === */

	/* === Iteration === */
	public:
	inline _R_Iterator &operator-- ()    { --_handle; return *this; }
	inline _R_Iterator &operator++ ()    { ++_handle; return *this; }
	inline _R_Iterator  operator-- (int) { return _R_Iterator(_handle--); }
	inline _R_Iterator  operator++ (int) { return _R_Iterator(_handle++); }

	inline _R_Iterator &operator-= (::std::ptrdiff_t n) { _handle -= n; return *this; }
	inline _R_Iterator &operator+= (::std::ptrdiff_t n) { _handle += n; return *this; }
	inline _R_Iterator  operator-  (::std::ptrdiff_t n) { return _R_Iterator(_handle - n); }
	inline _R_Iterator  operator+  (::std::ptrdiff_t n) { return _R_Iterator(_handle + n); }

	inline _R_Iterator &go_prev () { --_handle; return *this; }
	inline _R_Iterator &go_next () { ++_handle; return *this; }

	inline _R_Iterator prev () const { return _R_Iterator(_handle - 1); }
	inline _R_Iterator next () const { return _R_Iterator(_handle + 1); }
	/* === Iteration === */
};

template <bool Const, typename Node, typename Allocator>
struct point_kd_tree_range
{
	template <ushort, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
	template <bool, typename, typename> friend struct point_kd_tree_range;

	private:
	using _Node = ::std::conditional_t<Const, const typename Node::_Base, typename Node::_Base>;
	using _Info = ::std::conditional_t<Const, const typename Node::_Info, typename Node::_Info>;

	using  _R_Iterator = point_kd_tree_range_iterator<false, Node>;
	using _R_CIterator = point_kd_tree_range_iterator<true,  Node>;

	public:
	using      value_type = _Info;
	using difference_type = ::std::ptrdiff_t;
	using       reference = value_type &;
	using const_reference = const typename Node::_Info &;
	using         pointer = value_type *;
	using   const_pointer = const typename Node::_Info *;

	using       iterator =  _R_Iterator;
	using const_iterator = _R_CIterator;

	/* === Variables === */
	private:
	::std::vector<_Node *, Allocator> _nodes;
	/* === Variables === */

	/* === Constructor & Destructor === */
	public:
	point_kd_tree_range (size_t size = 0) { _nodes.reserve(size); }
	template <int _ = 0, typename = ::std::enable_if_t<Const && _ == _>>
	point_kd_tree_range (const point_kd_tree_range<false, Node, Allocator> &other)
		: _nodes(other._nodes.begin(), other._nodes.end()) {}
	template <int _ = 0, typename = ::std::enable_if_t<Const && _ == _>>
	point_kd_tree_range (point_kd_tree_range<false, Node, Allocator> &&other)
		: _nodes(other._nodes.begin(), other._nodes.end()) { other._nodes.clear(); }
	/* === Constructor & Destructor === */

	/* === Iterators === */
	public:
	template <bool _ = !Const, typename = ::std::enable_if_t<_>>
	inline  _R_Iterator  begin ()       { return  _R_Iterator(&_nodes[0]); }
	inline _R_CIterator  begin () const { return _R_CIterator(&_nodes[0]); }
	inline _R_CIterator cbegin () const { return _R_CIterator(&_nodes[0]); }

	template <bool _ = !Const, typename = ::std::enable_if_t<_>>
	inline  _R_Iterator  end ()       { return  _R_Iterator(&_nodes[_nodes.size()]); }
	inline _R_CIterator  end () const { return _R_CIterator(&_nodes[_nodes.size()]); }
	inline _R_CIterator cend () const { return _R_CIterator(&_nodes[_nodes.size()]); }
	/* === Iterators === */

	/* === Capacity === */
	public:
	bool  empty () const { return _nodes.empty(); }
	size_t size () const { return _nodes.size();  }
	/* === Capacity === */

	/* === Modifiers === */
	private:
	inline void _push (_Node *node) { _nodes.push_back(node); }
	/* === Modifiers === */
};

#endif
