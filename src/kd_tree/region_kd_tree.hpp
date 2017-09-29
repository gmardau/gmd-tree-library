#ifndef _GMD_REGION_KD_TREE_
#define _GMD_REGION_KD_TREE_

template <typename Node, typename Key, typename Value, typename Info, bool SetMap>
struct region_kd_tree_node_base
{
	template <ushort, typename, typename, typename, typename, typename> friend struct region_kd_tree_base;
	template <bool, typename> friend struct region_kd_tree_traversor;
	template <bool, typename> friend struct region_kd_tree_iterator;
	template <bool, typename> friend struct region_kd_tree_range_iterator;

	private:
	using _Node = region_kd_tree_node_base<Node, Key, Value, Info, SetMap>;

	/* === Variables === */
	private:
	_Node *_up, *_down[2] = {nullptr, nullptr};
	/* === Variables === */

	/* === Constructor & Destructor === */
	protected:
	region_kd_tree_node_base (_Node *up) : _up(up) {}
	region_kd_tree_node_base (_Node *up, _Node *prev, _Node *next) : _up(up), _down{prev, next} {}
	/* === Constructor & Destructor === */

	/* === Cast === */
	private:
	constexpr       Node *cast ()       { return reinterpret_cast<      Node *>(this); }
	constexpr const Node *cast () const { return reinterpret_cast<const Node *>(this); }
	/* === Cast === */

	/* === Key === */
	private:
	template <bool _ = !SetMap, typename = ::std::enable_if_t<_>>
	static inline const Key &key (const Info &info) { return info; }

	template <bool _ =  SetMap, typename = ::std::enable_if_t<_>, typename = void>
	static inline const Key &key (const Info &info) { return info.first; }

	private:
	template <bool _ = !SetMap, typename = ::std::enable_if_t<_>>
	inline const Key &operator* () const { return *cast()->_info._M_ptr(); }

	template <bool _ =  SetMap, typename = ::std::enable_if_t<_>, typename = void>
	inline const Key &operator* () const { return  cast()->_info._M_ptr()->first; }
	/* === Key === */

	/* === Value === */
	private:
	template <bool _ = SetMap, typename = ::std::enable_if_t<_>>
	inline       Value &value ()       { return cast()->_info._M_ptr()->second; }

	template <bool _ = SetMap, typename = ::std::enable_if_t<_>>
	inline const Value &value () const { return cast()->_info._M_ptr()->second; }
	/* === Value === */

	/* === Info === */
	private:
	inline       Info &info ()       { return *cast()->_info._M_ptr(); }
	inline const Info &info () const { return *cast()->_info._M_ptr(); }
	/* === Info === */

	/* === Depth === */
	private:
	inline       ushort &depth ()       { return cast()->_depth; }
	inline const ushort &depth () const { return cast()->_depth; }
	/* === Depth === */

	/* === Leaf === */
	private:
	inline bool is_leaf () const { return cast()->_depth == ::std::numeric_limits<ushort>::max();}
	/* === Leaf === */
};

template <typename Key, typename Value, typename Info, bool SetMap>
struct region_kd_tree_node
: public region_kd_tree_node_base<region_kd_tree_node<Key, Value, Info, SetMap>, Key, Value, Info, SetMap>
{
	template <ushort, typename, typename, typename, typename, typename> friend struct region_kd_tree_base;
	template <typename, typename, typename, typename, bool> friend struct region_kd_tree_node_base;
	template <bool, typename> friend struct region_kd_tree_traversor;
	template <bool, typename> friend struct region_kd_tree_iterator;
	template <bool, typename> friend struct region_kd_tree_range_iterator;

	private:
	using _Node  = region_kd_tree_node<Key, Value, Info, SetMap>;
	using _Base  = region_kd_tree_node_base<_Node, Key, Value, Info, SetMap>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr bool _SetMap = SetMap;

	/* === Variables === */
	private:
	ushort _depth = ::std::numeric_limits<ushort>::max();
	::__gnu_cxx::__aligned_membuf<Info> _info;
	/* === Variables === */

	/* === Constructor & Destructor === */
	private:
	region_kd_tree_node (_Base *up, ushort depth) : _Base(up), _depth(depth) {}
	region_kd_tree_node (_Base *up, _Base *prev, _Base *next) : _Base(up, prev, next) {}
	/* === Constructor & Destructor === */
};

template <ushort K, typename Node, typename Divider, typename Comparator, typename Equal, typename Allocator>
struct region_kd_tree_base
{
	template <ushort, typename, typename, typename, typename, typename> friend struct region_kd_tree_base;

	private:
	using _Node = typename Node::_Base;

	using _Allocator = typename ::std::allocator_traits<Allocator>::template rebind_alloc<Node>;
	using _ATraits   = typename ::std::allocator_traits<_Allocator>;

	using  _Traversor = region_kd_tree_traversor<false, Node>;
	using _CTraversor = region_kd_tree_traversor<true , Node>;
	using   _Iterator = region_kd_tree_iterator <false, Node>;
	using  _CIterator = region_kd_tree_iterator <true , Node>;

	using  _Range = region_kd_tree_range<false, Node, Allocator>;
	using _CRange = region_kd_tree_range<true , Node, Allocator>;

	// Perhaps use ::std::disjunction for this
	template <typename T> static constexpr bool _is_traversor_v = ::std::is_same_v<T, _Traversor> ||
	                                                              ::std::is_same_v<T, _CTraversor>;
	template <typename T> static constexpr bool _is_non_const_traversor_v = ::std::is_same_v<T, _Traversor>;
	template <typename T> static constexpr bool _is_const_traversor_v = ::std::is_same_v<T, _CTraversor>;

	template <typename T> static constexpr bool _is_iterator_v = ::std::is_same_v<T, _Iterator> ||
	                                                             ::std::is_same_v<T, _CIterator>;
	template <typename T> static constexpr bool _is_non_const_iterator_v = ::std::is_same_v<T, _Iterator>;
	template <typename T> static constexpr bool _is_const_iterator_v = ::std::is_same_v<T, _CIterator>;

	public:
	using        key_type = typename Node::_Key;
	using      value_type = typename Node::_Info;
	using       size_type = size_t;
	using difference_type = ::std::ptrdiff_t;
	using     key_divider = Divider;
	using     key_compare = Comparator;
	using       key_equal = Equal;
	using  allocator_type = Allocator;
	using       reference =       value_type &;
	using const_reference = const value_type &;
	using         pointer =       value_type *;
	using   const_pointer = const value_type *;

	using       traversor =  _Traversor;
	using const_traversor = _CTraversor;
	using        iterator =   _Iterator;
	using  const_iterator =  _CIterator;

	using       range =  _Range;
	using const_range = _CRange;


	/* === Variables === */
	private:
	Divider _divider;
	Comparator _comparator;
	Equal _equal;
	_Allocator _allocator;
	size_t _size = 0;
	_Node _head = _Node(nullptr);
	/* === Variables === */


	/* ##################################################################### */
	/* ##################### Constructor & Destructor ###################### */
	/* === Default === */
	public:
	region_kd_tree_base (const Divider &d = Divider(), const Comparator &c = Comparator(),
	                     const Equal &e = Equal(), const Allocator &a = Allocator())
		: _divider(d),         _comparator(c),            _equal(e),       _allocator(_Allocator(a)) { _reset_head(); }

	region_kd_tree_base (const Divider &d, const Comparator &c, const Allocator &a)
		: _divider(d),         _comparator(c),            _equal(Equal()), _allocator(_Allocator(a)) { _reset_head(); }

	region_kd_tree_base (const Divider &d, const Equal &e, const Allocator &a = Allocator())
		: _divider(d),         _comparator(Comparator()), _equal(e),       _allocator(_Allocator(a)) { _reset_head(); }

	region_kd_tree_base (const Divider &d, const Allocator &a)
		: _divider(d),         _comparator(Comparator()), _equal(Equal()), _allocator(_Allocator(a)) { _reset_head(); }

	region_kd_tree_base (const Comparator &c, const Equal &e = Equal(), const Allocator &a = Allocator())
		: _divider(Divider()), _comparator(c),            _equal(e),       _allocator(_Allocator(a)) { _reset_head(); }

	region_kd_tree_base (const Comparator &c, const Allocator &a)
		: _divider(Divider()), _comparator(c),            _equal(Equal()), _allocator(_Allocator(a)) { _reset_head(); }

	region_kd_tree_base (const Equal &e, const Allocator &a = Allocator())
		: _divider(Divider()), _comparator(Comparator()), _equal(e),       _allocator(_Allocator(a)) { _reset_head(); }

	region_kd_tree_base (const Allocator &a)
		: _divider(Divider()), _comparator(Comparator()), _equal(Equal()), _allocator(_Allocator(a)) { _reset_head(); }
	/* === Default === */


	/* === Destructor === */
	public:
	~region_kd_tree_base () { if(_size > 0) _clear(); }
	/* === Destructor === */
	/* ##################### Constructor & Destructor ###################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################# Observers ############################# */
	/* === Divider === */
	public:
	inline       Divider &get_divider ()       { return _divider; }
	inline const Divider &get_divider () const { return _divider; }
	/* === Divider === */


	/* === Comparator === */
	public:
	inline Comparator key_comp () const { return _comparator; }

	public:
	struct Info_Comparator {
		template <ushort, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
		private: Comparator _comparator; Info_Comparator (Comparator c) : _comparator(c) {}
		public: bool operator() (const typename Node::_Info &v1, const typename Node::_Info &v2) const {
			return _comparator(v1.first, v2.first); } };

	public:
	template <bool _ = !Node::_SetMap> inline ::std::enable_if_t<_, Comparator>
	value_comp () const { return _comparator; }

	template <bool _ =  Node::_SetMap> inline ::std::enable_if_t<_, Info_Comparator>
	value_comp () const { return Info_Comparator(_comparator); }

	public:
	inline       Comparator &get_comparator ()       { return _comparator; }
	inline const Comparator &get_comparator () const { return _comparator; }
	/* === Comparator === */


	/* === Equal === */
	public:
	inline Equal key_eq () const { return _equal; }

	public:
	struct Info_Equal {
		template <ushort, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
		private: Equal _equal; Info_Equal (Equal c) : _equal(c) {}
		public: bool operator() (const typename Node::_Info &v1, const typename Node::_Info &v2) const {
			return _equal(v1.first, v2.first); } };

	public:
	template <bool _ = !Node::_SetMap> inline ::std::enable_if_t<_, Equal>
	value_eq () const { return _equal; }

	template <bool _ =  Node::_SetMap> inline ::std::enable_if_t<_, Info_Equal>
	value_eq () const { return Info_Equal(_equal); }

	public:
	inline       Equal &get_equal ()       { return _equal; }
	inline const Equal &get_equal () const { return _equal; }
	/* === Equal === */


	/* === Allocator === */
	public:
	inline Allocator get_allocator () const { return Allocator(_allocator); }
	/* === Allocator === */
	/* ############################# Observers ############################# */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ###################### Traversors / Iterators ####################### */
	public:
	inline  _Traversor  root ()       { return  _Traversor(_head._up); }
	inline _CTraversor  root () const { return _CTraversor(_head._up); }
	inline _CTraversor croot () const { return _CTraversor(_head._up); }

	inline  _Iterator  begin ()       { return  _Iterator(_head._down[1]); }
	inline _CIterator  begin () const { return _CIterator(_head._down[1]); }
	inline _CIterator cbegin () const { return _CIterator(_head._down[1]); }

	inline  _Iterator  end ()       { return  _Iterator(&_head); }
	inline _CIterator  end () const { return _CIterator(&_head); }
	inline _CIterator cend () const { return _CIterator(&_head); }
	/* ###################### Traversors / Iterators ####################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################# Capacity ############################## */
	public:
	inline bool      empty () const { return _size == 0; }
	inline size_t     size () const { return _size;      }
	inline size_t max_size () const { return _ATraits::max_size(_allocator); }
	/* ############################# Capacity ############################## */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################# Modifiers ############################# */
	/* === Clear === */
	public:
	void
	clear ()
	{ if(_size > 0) { _clear(); _head._up = nullptr; _reset_head(); } }
	/* === Clear === */


	/* === Insert === */
	public:
	template <bool Replace = false, typename T = _Traversor>
	::std::enable_if_t<_is_traversor_v<T> || _is_iterator_v<T>, ::std::pair<T, bool>>
	insert (const typename Node::_Info &info)
	{
		if(!Replace) return _insert(info);
		else {
			::std::pair<_Node *, bool> result = _insert(info);
			if(!result.second) { _del_info(result.first); _new_info(result.first, info); }
			return result; }
	}

	public:
	template <bool Replace = false, typename T = _Traversor>
	::std::enable_if_t<_is_traversor_v<T> || _is_iterator_v<T>, ::std::pair<T, bool>>
	insert (typename Node::_Info &&info)
	{
		if(!Replace) return _insert(::std::move(info));
		else {
			::std::pair<_Node *, bool> result = _insert(::std::move(info));
			if(!result.second) { _del_info(result.first); _new_info(result.first, ::std::move(info)); }
			return result; }
	}

	public:
	template <bool Replace = false, typename T1, typename T2>
	size_t
	insert (const T1 &first, const T2 &last)
	{
		if(_size == 0) { _construct_tree(first, last); return _size; }
		size_t count = 0;
		if(!Replace) for(T1 tr = first; tr != last; ++tr) count += _insert(*tr).second;
		else {
			for(T1 tr = first; tr != last; ++tr) {
				::std::pair<_Node *, bool> result = _insert(*tr); count += result.second;
				if(!result.second) { _del_info(result.first); _new_info(result.first, *tr); } } }
		return count;
	}

	public:
	template <bool Replace = false>
	inline size_t
	insert (const ::std::initializer_list<typename Node::_Info> &il)
	{ return insert<Replace>(il.begin(), il.end()); }
	/* === Insert === */


	/* === Emplace === */
	public:
	template <bool Replace = false, typename T = _Traversor, typename... Args>
	::std::enable_if_t<_is_traversor_v<T> || _is_iterator_v<T>, ::std::pair<T, bool>>
	emplace (Args&&... info)
	{
		_Node *node = _new_node_leaf(nullptr, _head._down[0], &_head, ::std::forward<Args>(info)...);
		::std::pair<_Node *, bool> result = _emplace(node);
		if(!result.second) { if(Replace) { _del_info(result.first); _new_info(result.first, node->info()); }
		                     _del_node_leaf(node); }
		return result;
	}

	public:
	template <typename T = _Traversor, typename... Args>
	::std::enable_if_t<Node::_SetMap && (_is_traversor_v<T> || _is_iterator_v<T>), ::std::pair<T, bool>>
	try_emplace (const typename Node::_Key &key, Args&&... value)
	{
		int side; _Node *place = _place(side, key);
		if(side == -1) return {place, false};
		return {_emplace_place(side, place, _new_node(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(key), ::std::forward_as_tuple(::std::forward<Args>(value)...))), true};
	}

	public:
	template <typename T = _Traversor, typename... Args>
	::std::enable_if_t<Node::_SetMap && (_is_traversor_v<T> || _is_iterator_v<T>), ::std::pair<T, bool>>
	try_emplace (typename Node::_Key &&key, Args&&... value)
	{
		int side; _Node *place = _place(side, ::std::move(key));
		if(side == -1) return {place, false};
		return {_emplace_place(side, place, _new_node(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(::std::move(key)), ::std::forward_as_tuple(::std::forward<Args>(value)...))), true};
	}
	/* === Emplace === */


	/* === Erase === */
	public:
	bool
	erase (const typename Node::_Key &key)
	{ _Node *node = _find(key); if(node == &_head) return false; _erase_(node, true); return true; }

	public:
	template <typename T>
	inline ::std::enable_if_t<_is_non_const_traversor_v<T> || _is_non_const_iterator_v<T>, void>
	erase (const T &tr)
	{ _erase(tr.node(), true); }

	public:
	inline size_t
	erase (const ::std::initializer_list<typename Node::_Key> &il)
	{
		size_t count = 0;
		for(const typename Node::_Key *key = il.begin(); key != il.end(); ++key) count += erase(*key);
		return count;
	}
	/* === Erase === */
	/* ############################# Modifiers ############################# */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ########################## Element Access ########################### */
	/* === Array subscript === */
	public:
	template <int _ = 0>
	::std::enable_if_t<Node::_SetMap && _ == _, typename Node::_Value &>
	operator[] (const typename Node::_Key &key)
	{
		int side; _Node *place = _place(side, key);
		if(side == -1) return place->value();
		return _emplace_place(side, place, _new_node(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(key), ::std::tuple<>())).first->value();
	}

	public:
	template <int _ = 0>
	::std::enable_if_t<Node::_SetMap && _ == _, typename Node::_Value &>
	operator[] (typename Node::_Key &&key)
	{
		int side; _Node *place = _place(side, ::std::move(key));
		if(side == -1) return place->value();
		return _emplace_place(side, place, _new_node(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(::std::move(key)), ::std::tuple<>())).first->value();
	}
	/* === Array subscript === */


	/* === At === */
	public:
	template <typename Key>
	::std::enable_if_t<Node::_SetMap &&
		(::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>), typename Node::_Value &>
	at (const Key &key)
	{
		_Node *node = _find(key);
		if(node == &_head) throw ::std::out_of_range("range_kd_tree_map.at() out_of_range");
		return node->value();
	}

	public:
	template <typename Key>
	::std::enable_if_t<Node::_SetMap &&
		(::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>), const typename Node::_Value &>
	at (const Key &key)
	const
	{
		const _Node *node = _find(key);
		if(node == &_head) throw ::std::out_of_range("range_kd_tree_map.at() out_of_range");
		return node->value();
	}
	/* === At === */
	/* ########################## Element Access ########################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################## Lookup ############################### */
	/* === Count === */
	public:
	template <typename Key>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, size_t>
	count (const Key &key)
	{ return _find(key) != &_head; }

	public:
	template <typename Key>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, size_t>
	count (const Key &key)
	const
	{ return _find(key) != &_head; }
	/* === Count === */


	/* === Contains === */
	public:
	template <typename Key>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, bool>
	contains (const Key &key)
	{ return _find(key) != &_head; }

	public:
	template <typename Key>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, bool>
	contains (const Key &key)
	const
	{ return _find(key) != &_head; }
	/* === Contains === */


	/* === Find === */
	public:
	template <typename T = _Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && (_is_traversor_v<T> || _is_iterator_v<T>), T>
	find (const Key &key)
	{ return T(_find(key)); }

	public:
	template <typename T = _CTraversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && (_is_const_traversor_v<T> || _is_const_iterator_v<T>), T>
	find (const Key &key)
	const
	{ return T(_find(key)); }
	/* === Find === */


	/* === Equal range === */
	public:
	template <typename T = _Traversor, typename Key>
	::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && (_is_traversor_v<T> || _is_iterator_v<T>), ::std::pair<T, T>>
	equal_range (const Key &key)
	{ _Node* node = _find(key); return ::std::pair<T, T>(T(node), T(node == &_head ? node : node->_down[1])); }

	public:
	template <typename T = _CTraversor, typename Key>
	::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && (_is_const_traversor_v<T> || _is_const_iterator_v<T>), ::std::pair<T, T>>
	equal_range (const Key &key)
	const
	{ const _Node* node = _find(key); return ::std::pair<T, T>(T(node), T(node == &_head ? node : node->_down[1])); }
	/* === Equal range === */


	/* === Nearest neighbour === */
	public:
	template <typename Measure, typename T = _Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
					   && (_is_traversor_v<T> || _is_iterator_v<T>), ::std::pair<T, double>>
	nearest_neighbour (const Key &key, Measure &measure)
	{
		if(size == 0) return {&_head, 0};
		double distance = ::std::numeric_limits<double>::max(); _Node *node;
		_nearest_neighbour(key, measure, distance, node, 0, _head._up);
		return {node, distance};
	}

	public:
	template <typename Measure, typename T = _CTraversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
					   && (_is_const_traversor_v<T> || _is_const_iterator_v<T>), ::std::pair<T, double>>
	nearest_neighbour (const Key &key, Measure &measure)
	const
	{
		if(size == 0) return {&_head, 0};
		double distance = ::std::numeric_limits<double>::max(); const _Node *node;
		_nearest_neighbour(key, measure, distance, node, 0, _head._up);
		return {node, distance};
	}

	public:
	template <typename Measure, typename T = _Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
					   && (_is_traversor_v<T> || _is_iterator_v<T>), ::std::pair<T, double>>
	nearest_neighbour (const Key &key, const Measure &measure = Measure())
	{
		if(size == 0) return {&_head, 0};
		double distance = ::std::numeric_limits<double>::max(); _Node *node;
		_nearest_neighbour(key, measure, distance, node, 0, _head._up);
		return {node, distance};
	}

	public:
	template <typename Measure, typename T = _CTraversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
					   && (_is_const_traversor_v<T> || _is_const_iterator_v<T>), ::std::pair<T, double>>
	nearest_neighbour (const Key &key, const Measure &measure = Measure())
	const
	{
		if(size == 0) return {&_head, 0};
		double distance = ::std::numeric_limits<double>::max(); const _Node *node;
		_nearest_neighbour(key, measure, distance, node, 0, _head._up);
		return {node, distance};
	}
	/* === Nearest neighbour === */


	/* === Range search === */
	public:
	template <typename Key1, typename Key2>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key1> && std::is_same_v<typename Node::_Key, Key2>)
							  || _is_transparent_v<Comparator, Key1>, _Range>
	range_search (const Key1 &min, const Key2 &max)
	{ _Range range(::std::sqrt(_size)); _range_search(range, min, max, 0, 0, _head._up); return range; }

	public:
	template <typename Key1, typename Key2>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key1> && std::is_same_v<typename Node::_Key, Key2>)
							  || _is_transparent_v<Comparator, Key1>, _CRange>
	range_search (const Key1 &min, const Key2 &max)
	const
	{ _CRange range(::std::sqrt(_size)); _range_search(range, min, max, 0, 0, _head._up); return range; }
	/* === Range search === */
	/* ############################## Lookup ############################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################### Print ############################### */
	public:
	template <bool Verbose = false, typename Printer>
	inline void
	print (Printer &printer) const
	{ if(_size > 0) _print<Verbose>(printer, 0, 0, 0, _head._up); }

	template <bool Verbose = false, typename Printer>
	inline void
	print (const Printer &printer = Printer()) const
	{ if(_size > 0) _print<Verbose>(printer, 0, 0, 0, _head._up); }

	template <bool Verbose = false, typename Printer, typename T>
	inline ::std::enable_if_t<_is_traversor_v<T>, void>
	print (const T &tr, Printer &printer) const
	{ _print<Verbose>(printer, 0, 0, 0, tr._node); }

	template <bool Verbose = false, typename Printer, typename T>
	inline ::std::enable_if_t<_is_traversor_v<T>, void>
	print (const T &tr, const Printer &printer = Printer()) const
	{ _print<Verbose>(printer, 0, 0, 0, tr._node); }
	/* ############################### Print ############################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ###################### Public functions (API) ####################### */
	/* ##################################################################### */
	                            /* ########### */
	/* ##################################################################### */
	                            /* ########### */
	/* ##################################################################### */
	/* ######################## Internal functions ######################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ########################## Tree Management ########################## */
	private:
	inline void _reset () { _size = 0; _head._up = nullptr; _reset_head(); }
	/* ########################## Tree Management ########################## */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ########################## Node Management ########################## */
	/* === Head === */
	private:
	void
	_reset_head ()
	{ _head._down[0] = &_head; _head._down[1] = &_head; }
	/* === Head === */


	/* === Node === */
	private:
	template <typename... Args>
	_Node *
	_new_node_divider (_Node *up, ushort depth, Args&&... info)
	{
		Node *node = _ATraits::allocate(_allocator, 1);
		:: new(node) Node(up, depth); _new_info(node, ::std::forward<Args>(info)...);
		return node;
	}

	private:
	template <typename... Args>
	_Node *
	_new_node_leaf (_Node *up, _Node *prev, _Node *next, Args&&... info)
	{
		++_size; Node *node = _ATraits::allocate(_allocator, 1);
		:: new(node) Node(up, prev, next); _new_info(node, ::std::forward<Args>(info)...);
		return node;
	}

	private:
	void
	_del_node_divider (_Node *node)
	{ _del_info(node); node->cast()->~Node(); _ATraits::deallocate(_allocator, node->cast(), 1); }

	private:
	void
	_del_node_leaf (_Node *node)
	{ _del_info(node); node->cast()->~Node(); _ATraits::deallocate(_allocator, node->cast(), 1); --_size; }

	private:
	void
	_reset_node (_Node *node)
	{ node->_down[0] = nullptr; node->_down[1] = nullptr; node->cast()->reset(); }
	/* === Node === */


	/* === Info === */
	private:
	template <typename... Args>
	inline void
	_new_info (_Node *node, Args&&... info)
	{ ::new(&node->info()) typename Node::_Info(::std::forward<Args>(info)...); }

	private:
	inline void
	_del_info (_Node *node)
	{ node->info().Node::_Info::~_Info(); }
	/* === Info === */
	/* ########################## Node Management ########################## */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################# Modifiers ############################# */
	/* === Clear === */
	private:
	inline void
	_clear ()
	{ _clear_routine(_head._up); }

	private:
	void
	_clear_routine (_Node *node)
	{
		for(_Node *save; node != nullptr && !node->is_leaf(); node = save) {
			if(node->_down[0] != nullptr) _clear_routine(node->_down[0]);
			save = node->_down[1];
			_del_node_divider(node); }
		_del_node_leaf(node);
	}
	/* === Clear === */


	/* === Place === */
	private:
	_Node *
	_place (int &side, const typename Node::_Key &key)
	{
		if(_head._up == nullptr || _head._up->is_leaf()) { side = 0; return &_head; }
		_Node *node = _head._up; side = 0;
		for(ushort d = 0; !node->is_leaf(); d = (d + 1) % K) {
			side = !_comparator(d, key, **node);
			if(!side) { if(node->_down[0] != nullptr) node = node->_down[0]; else return node; }
			else      { if(node->_down[1] != nullptr) node = node->_down[1]; else return node; } }
		if(_equal(**node, key)) { side = -1; return node; } else return node->_up;
	}

	private:
	const _Node *
	_place (int &side, const typename Node::_Key &key)
	const
	{
		if(_head._up == nullptr || _head._up->is_leaf()) { side = 0; return &_head; }
		const _Node *node = _head._up; side = 0;
		for(ushort d = 0; !node->is_leaf(); d = (d + 1) % K) {
			side = !_comparator(d, key, **node);
			if(!side) { if(node->_down[0] != nullptr) node = node->_down[0]; else return node; }
			else      { if(node->_down[1] != nullptr) node = node->_down[1]; else return node; } }
		if(_equal(**node, key)) { side = -1; return node; } else return node->_up;
	}

	private:
	void
	_place_dividers (int &side, _Node *&place, const typename Node::_Key &key)
	{
		_Node *node;
		if(place == &_head) {
			if(_head._up == nullptr) return;
			node = _new_node_divider(&_head, 0, _divider());
			node->_down[!_comparator(0, **_head._up, **node)] = _head._up;
			_head._up->_up = node; _head._up = node;
			side = !_comparator(0, key, **node);
			place = node; return; }

		for( ; place->_down[side] != nullptr; place = node) {
			node = _new_node_divider(place, place->depth() + 1, _divider(place->depth() + 1, **place, side));
			node->_down[!_comparator(node->depth() % K, **place->_down[side], **node)] = place->_down[side];
			place->_down[side]->_up = node; place->_down[side] = node;
			side = !_comparator(node->depth() % K, key, **node); }
	}
	/* === Place === */


	/* === Insert === */
	private:
	template <typename Arg>
	::std::pair<_Node *, bool>
	_insert (Arg &&info)
	{
		int side; _Node *node = _place(side, _Node::key(::std::forward<Arg>(info)));
		if(side == -1) return {node, false};
		else return {_insert_place(side, node, ::std::forward<Arg>(info)), true};
	}

	private:
	template <typename Arg>
	_Node *
	_insert_place (int side, _Node *place, Arg &&info)
	{
		_place_dividers(side, place, _Node::key(::std::forward<Arg>(info)));
		if(place == &_head) {
			_head._up = _new_node_leaf(&_head, &_head, &_head, ::std::forward<Arg>(info));
			_head._down[0] = _head._up; _head._down[1] = _head._up;
			return _head._up; }
		else {
			_Node *node = _new_node_leaf(place, _head._down[0], &_head, ::std::forward<Arg>(info)); place->_down[side] = node;
			_head._down[0]->_down[1] = node; _head._down[0] = node;
			return node; }
	}
	/* === Insert === */


	/* === Emplace === */
	private:
	::std::pair<_Node *, bool>
	_emplace (_Node *node)
	{
		int side; _Node *place = _place(side, **node);
		if(side == -1) return {place, false};
		_emplace_place(side, place, node); return {node, true};
	}

	private:
	void
	_emplace_place (int side, _Node *place, _Node *node)
	{
		_place_dividers(side, place, **node);
		if(place == &_head) {
			_head._up = node; node->_up = &_head;
			_head._down[0] = node; _head._down[1] = node; }
		else {
			place->_down[side] = node; node->_up = place;
			_head._down[0]->_down[1] = node; _head._down[0] = node; }
	}
	/* === Emplace === */


	/* === Erase === */
	private:
	void
	_erase (_Node *node, const bool del)
	{
		printf("%f %f\n", (**node).v[0], (**node).v[1]);
		_Node *parent = node->_up; bool side;
		node->_down[0]->_down[1] = node->_down[1];
		node->_down[1]->_down[0] = node->_down[0];
		if(parent == &_head)                  { _head._up           = nullptr; if(del) _del_node_leaf(node); return; }
		else { side = node == parent->_down[1]; parent->_down[side] = nullptr; if(del) _del_node_leaf(node); }
		side = !side; node = parent->_down[side]; if(!node->is_leaf()) return;
		for( ; parent->_down[!side] == nullptr; parent = node->_up) {
			if(parent->_up == &_head) {
				_head._up                = node; node->_up = &_head;      _del_node_divider(parent); return; }
			else { side = parent == parent->_up->_down[1];
				parent->_up->_down[side] = node; node->_up = parent->_up; _del_node_divider(parent); } }
	}
	/* === Erase === */
	/* ############################# Modifiers ############################# */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################## Lookup ############################### */
	/* === Find === */
	private:
	template <typename Key>
	_Node *
	_find (const Key &key)
	{
		_Node *node = _head._up;
		for(ushort d = 0; !node->is_leaf(); node = node->_down[!_comparator(d, key, **node)], d = (d + 1) % K) {}
		return _equal(**node, key) ? node : &_head;
	}

	private:
	template <typename Key>
	const _Node *
	_find (const Key &key)
	const
	{
		const _Node *node = _head._up;
		for(ushort d = 0; !node->is_leaf(); node = node->_down[!_comparator(d, key, **node)], d = (d + 1) % K) {}
		return _equal(**node, key) ? node : &_head;
	}
	/* === Find === */


	/* === Nearest neighbour === */
	private:
	template <typename Measure, typename Key>
	void
	_nearest_neighbour (const Key &key, Measure &measure,
		                double &distance, _Node *&nearest, ushort d, const _Node *node)
	{
		if(node->is_leaf()) {
			double tmp = measure(**node, key);
			if(tmp < distance) { distance = tmp, nearest = node; }
			return; }
		if(_comparator(d, key, **node)) {
			if(node->_down[0] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]);
			if(node->_down[1] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]); }
		else {
			if(node->_down[1] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]);
			if(node->_down[0] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]); }
	}

	private:
	template <typename Measure, typename Key>
	void
	_nearest_neighbour (const Key &key, Measure &measure,
		                double &distance, _Node *&nearest, ushort d, const _Node *node)
	const
	{
		if(node->is_leaf()) {
			double tmp = measure(**node, key);
			if(tmp < distance) { distance = tmp, nearest = node; }
			return; }
		if(_comparator(d, key, **node)) {
			if(node->_down[0] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]);
			if(node->_down[1] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]); }
		else {
			if(node->_down[1] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]);
			if(node->_down[0] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]); }
	}

	private:
	template <typename Measure, typename Key>
	void
	_nearest_neighbour (const Key &key, const Measure &measure,
		                double &distance, _Node *&nearest, ushort d, const _Node *node)
	{
		if(node->is_leaf()) {
			double tmp = measure(**node, key);
			if(tmp < distance) { distance = tmp, nearest = node; }
			return; }
		if(_comparator(d, key, **node)) {
			if(node->_down[0] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]);
			if(node->_down[1] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]); }
		else {
			if(node->_down[1] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]);
			if(node->_down[0] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]); }
	}

	private:
	template <typename Measure, typename Key>
	void
	_nearest_neighbour (const Key &key, const Measure &measure,
						double &distance, _Node *&nearest, ushort d, const _Node *node)
	const
	{
		if(node->is_leaf()) {
			double tmp = measure(**node, key);
			if(tmp < distance) { distance = tmp, nearest = node; }
			return; }
		if(_comparator(d, key, **node)) {
			if(node->_down[0] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]);
			if(node->_down[1] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]); }
		else {
			if(node->_down[1] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]);
			if(node->_down[0] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]); }
	}
	/* === Nearest neighbour === */


	/* === Range search === */
	private:
	template <typename Key1, typename Key2>
	void
	_range_search (_Range &range, const Key1 &min, const Key2 &max, ushort bounds, ushort d, _Node *node)
	{
		if(node->is_leaf()) { if(_range_inside(min, max, d, node)) range._push(node); return; }
		if(_range_bounded(bounds)) { _report_subtree(range, node); return; }
		if(!_comparator(d, max, **node)) {
			if(node->_down[1] != nullptr) {
				if(!_comparator(d, node, min))
					 _range_search(range, min, max, bounds | (1 << (d * 2)), (d + 1) % K, node->_down[1]);
				else _range_search(range, min, max, bounds                 , (d + 1) % K, node->_down[1]); }
			if(node->_down[0] != nullptr && _comparator(d, min, **node))
				_range_search(range, min, max, bounds | (1 << (d * 2 + 1)), (d + 1) % K, node->_down[0]); }
		else if(node->_down[0] != nullptr) _range_search(range, min, max, bounds, (d + 1) % K, node->_down[0]);
	}

	private:
	template <typename Key1, typename Key2>
	void
	_range_search (_CRange &range, const Key1 &min, const Key2 &max, ushort bounds, ushort d, _Node *node)
	const
	{
		if(node->is_leaf()) { if(_range_inside(min, max, d, node)) range._push(node); return; }
		if(_range_bounded(bounds)) { _report_subtree(range, node); return; }
		if(!_comparator(d, max, **node)) {
			if(node->_down[1] != nullptr) {
				if(!_comparator(d, node, min))
					 _range_search(range, min, max, bounds | (1 << (d * 2)), (d + 1) % K, node->_down[1]);
				else _range_search(range, min, max, bounds                 , (d + 1) % K, node->_down[1]); }
			if(node->_down[0] != nullptr && _comparator(d, min, **node))
				_range_search(range, min, max, bounds | (1 << (d * 2 + 1)), (d + 1) % K, node->_down[0]); }
		else if(node->_down[0] != nullptr) _range_search(range, min, max, bounds, (d + 1) % K, node->_down[0]);
	}

	private:
	bool
	_range_bounded (ushort bounds)
	const
	{ for(ushort i = 0; i < K * 2; ++i) if(!((bounds >> i) & 1)) return false; return true; }

	private:
	template <typename Key1, typename Key2>
	bool
	_range_inside (const Key1 &min, const Key2 &max, ushort d, _Node *node)
	{
		for(ushort i = 0; i < K; ++i)
			if(i != d && (_comparator(i, **node, min) || _comparator(i, max, **node))) return false;
		return true;
	}

	private:
	template <typename Key1, typename Key2>
	bool
	_range_inside (const Key1 &min, const Key2 &max, ushort d, const _Node *node)
	const
	{
		for(ushort i = 0; i < K; ++i)
			if(i != d && (_comparator(i, **node, min) || _comparator(i, max, **node))) return false;
		return true;
	}

	private:
	template <typename Range>
	void
	_report_subtree (Range &range, const _Node *node)
	const
	{
		_Node *first = node, *last = node;
		while(!first->is_leaf()) first = first->_down[first->_down[0] == nullptr];
		while(! last->is_leaf())  last =  last->_down[ last->_down[1] != nullptr];
		for( ; first != last; first = first->_down[1]) range._push(first);
		range._push(last);
	}
	/* === Range search === */
	/* ############################## Lookup ############################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################### Print ############################### */
	private:
	template <bool Verbose, typename Printer>
	void
	_print (Printer &printer, int_fast64_t branches, ushort depth, bool side, const _Node *node)
	const
	{
		if(!node->is_leaf() && node->_down[1] != nullptr)
			_print<Verbose>
				(printer, side == 0 ? branches | (1 << (depth - 1)) : branches, depth + 1, 1, node->_down[1]);
		if(depth == 0) printf("%s\u2574", node->_up == &_head ? "\u2500" : "\u2504");
		else           printf("  ");
		if(depth > 1) {
			for(ushort i = 0; i < depth - 1; ++i) {
				if((branches >> i) & 1) printf("\u2502   ");
				else                    printf("    "); } }
		if(depth > 0) {
			if(side == 0) printf("\u2514\u2500\u2500\u2574");
			else          printf("\u250c\u2500\u2500\u2574"); }
		if constexpr(Verbose) {
			if(!node->is_leaf()) printf("\x1B[90m%d\x1B[0m ", node->depth() % K);
			else                 printf("\x1B[90m\u2022\x1B[0m "); }
		printer(node->info()); printf("\n");
		if(!node->is_leaf() && node->_down[0] != nullptr)
			_print<Verbose>
				(printer, side == 1 ? branches | (1 << (depth - 1)) : branches, depth + 1, 0, node->_down[0]);
	}

	private:
	template <bool Verbose, typename Printer>
	void
	_print (const Printer &printer, int_fast64_t branches, ushort depth, bool side, const _Node *node)
	const
	{
		if(!node->is_leaf() && node->_down[1] != nullptr)
			_print<Verbose>
				(printer, side == 0 ? branches | (1 << (depth - 1)) : branches, depth + 1, 1, node->_down[1]);
		if(depth == 0) printf("%s\u2574", node->_up == &_head ? "\u2500" : "\u2504");
		else           printf("  ");
		if(depth > 1) {
			for(ushort i = 0; i < depth - 1; ++i) {
				if((branches >> i) & 1) printf("\u2502   ");
				else                    printf("    "); } }
		if(depth > 0) {
			if(side == 0) printf("\u2514\u2500\u2500\u2574");
			else          printf("\u250c\u2500\u2500\u2574"); }
		if constexpr(Verbose) {
			if(!node->is_leaf()) printf("\x1B[90m%d\x1B[0m ", node->depth() % K);
			else                 printf("\x1B[90m\u2022\x1B[0m "); }
		printer(node->info()); printf("\n");
		if(!node->is_leaf() && node->_down[0] != nullptr)
			_print<Verbose>
				(printer, side == 1 ? branches | (1 << (depth - 1)) : branches, depth + 1, 0, node->_down[0]);
	}
	/* ############################### Print ############################### */
	/* ##################################################################### */
};

#endif
