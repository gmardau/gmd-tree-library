#ifndef _GMD_KD_TREE_TRAVERSOR_
#define _GMD_KD_TREE_TRAVERSOR_

struct point_kd_tree_iteration
{
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

	template <bool Const_Other>
	inline bool same (const point_kd_tree_range_iterator<Const_Other, Node> &tr)
	const
	{ return (*this)() && tr() && node() == tr.node(); }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	same       (const T &tr) const { return (*this)() && tr() && node() == tr.node(); }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	operator== (const T &tr) const { return _node == tr._node; }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	operator!= (const T &tr) const { return _node != tr._node; }
	/* === Comparison === */

	/* === Info === */
	public:
	inline _Info info        () const { return  _node->info(); }
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
};

template <bool Const, typename Node>
struct point_kd_tree_range_iterator
{
	template <size_t, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
	template <bool, typename> friend struct point_kd_tree_traversor;
	template <bool, typename> friend struct point_kd_tree_range_iterator;

	private:
	using _Node       = ::std::conditional_t<Const, const typename Node::_Base, typename Node::_Base>;
	using _Handle     = _Node *;
	using _Info       = ::std::conditional_t<Const, const typename Node::_Info, typename Node::_Info>;
	using _R_Iterator = point_kd_tree_range_iterator<Const, Node>;

	template <typename T> constexpr static bool _is_traversor_v = ::std::is_same_v<T, _R_Iterator> ||
		::std::is_same_v<T, point_kd_tree_range_iterator<Const^1, Node>>;

	public:
	using value_type = _Info;
	using reference  = _Info &;
	using pointer    = _Info *;
	using iterator_category = ::std::random_access_iterator_tag;
	using difference_type = ::std::ptrdiff_t;

	/* === Variables === */
	private:
	_Handle *_handle;
	inline _Node *node () const { return *_handle; }
	/* === Variables === */

	/* === Constructor & Destructor === */
	public:
	point_kd_tree_range_iterator (_Handle *handle = nullptr) : _handle(handle) {}
	point_kd_tree_range_iterator (const point_kd_tree_range_iterator<false, Node> &other) : _handle(other._handle) {}
	/* === Constructor & Destructor === */

	/* === Comparison === */
	public:
	inline bool operator() () const { return _handle != nullptr; }

	template <bool Const_Other>
	inline bool same (const point_kd_tree_traversor<Const_Other, Node> &tr)
	const
	{ return (*this)() && tr() && node() == tr.node(); }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	same       (const T &tr) const { return (*this)() && tr() && node() == tr.node(); }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	operator== (const T &tr) const { return _handle == tr._handle; }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	operator!= (const T &tr) const { return _handle != tr._handle; }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	operator<  (const T &tr) const { return _handle <  tr._handle; }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	operator>  (const T &tr) const { return _handle >  tr._handle; }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	operator<= (const T &tr) const { return _handle <= tr._handle; }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	operator>= (const T &tr) const { return _handle >= tr._handle; }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, ::std::ptrdiff_t>
	operator-  (const T &tr) const { return _handle -  tr._handle; }
	/* === Comparison === */

	/* === Info === */
	public:
	inline _Info info        () const { return  (*_handle)->info(); }
	inline _Info &operator*  () const { return  (*_handle)->info(); }
	inline _Info *operator-> () const { return &(*_handle)->info(); }

	inline _Info &operator[] (::std::ptrdiff_t n) const { return _handle[n]->info(); }
	/* === Info === */

	/* === Traversal === */
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
	/* === Traversal === */
};

template <bool Const, typename Node, typename Allocator>
struct point_kd_tree_range
{
	template <typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
	template <bool, typename, typename> friend struct point_kd_tree_range;

	private:
	using _Node = ::std::conditional_t<Const, const typename Node::_Base, typename Node::_Base>;

	using  _R_Iterator = point_kd_tree_range_iterator<false, Node>;
	using _R_CIterator = point_kd_tree_range_iterator<true,  Node>;

	public:
	using       iterator =  _R_Iterator;
	using const_iterator = _R_CIterator;

	/* === Variables === */
	private:
	::std::vector<_Node *, Allocator> _nodes;
	/* === Variables === */

	/* === Constructor & Destructor === */
	public:
	point_kd_tree_range (size_t size = 0) { _nodes.reserve(size); }
	point_kd_tree_range (const point_kd_tree_range<false, Node, Allocator> &other)
		: _nodes(other._nodes.begin(), other._nodes.end()) {}
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
