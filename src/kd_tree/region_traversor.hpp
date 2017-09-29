#ifndef _GMD_REGION_KD_TREE_TRAVERSOR_
#define _GMD_REGION_KD_TREE_TRAVERSOR_

template <bool Const, typename Node> struct region_kd_tree_iterator;
template <bool Const, typename Node> struct region_kd_tree_range_iterator;

template <bool Const, typename Node>
struct region_kd_tree_traversor
{
	template <ushort, typename, typename, typename, typename, typename> friend struct region_kd_tree_base;
	template <bool, typename> friend struct region_kd_tree_traversor;
	template <bool, typename> friend struct region_kd_tree_iterator;
	template <bool, typename> friend struct region_kd_tree_range_iterator;

	private:
	using _Node      = ::std::conditional_t<Const, const typename Node::_Base, typename Node::_Base>;
	using _Info      = ::std::conditional_t<Const, const typename Node::_Info, typename Node::_Info>;
	using _Traversor = region_kd_tree_traversor<Const, Node>;
	using _Iterator  = region_kd_tree_iterator<Const, Node>;

	template <typename T> constexpr static bool _is_traversor_v = ::std::is_same_v<T, _Traversor> ||
		::std::is_same_v<T, region_kd_tree_traversor<Const^1, Node>>;

	public:
	using value_type = _Info;
	using reference  = _Info &;
	using pointer    = _Info *;

	/* === Variables === */
	private:
	_Node *_node;
	inline _Node *node () const { return _node; }
	/* === Variables === */

	/* === Constructor & Destructor === */
	public:
	region_kd_tree_traversor (_Node *node = nullptr) : _node(node) {}
	region_kd_tree_traversor (const region_kd_tree_traversor<false, Node> &other) : _node(other._node) {}
	explicit region_kd_tree_traversor (const _Iterator &other) : _node(other.node()) {}
	explicit region_kd_tree_traversor (const region_kd_tree_range_iterator<Const, Node> &other) : _node(other.node()) {}
	/* === Constructor & Destructor === */

	/* === Comparison === */
	public:
	inline bool operator() () const { return _node != nullptr; }

	template <bool Const_Other>
	inline bool same (const region_kd_tree_iterator<Const_Other, Node> &it)
	const
	{ return (*this)() && it() && node() == it.node(); }

	template <bool Const_Other>
	inline bool same (const region_kd_tree_range_iterator<Const_Other, Node> &it)
	const
	{ return (*this)() && it() && node() == it.node(); }

	template <typename T> inline ::std::enable_if_t<_is_traversor_v<T>, bool>
	same       (const T &tr) const { return (*this)() && tr() && node() == tr.node(); }

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
	inline bool is_leaf () const { return _node->is_leaf(); }

	inline _Traversor &go_up      () { _node = _node->_up;      return *this; }
	inline _Traversor &go_lesser  () { _node = _node->_down[0]; return *this; }
	inline _Traversor &go_greater () { _node = _node->_down[1]; return *this; }

	inline _Traversor up      () const { return _Traversor(_node->_up);      }
	inline _Traversor lesser  () const { return _Traversor(_node->_down[0]); }
	inline _Traversor greater () const { return _Traversor(_node->_down[1]); }
	/* === Traversal === */

	/* === Range === */
	public:
	::std::pair<_Iterator, _Iterator>
	range ()
	const
	{
		_Node *first = _node, *last = _node;
		while(!first->is_leaf()) first = first->_down[first->_down[0] == nullptr];
		while(! last->is_leaf())  last =  last->_down[ last->_down[1] != nullptr];
		return {_Iterator(first), _Iterator(last->_down[1])};
	}
	/* === Range === */
};

template <bool Const, typename Node>
struct region_kd_tree_iterator
{
	template <ushort, typename, typename, typename, typename, typename> friend struct region_kd_tree_base;
	template <bool, typename> friend struct region_kd_tree_traversor;
	template <bool, typename> friend struct region_kd_tree_iterator;
	template <bool, typename> friend struct region_kd_tree_range_iterator;

	private:
	using _Node     = ::std::conditional_t<Const, const typename Node::_Base, typename Node::_Base>;
	using _Info     = ::std::conditional_t<Const, const typename Node::_Info, typename Node::_Info>;
	using _Traversor = region_kd_tree_traversor<Const, Node>;
	using _Iterator = region_kd_tree_iterator<Const, Node>;

	template <typename T> constexpr static bool _is_iterator_v = ::std::is_same_v<T, _Iterator> ||
		::std::is_same_v<T, region_kd_tree_iterator<Const^1, Node>>;

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
	region_kd_tree_iterator (_Node *node = nullptr) : _node(node) {}
	region_kd_tree_iterator (const region_kd_tree_iterator<false, Node> &other) : _node(other._node) {}
	explicit region_kd_tree_iterator (const _Traversor &other) : _node(other.is_leaf() ? other.node() : nullptr) {}
	explicit region_kd_tree_iterator (const region_kd_tree_range_iterator<Const, Node> &other) : _node(other.node()) {}
	/* === Constructor & Destructor === */

	/* === Comparison === */
	public:
	inline bool operator() () const { return _node != nullptr; }

	template <bool Const_Other>
	inline bool same (const region_kd_tree_traversor<Const_Other, Node> &tr)
	const
	{ return (*this)() && tr() && node() == tr.node(); }

	template <bool Const_Other>
	inline bool same (const region_kd_tree_range_iterator<Const_Other, Node> &it)
	const
	{ return (*this)() && it() && node() == it.node(); }

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, bool>
	same       (const T &tr) const { return (*this)() && tr() && node() == tr.node(); }

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, bool>
	operator== (const T &tr) const { return _node == tr._node; }

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, bool>
	operator!= (const T &tr) const { return _node != tr._node; }
	/* === Comparison === */

	/* === Info === */
	public:
	inline _Info &operator*  () const { return  _node->info(); }
	inline _Info *operator-> () const { return &_node->info(); }
	/* === Info === */

	/* === Iteration === */
	public:
	inline _Iterator &operator-- ()    {                        _node = node->_down[0]; return *this; }
	inline _Iterator &operator++ ()    {                        _node = node->_down[1]; return *this; }
	inline _Iterator  operator-- (int) { _Iterator tmp = *this; _node = node->_down[0]; return tmp;   }
	inline _Iterator  operator++ (int) { _Iterator tmp = *this; _node = node->_down[1]; return tmp;   }

	inline _Iterator &go_prev () { _node = _node->_down[0]; return *this; }
	inline _Iterator &go_next () { _node = _node->_down[1]; return *this; }

	inline _Iterator prev () const { return _Iterator(_node->_down[0]); }
	inline _Iterator next () const { return _Iterator(_node->_down[1]); }
	/* === Iteration === */
};

template <bool Const, typename Node>
struct region_kd_tree_range_iterator
{
	template <ushort, typename, typename, typename, typename, typename> friend struct region_kd_tree_base;
	template <bool, typename> friend struct region_kd_tree_traversor;
	template <bool, typename> friend struct region_kd_tree_iterator;
	template <bool, typename> friend struct region_kd_tree_range_iterator;

	private:
	using _Node       = ::std::conditional_t<Const, const typename Node::_Base, typename Node::_Base>;
	using _Handle     = _Node *;
	using _Info       = ::std::conditional_t<Const, const typename Node::_Info, typename Node::_Info>;
	using _R_Iterator = region_kd_tree_range_iterator<Const, Node>;

	template <typename T> constexpr static bool _is_iterator_v = ::std::is_same_v<T, _R_Iterator> ||
		::std::is_same_v<T, region_kd_tree_range_iterator<Const^1, Node>>;

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
	region_kd_tree_range_iterator (_Handle *handle = nullptr) : _handle(handle) {}
	region_kd_tree_range_iterator (const region_kd_tree_range_iterator<false, Node> &other) : _handle(other._handle) {}
	/* === Constructor & Destructor === */

	/* === Comparison === */
	public:
	inline bool operator() () const { return _handle != nullptr; }

	template <bool Const_Other>
	inline bool same (const region_kd_tree_traversor<Const_Other, Node> &tr)
	const
	{ return (*this)() && tr() && node() == tr.node(); }

	template <bool Const_Other>
	inline bool same (const region_kd_tree_iterator<Const_Other, Node> &it)
	const
	{ return (*this)() && it() && node() == it.node(); }

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, bool>
	same       (const T &it) const { return (*this)() && it() && node() == it.node(); }

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

	template <typename T> inline ::std::enable_if_t<_is_iterator_v<T>, ::std::ptrdiff_t>
	operator-  (const T &it) const { return _handle -  it._handle; }
	/* === Comparison === */

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
struct region_kd_tree_range
{
	template <ushort, typename, typename, typename, typename, typename> friend struct region_kd_tree_base;
	template <bool, typename, typename> friend struct region_kd_tree_range;

	private:
	using _Node = ::std::conditional_t<Const, const typename Node::_Base, typename Node::_Base>;

	using  _R_Iterator = region_kd_tree_range_iterator<false, Node>;
	using _R_CIterator = region_kd_tree_range_iterator<true,  Node>;

	public:
	using       iterator =  _R_Iterator;
	using const_iterator = _R_CIterator;

	/* === Variables === */
	private:
	::std::vector<_Node *, Allocator> _nodes;
	/* === Variables === */

	/* === Constructor & Destructor === */
	public:
	region_kd_tree_range (size_t size = 0) { _nodes.reserve(size); }
	region_kd_tree_range (const region_kd_tree_range<false, Node, Allocator> &other)
		: _nodes(other._nodes.begin(), other._nodes.end()) {}
	region_kd_tree_range (region_kd_tree_range<false, Node, Allocator> &&other)
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
