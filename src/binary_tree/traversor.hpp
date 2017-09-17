#ifndef _GMD_BINARY_TREE_TRAVERSOR_
#define _GMD_BINARY_TREE_TRAVERSOR_

struct binary_tree_iteration
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <bool, typename, bool> friend struct binary_tree_traversor;

	private:
	template <bool Direction, typename Node, typename = ::std::enable_if_t<!Node::_Threaded>>
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
	template <bool Direction, typename Node, typename = ::std::enable_if_t<!Node::_Threaded>>
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

	private:
	template <bool Direction, typename Node, typename = ::std::enable_if_t<Node::_Threaded>, typename = void>
	static constexpr       Node *_ (      Node *node) { return node->_thread[Direction]; }

	template <bool Direction, typename Node, typename = ::std::enable_if_t<Node::_Threaded>, typename = void>
	static constexpr const Node *_ (const Node *node) { return node->_thread[Direction]; }
};

template <bool Const, typename Node, bool Direction>
struct binary_tree_traversor
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <bool, typename, bool> friend struct binary_tree_traversor;

	private:
	using _Node       = ::std::conditional_t<Const, const typename Node::_Base, typename Node::_Base>;
	using _Info       = ::std::conditional_t<Const, const typename Node::_Info, typename Node::_Info>;
	using _Traversor  = binary_tree_traversor<Const, Node, Direction>;
	using _RTraversor = binary_tree_traversor<Const, Node, Direction^1>;
	using _Iteration  = binary_tree_iteration;

	template <typename T> constexpr static bool _is_traversor_v = ::std::is_same_v<T, _Traversor> ||
		::std::is_same_v<T, _RTraversor> || ::std::is_same_v<T, binary_tree_traversor<Const^1, Node, Direction>> ||
		::std::is_same_v<T, binary_tree_traversor<Const^1, Node, Direction^1>>;

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
	binary_tree_traversor (_Node *node = nullptr) : _node(node) {}
	template <bool Direction_Other>
	binary_tree_traversor (const binary_tree_traversor<false, Node, Direction_Other> &other) : _node(other._node) {}
	/* === Constructor & Destructor === */

	/* === Reverse === */
	public:
	inline _RTraversor reverse () const { return _RTraversor(_node); }
	/* === Reverse === */

	/* === Comparison === */
	public:
	inline bool operator() () const { return _node != nullptr; }

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
	inline _Traversor &operator-- ()    {                         _node = _Iteration::_<Direction^1>(_node); return *this; }
	inline _Traversor &operator++ ()    {                         _node = _Iteration::_<Direction  >(_node); return *this; }
	inline _Traversor  operator-- (int) { _Traversor tmp = *this; _node = _Iteration::_<Direction^1>(_node); return tmp;   }
	inline _Traversor  operator++ (int) { _Traversor tmp = *this; _node = _Iteration::_<Direction  >(_node); return tmp;   }

	inline _Traversor &go_up    () { _node = _node->_up;                        return *this; }
	inline _Traversor &go_left  () { _node = _node->_down[0];                   return *this; }
	inline _Traversor &go_right () { _node = _node->_down[1];                   return *this; }
	inline _Traversor &go_prev  () { _node = _Iteration::_<Direction^1>(_node); return *this; }
	inline _Traversor &go_next  () { _node = _Iteration::_<Direction  >(_node); return *this; }

	inline _Traversor up    () const { return _Traversor(_node->_up);                        }
	inline _Traversor left  () const { return _Traversor(_node->_down[0]);                   }
	inline _Traversor right () const { return _Traversor(_node->_down[1]);                   }
	inline _Traversor prev  () const { return _Traversor(_Iteration::_<Direction^1>(_node)); }
	inline _Traversor next  () const { return _Traversor(_Iteration::_<Direction  >(_node)); }
	/* === Traversal === */
};

#endif
