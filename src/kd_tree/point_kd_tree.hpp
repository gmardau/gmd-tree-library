#ifndef _GMD_POINT_KD_TREE_
#define _GMD_POINT_KD_TREE_

template <typename Node, typename Key, typename Value, typename Info, bool SetMap>
struct point_kd_tree_node_base
{
	template <ushort, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
	template <bool, typename, typename> friend struct kd_tree_range;
	template <bool, typename> friend struct point_kd_tree_traversor;
	template <bool, typename> friend struct point_kd_tree_range_iterator;

	private:
	using _Node = point_kd_tree_node_base<Node, Key, Value, Info, SetMap>;

	/* === Variables === */
	private:
	_Node *_up, *_down[2] = {nullptr, nullptr};
	/* === Variables === */

	/* === Constructor & Destructor === */
	protected:
	point_kd_tree_node_base (_Node *up) : _up(up) {}
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
};

template <typename Key, typename Value, typename Info, bool SetMap, bool Balanced>
struct point_kd_tree_node;

template <typename Key, typename Value, typename Info, bool SetMap>
struct point_kd_tree_node<Key, Value, Info, SetMap, false>
: public point_kd_tree_node_base<point_kd_tree_node<Key, Value, Info, SetMap, false>, Key, Value, Info, SetMap>
{
	template <ushort, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
	template <typename, typename, typename, typename, bool> friend struct point_kd_tree_node_base;
	template <bool, typename, typename> friend struct kd_tree_range;
	template <bool, typename> friend struct point_kd_tree_traversor;
	template <bool, typename> friend struct point_kd_tree_range_iterator;
	friend struct point_kd_tree_iteration;

	private:
	using _Node  = point_kd_tree_node<Key, Value, Info, SetMap, false>;
	using _Base  = point_kd_tree_node_base<_Node, Key, Value, Info, SetMap>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr bool _SetMap = SetMap, _Balanced = false;

	/* === Variables === */
	private:
	::__gnu_cxx::__aligned_membuf<Info> _info;
	/* === Variables === */

	/* === Constructor & Destructor === */
	private:
	point_kd_tree_node (_Base *up) : _Base(up) {}
	template <typename Node_Other>
	point_kd_tree_node (_Base *up, Node_Other *) : _Base(up) {}
	/* === Constructor & Destructor === */

	/* === Print === */
	private:
	inline void print () const {}
	/* === Print === */
};

template <typename Key, typename Value, typename Info, bool SetMap>
struct point_kd_tree_node<Key, Value, Info, SetMap, true>
: public point_kd_tree_node_base<point_kd_tree_node<Key, Value, Info, SetMap, true>, Key, Value, Info, SetMap>
{
	template <ushort, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;
	template <typename, typename, typename, typename, bool> friend struct point_kd_tree_node_base;
	template <bool, typename, typename> friend struct kd_tree_range;
	template <bool, typename> friend struct point_kd_tree_traversor;
	template <bool, typename> friend struct point_kd_tree_range_iterator;
	friend struct point_kd_tree_iteration;

	private:
	using _Node  = point_kd_tree_node<Key, Value, Info, SetMap, true>;
	using _Base  = point_kd_tree_node_base<_Node, Key, Value, Info, SetMap>;
	using _Key   = Key;
	using _Value = Value;
	using _Info  = Info;

	static constexpr bool _SetMap = SetMap, _Balanced = true;

	/* === Variables === */
	private:
	size_t _weight = 2;
	::__gnu_cxx::__aligned_membuf<Info> _info;
	/* === Variables === */

	/* === Constructor & Destructor === */
	private:
	point_kd_tree_node (_Base *up) : _Base(up) {}
	template <typename Node_Other>
	point_kd_tree_node (_Base *up, Node_Other *other) : _Base(up), _weight(other->_weight) {}
	/* === Constructor & Destructor === */

	/* === Print === */
	private:
	inline void print () const { printf("-%lu", _weight); }
	/* === Print === */
};

template <ushort K, typename Node, bool Multi, typename Comparator, typename Equal, typename Allocator>
struct point_kd_tree_base
{
	template <ushort, typename, bool, typename, typename, typename> friend struct point_kd_tree_base;

	private:
	using _Node = typename Node::_Base;

	using _Allocator         = typename ::std::allocator_traits<Allocator>::template rebind_alloc<Node>;
	using _ATraits           = typename ::std::allocator_traits<_Allocator>;
	using _Allocator_Pointer = typename ::std::allocator_traits<Allocator>::template rebind_alloc<_Node *>;
	using _ATraits_Pointer   = typename ::std::allocator_traits<_Allocator_Pointer>;

	using  _Traversor  = point_kd_tree_traversor<false, Node>;
	using _CTraversor  = point_kd_tree_traversor<true , Node>;

	using  _Range = point_kd_tree_range<false, Node, Allocator>;
	using _CRange = point_kd_tree_range<true , Node, Allocator>;

	using _Iteration = point_kd_tree_iteration;

	// Perhaps use ::std::disjunction for this
	template <typename T> static constexpr bool _is_traversor_v = ::std::is_same_v<T, _Traversor> ||
	                                                              ::std::is_same_v<T, _CTraversor>;
	template <typename T> static constexpr bool _is_non_const_traversor_v = ::std::is_same_v<T, _Traversor>;

	public:
	using        key_type = typename Node::_Key;
	using      value_type = typename Node::_Info;
	using       size_type = size_t;
	using difference_type = ::std::ptrdiff_t;
	using     key_compare = Comparator;
	using       key_equal = Equal;
	using  allocator_type = Allocator;
	using       reference =       value_type &;
	using const_reference = const value_type &;
	using         pointer =       value_type *;
	using   const_pointer = const value_type *;

	using       traversor =  _Traversor; using       iterator =  _Traversor;
	using const_traversor = _CTraversor; using const_iterator = _CTraversor;
	using       range =  _Range;
	using const_range = _CRange;


	/* === Variables === */
	private:
	Comparator _comparator;
	Equal _equal;
	_Allocator _allocator;
	_Allocator_Pointer _allocator_pointer;
	size_t _size = 0;
	_Node _head = _Node(nullptr);
	constexpr static double _factor = 0.2;
	/* === Variables === */


	/* ##################################################################### */
	/* ##################### Constructor & Destructor ###################### */
	/* === Default === */
	public:
	point_kd_tree_base (const Comparator &c = Comparator(), const Equal &e = Equal(), const Allocator &a = Allocator())
		: _comparator(c),            _equal(e),       _allocator(_Allocator(a)) { _reset_head(); }

	point_kd_tree_base (const Comparator &c,                                          const Allocator &a)
		: _comparator(c),            _equal(Equal()), _allocator(_Allocator(a)) { _reset_head(); }

	point_kd_tree_base (                                    const Equal &e,           const Allocator &a = Allocator())
		: _comparator(Comparator()), _equal(e),       _allocator(_Allocator(a)) { _reset_head(); }

	point_kd_tree_base (                                                              const Allocator &a)
		: _comparator(Comparator()), _equal(Equal()), _allocator(_Allocator(a)) { _reset_head(); }
	/* === Default === */


	/* === Range === */
	public:
	template <typename T1, typename T2>
	point_kd_tree_base (const T1 &first, const T2 &last,
	               const Comparator &c = Comparator(), const Equal &e = Equal(), const Allocator &a = Allocator())
		: _comparator(c),            _equal(e),       _allocator(_Allocator(a))
	{ _reset_head(); _construct_tree(first, last); }

	template <typename T1, typename T2>
	point_kd_tree_base (const T1 &first, const T2 &last,
	               const Comparator &c,                                          const Allocator &a)
		: _comparator(c),            _equal(Equal()), _allocator(_Allocator(a))
	{ _reset_head(); _construct_tree(first, last); }

	template <typename T1, typename T2>
	point_kd_tree_base (const T1 &first, const T2 &last,
	                                                   const Equal &e,           const Allocator &a = Allocator())
		: _comparator(Comparator()), _equal(e),       _allocator(_Allocator(a))
	{ _reset_head(); _construct_tree(first, last); }

	template <typename T1, typename T2>
	point_kd_tree_base (const T1 &first, const T2 &last,
	                                                                             const Allocator &a)
		: _comparator(Comparator()), _equal(Equal()), _allocator(_Allocator(a))
	{ _reset_head(); _construct_tree(first, last); }
	/* === Range === */


	/* === Copy === */
	public:
	point_kd_tree_base (const point_kd_tree_base &other)
		: _comparator(other._comparator), _equal(other._equal),
		  _allocator(_ATraits::select_on_container_copy_construction(other._allocator))
	{ _reset_head(); _copy_structure(other); }

	point_kd_tree_base (const point_kd_tree_base &other, const Comparator &c)
		: _comparator(c),                 _equal(other._equal),
		  _allocator(_ATraits::select_on_container_copy_construction(other._allocator))
	{ _reset_head(); _copy_structure(other); }

	point_kd_tree_base (const point_kd_tree_base &other,                      const Equal &e)
		: _comparator(other._comparator), _equal(e),
		  _allocator(_ATraits::select_on_container_copy_construction(other._allocator))
	{ _reset_head(); _copy_structure(other); }

	point_kd_tree_base (const point_kd_tree_base &other,                                      const Allocator &a)
		: _comparator(other._comparator), _equal(other._equal), _allocator(_Allocator(a))
	{ _reset_head(); _copy_structure(other); }

	point_kd_tree_base (const point_kd_tree_base &other, const Comparator &c, const Equal &e)
		: _comparator(c),                 _equal(e),
		  _allocator(_ATraits::select_on_container_copy_construction(other._allocator))
	{ _reset_head(); _copy_structure(other); }

	point_kd_tree_base (const point_kd_tree_base &other, const Comparator &c,                 const Allocator &a)
		: _comparator(c),                 _equal(other._equal), _allocator(_Allocator(a))
	{ _reset_head(); _copy_structure(other); }

	point_kd_tree_base (const point_kd_tree_base &other,                      const Equal &e, const Allocator &a)
		: _comparator(other._comparator), _equal(e),            _allocator(_Allocator(a))
	{ _reset_head(); _copy_structure(other); }

	point_kd_tree_base (const point_kd_tree_base &other, const Comparator &c, const Equal &e, const Allocator &a)
		: _comparator(c),                 _equal(e),            _allocator(_Allocator(a))
	{ _reset_head(); _copy_structure(other); }
	/* === Copy === */


	/* === Move === */
	public:
	point_kd_tree_base (point_kd_tree_base &&other)
		: _comparator(::std::move(other._comparator)), _equal(::std::move(other._equal)),
		  _allocator(::std::move(other._allocator))
	{ _reset_head(); _move_structure(::std::move(other)); other._reset(); }

	point_kd_tree_base (point_kd_tree_base &&other, const Comparator &c)
		: _comparator(c),                              _equal(::std::move(other._equal)),
		  _allocator(::std::move(other._allocator))
	{ _reset_head(); _move_structure(::std::move(other)); other._reset(); }

	point_kd_tree_base (point_kd_tree_base &&other,                      const Equal &e)
		: _comparator(::std::move(other._comparator)), _equal(e),
		  _allocator(::std::move(other._allocator))
	{ _reset_head(); _move_structure(::std::move(other)); other._reset(); }

	point_kd_tree_base (point_kd_tree_base &&other,                                      const Allocator &a)
		: _comparator(::std::move(other._comparator)), _equal(::std::move(other._equal)),
		  _allocator(_Allocator(a))
	{ _reset_head();
		if(_ATraits::is_always_equal::value || _allocator == other._allocator) {
			_move_structure(::std::move(other)); other._reset(); }
	    else { _copy_structure(other); other.clear(); } }

	point_kd_tree_base (point_kd_tree_base &&other, const Comparator &c, const Equal &e)
		: _comparator(c),                              _equal(e),
		  _allocator(::std::move(other._allocator))
	{ _reset_head(); _move_structure(::std::move(other)); other._reset(); }

	point_kd_tree_base (point_kd_tree_base &&other, const Comparator &c,                 const Allocator &a)
		: _comparator(c),                              _equal(::std::move(other._equal)),
		  _allocator(_Allocator(a))
	{ _reset_head();
		if(_ATraits::is_always_equal::value || _allocator == other._allocator) {
			_move_structure(::std::move(other)); other._reset(); }
	    else { _copy_structure(other); other.clear(); } }

	point_kd_tree_base (point_kd_tree_base &&other,                      const Equal &e, const Allocator &a)
		: _comparator(::std::move(other._comparator)), _equal(e),
		  _allocator(_Allocator(a))
	{ _reset_head();
		if(_ATraits::is_always_equal::value || _allocator == other._allocator) {
			_move_structure(::std::move(other)); other._reset(); }
	    else { _copy_structure(other); other.clear(); } }

	point_kd_tree_base (point_kd_tree_base &&other, const Comparator &c, const Equal &e, const Allocator &a)
		: _comparator(c),                              _equal(e),
		  _allocator(_Allocator(a))
	{ _reset_head();
		if(_ATraits::is_always_equal::value || _allocator == other._allocator) {
			_move_structure(::std::move(other)); other._reset(); }
	    else { _copy_structure(other); other.clear(); } }
	/* === Move === */


	/* === Initializer List === */
	public:
	point_kd_tree_base (const ::std::initializer_list<typename Node::_Info> &il,
	               const Comparator &c = Comparator(), const Equal &e = Equal(), const Allocator &a = Allocator())
		: _comparator(c),            _equal(e),       _allocator(_Allocator(a))
	{ _reset_head(); _construct_tree(il.begin(), il.end()); }

	point_kd_tree_base (const ::std::initializer_list<typename Node::_Info> &il,
	               const Comparator &c,                                          const Allocator &a)
		: _comparator(c),            _equal(Equal()), _allocator(_Allocator(a))
	{ _reset_head(); _construct_tree(il.begin(), il.end()); }

	point_kd_tree_base (const ::std::initializer_list<typename Node::_Info> &il,
	                                                   const Equal &e,           const Allocator &a = Allocator())
		: _comparator(Comparator()), _equal(e),       _allocator(_Allocator(a))
	{ _reset_head(); _construct_tree(il.begin(), il.end()); }

	point_kd_tree_base (const ::std::initializer_list<typename Node::_Info> &il,
	                                                                             const Allocator &a)
		: _comparator(Comparator()), _equal(Equal()), _allocator(_Allocator(a))
	{ _reset_head(); _construct_tree(il.begin(), il.end()); }
	/* === Initializer List === */


	/* === Destructor === */
	protected:
	~point_kd_tree_base () { if(_size > 0) _clear(); }
	/* === Destructor === */
	/* ##################### Constructor & Destructor ###################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ########################## Assign operator ########################## */
	/* === Copy === */
	public:
	point_kd_tree_base &
	operator =(const point_kd_tree_base &other)
	{ if(this != &other) { _prepare_copy(other); if(other._size > 0) _copy_structure(other); } return *this; }

	public:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info> &&
	                   (Multi || !Multi_Other) && (!Node::_Balanced || Node_Other::_Balanced), point_kd_tree_base &>
	operator= (const point_kd_tree_base<K, Node_Other, Multi_Other, Comparator, Equal, Allocator_Other> &other)
	{ _prepare_copy(other); if(other._size > 0) _copy_structure(other); return *this; }

	public:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, point_kd_tree_base &>
	operator= (const point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                                Comparator_Other, Equal_Other, Allocator_Other> &other)
	{ _prepare_copy(other); if(other._size > 0) _copy_nodes(other); return *this; }
	/* === Copy === */


	/* === Move === */
	public:
	point_kd_tree_base &
	operator= (point_kd_tree_base &&other)
	{
		if(this != &other) {
			if(_prepare_move(::std::move(other))) {
				 if(other._size > 0) { _move_structure(::std::move(other)); other._reset(); } }
			else if(other._size > 0) { _copy_structure(other);              other.clear();  } }
		return *this;
	}

	public:
	template <bool Multi_Other>
	::std::enable_if_t<Multi || !Multi_Other, point_kd_tree_base &>
	operator= (point_kd_tree_base<K, Node, Multi_Other, Comparator, Equal, Allocator> &&other)
	{
		if(_prepare_move(::std::move(other))) {
			 if(other._size > 0) { _move_structure(::std::move(other)); other._reset(); } }
		else if(other._size > 0) { _copy_structure(other);              other.clear();  }
		return *this;
	}

	public:
	template <ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other>
	point_kd_tree_base &
	operator= (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &&other)
	{
		if(_prepare_move(::std::move(other))) {
			 if(other._size > 0) { _move_nodes(::std::move(other)); other._reset(); } }
		else if(other._size > 0) { _copy_nodes(other);              other.clear();  }
		return *this;
	}

	public:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info> &&
	                   (Multi || !Multi_Other) && (!Node::_Balanced || Node_Other::_Balanced), point_kd_tree_base &>
	operator= (point_kd_tree_base<K, Node_Other, Multi_Other, Comparator, Equal, Allocator_Other> &&other)
	{ _prepare_move(::std::move(other)); if(other._size > 0) { _copy_structure(other); other.clear(); } return *this; }

	public:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, point_kd_tree_base &>
	operator= (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other> &&other)
	{ _prepare_move(::std::move(other)); if(other._size > 0) { _copy_nodes(other); other.clear(); } return *this; }
	/* === Move === */


	/* === Initializer List === */
	public:
	point_kd_tree_base &
	operator= (const ::std::initializer_list<typename Node::_Info> &il)
	{ clear(); insert(il); return *this; }
	/* === Initializer List === */
	/* ########################## Assign operator ########################## */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ####################### Comparison operators ######################## */
	/* === Equal === */
	public:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator== (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other> &other)
	{ return _equal_to(other); }

	public:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator== (const point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                                 Comparator_Other, Equal_Other, Allocator_Other> &other)
	const
	{ return _equal_to(other); }
	/* === Equal === */


	/* === Not Equal === */
	public:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator!= (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other> &other)
	{ return !_equal_to(other); }

	public:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator!= (const point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                                 Comparator_Other, Equal_Other, Allocator_Other> &other)
	const
	{ return !_equal_to(other); }
	/* === Not Equal === */
	/* ####################### Comparison operators ######################## */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################# Observers ############################# */
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

	inline  _Traversor  begin ()       { return  _Traversor(_head._down[1]); }
	inline _CTraversor  begin () const { return _CTraversor(_head._down[1]); }
	inline _CTraversor cbegin () const { return _CTraversor(_head._down[1]); }

	inline  _Traversor  end ()       { return  _Traversor(&_head); }
	inline _CTraversor  end () const { return _CTraversor(&_head); }
	inline _CTraversor cend () const { return _CTraversor(&_head); }
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
	::std::enable_if_t<!Multi && _is_traversor_v<T>, ::std::pair<T, bool>>
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
	::std::enable_if_t<!Multi && _is_traversor_v<T>, ::std::pair<T, bool>>
	insert (typename Node::_Info &&info)
	{
		if(!Replace) return _insert(::std::move(info));
		else {
			::std::pair<_Node *, bool> result = _insert(::std::move(info));
			if(!result.second) { _del_info(result.first); _new_info(result.first, ::std::move(info)); }
			return result; }
	}

	public:
	template <typename T = _Traversor>
	inline ::std::enable_if_t<Multi && _is_traversor_v<T>, T>
	insert (const typename Node::_Info &info)
	{ return _insert(info).first; }

	public:
	template <typename T = _Traversor>
	inline ::std::enable_if_t<Multi && _is_traversor_v<T>, T>
	insert (typename Node::_Info &&info)
	{ return _insert(::std::move(info)).first; }

	public:
	template <bool Replace = false, typename T1, typename T2>
	::std::enable_if_t<!Multi && Replace == Replace, size_t>
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
	template <typename T1, typename T2>
	::std::enable_if_t<Multi && ::std::is_same_v<T1, T1>, void>
	insert (const T1 &first, const T2 &last)
	{ if(_size == 0) _construct_tree(first, last); else for(T1 tr = first; tr != last; ++tr) _insert(*tr); }

	public:
	template <bool Replace = false>
	inline ::std::enable_if_t<!Multi && Replace == Replace, size_t>
	insert (const ::std::initializer_list<typename Node::_Info> &il)
	{ return insert<Replace>(il.begin(), il.end()); }

	public:
	template <int _ = 0>
	inline ::std::enable_if_t<Multi && _ == _, void>
	insert (const ::std::initializer_list<typename Node::_Info> &il)
	{ return insert(il.begin(), il.end()); }
	/* === Insert === */


	/* === Emplace === */
	public:
	template <bool Replace = false, typename T = _Traversor, typename... Args>
	::std::enable_if_t<!Multi && _is_traversor_v<T>, ::std::pair<T, bool>>
	emplace (Args&&... info)
	{
		_Node *node = _new_node(nullptr, ::std::forward<Args>(info)...);
		::std::pair<_Node *, bool> result = _emplace(node);
		if(!result.second) { if(Replace) { _del_info(result.first); _new_info(result.first, node->info()); }
		                     _del_node(node); }
		return result;
	}

	public:
	template <typename T = _Traversor, typename... Args>
	inline ::std::enable_if_t<Multi && _is_traversor_v<T>, T>
	emplace (Args&&... info)
	{ return _emplace(_new_node(nullptr, ::std::forward<Args>(info)...)).first; }

	public:
	template <typename T = _Traversor, typename... Args>
	::std::enable_if_t<!Multi && Node::_SetMap && _is_traversor_v<T>, ::std::pair<T, bool>>
	try_emplace (const typename Node::_Key &key, Args&&... value)
	{
		int side; _Node *place = _place(side, key);
		if(side == -1) return {place, false};
		return {_emplace_place(side, place, _new_node(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(key), ::std::forward_as_tuple(::std::forward<Args>(value)...))), true};
	}

	public:
	template <typename T = _Traversor, typename... Args>
	::std::enable_if_t<!Multi && Node::_SetMap && _is_traversor_v<T>, ::std::pair<T, bool>>
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
	template <bool _ = 0>
	::std::enable_if_t<!Multi && _ == _, bool>
	erase (const typename Node::_Key &key)
	{ _Node *node = _find(key); if(node == &_head) return false; _erase_(node, true); return true; }

	public:
	template <bool _ = 0>
	::std::enable_if_t<Multi && _ == _, size_t>
	erase (const typename Node::_Key &key)
	{
		_Range r = _equal_range(key);
		for(typename _Range::iterator it = r.begin(); it != r.end(); ++it) _erase(it.node(), true);
		return r.size();
	}

	public:
	template <typename T>
	inline ::std::enable_if_t<_is_non_const_traversor_v<T>, void>
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


	/* === Transfer === */
	public:
	template <bool Replace = false, typename TOut = _Traversor, ushort K_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename TIn>
	inline ::std::enable_if_t<!Multi && _is_traversor_v<TOut> &&
		point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator>::
		template _is_non_const_traversor_v<TIn>, ::std::pair<TOut, bool>>
	transfer (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other, const TIn &tr)
	{
		if(_ATraits::is_always_equal::value || _allocator == other._allocator)
			 return _transfer_move<Replace>(other, tr.node());
		else return _transfer_copy<Replace>(other, tr.node());
	}

	public:
	template <typename TOut = _Traversor, ushort K_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename TIn>
	inline ::std::enable_if_t<Multi && _is_traversor_v<TOut> &&
		point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator>::
		template _is_non_const_traversor_v<TIn>, TOut>
	transfer (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other, const TIn &tr)
	{
		if(_ATraits::is_always_equal::value || _allocator == other._allocator)
			 return TOut(_transfer_move(other, tr.node()));
		else return TOut(_transfer_copy(other, tr.node()));
	}

	public:
	template <bool Replace = false, typename TOut = _Traversor, ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other, typename TIn>
	inline ::std::enable_if_t<!Multi && ::std::is_same_v<typename Node::_Info, typename Node_Other::_Info> &&
	                          _is_traversor_v<TOut> &&
		point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other>::
		template _is_non_const_traversor_v<TIn>, ::std::pair<TOut, bool>>
	transfer (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other> &other,
		      const TIn &tr)
	{ return _transfer_copy<Replace>(other, tr.node()); }

	public:
	template <typename TOut = _Traversor, ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other, typename TIn>
	inline ::std::enable_if_t<Multi && ::std::is_same_v<typename Node::_Info, typename Node_Other::_Info> &&
	                          _is_traversor_v<TOut> &&
		point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other>::
		template _is_non_const_traversor_v<TIn>, TOut>
	transfer (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other> &other,
		      const TIn &tr)
	{ return TOut(_transfer_copy(other, tr.node())); }
	/* === Transfer === */


	/* === Merge === */
	public:
	template <bool Replace = false>
	inline ::std::enable_if_t<!Multi && Replace == Replace, size_t>
	merge (point_kd_tree_base &other)
	{
		if(this == &other || other._size == 0) return 0;
		if(_ATraits::is_always_equal::value || _allocator == other._allocator)
			 return _merge_move<Replace>(other);
		else return _merge_copy<Replace>(other);
	}

	public:
	template <int _ = 0>
	inline ::std::enable_if_t<Multi && _ == _, void>
	merge (point_kd_tree_base &other)
	{
		if(this == &other || other._size == 0) return;
		if(_ATraits::is_always_equal::value || _allocator == other._allocator)
			 _merge_move(other);
		else _merge_copy(other);
	}

	public:
	template <bool Replace = false, ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other>
	inline ::std::enable_if_t<!Multi && Replace == Replace, size_t>
	merge (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other)
	{
		if(other._size == 0) return 0;
		if(_ATraits::is_always_equal::value || _allocator == other._allocator)
			 return _merge_move<Replace>(other);
		else return _merge_copy<Replace>(other);
	}

	public:
	template <ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other>
	inline ::std::enable_if_t<Multi && Multi_Other == Multi_Other, void>
	merge (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other)
	{
		if(other._size == 0) return;
		if(_ATraits::is_always_equal::value || _allocator == other._allocator)
			 _merge_move(other);
		else _merge_copy(other);
	}

	public:
	template <bool Replace = false, ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	inline ::std::enable_if_t<!Multi && ::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, size_t>
	merge (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other> &other)
	{ if(other._size == 0) return 0; return _merge_copy<Replace>(other); }

	public:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	inline ::std::enable_if_t<Multi && ::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, void>
	merge (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other> &other)
	{ if(other._size > 0) _merge_copy(other); }
	/* === Merge === */


	/* === Swap === */
	public:
	void
	swap (point_kd_tree_base &other)
	{ if(this != &other) { if(_prepare_swap(other)) _swap_move_structure(other); else _swap_copy_structure(other); } }

	public:
	template <bool Multi_Other>
	void
	swap (point_kd_tree_base<K, Node, Multi_Other, Comparator, Equal, Allocator> &other)
	{
		if(_prepare_swap(other)) {
			if(Multi == Multi_Other) _swap_move_structure(other);
			else if(Multi)     _swap_move_structure_nodes(other);
			else         other._swap_move_structure_nodes(*this); }
		else {
			if(Multi == Multi_Other) _swap_copy_structure(other);
			else if(Multi)     _swap_copy_structure_nodes(other);
			else         other._swap_copy_structure_nodes(*this); }
	}

	public:
	template <ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other>
	void
	swap (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other)
	{ if(_prepare_swap(other)) _swap_move_nodes(other); else _swap_copy_nodes(other); }

	public:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, void>
	swap (point_kd_tree_base<K, Node_Other, Multi_Other, Comparator, Equal, Allocator_Other> &other)
	{
		_prepare_swap(other);
		if(Multi == Multi_Other) {
			if(Node::_Balanced == Node_Other::_Balanced) _swap_copy_structure(other);
			else if(!Node::_Balanced) _swap_copy_structure_nodes(other);
			else                other._swap_copy_structure_nodes(*this); }
		else if( Multi && (!Node::_Balanced || Node_Other::_Balanced))       _swap_copy_structure_nodes(other);
		else if(!Multi && (!Node_Other::_Balanced || Node::_Balanced)) other._swap_copy_structure_nodes(*this);
		else _swap_copy_nodes(other);
	}

	public:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, void>
	swap (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other> &other)
	{ _prepare_swap(other); _swap_copy_nodes(other); }
	/* === Swap === */


	/* === Balance === */
	public:
	inline void
	balance ()
	{ if(_size > 0) _construct_subtree(_head._up, 0); }

	public:
	template <typename T>
	::std::enable_if_t<_is_traversor_v<T>, void>
	balance (const T &tr)
	{
		if(tr.node()->_up == &_head) _construct_subtree(_head._up, 0);
		else _construct_subtree(tr.node()->_up->_down[tr.node() == tr.node()->_up->_down[1]], _get_d(tr.node()));
	}
	/* === Balance === */
	/* ############################# Modifiers ############################# */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ########################## Element Access ########################### */
	/* === Array subscript === */
	public:
	template <int _ = 0>
	::std::enable_if_t<!Multi && Node::_SetMap && _ == _, typename Node::_Value &>
	operator[] (const typename Node::_Key &key)
	{
		int side; _Node *place = _place(side, key);
		if(side == -1) return place->value();
		return _emplace_place(side, place, _new_node(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(key), ::std::tuple<>())).first->value();
	}

	public:
	template <int _ = 0>
	::std::enable_if_t<!Multi && Node::_SetMap && _ == _, typename Node::_Value &>
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
	::std::enable_if_t<!Multi && Node::_SetMap &&
		(::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>), typename Node::_Value &>
	at (const Key &key)
	{
		_Node *node = _find(key);
		if(node == &_head) throw ::std::out_of_range("point_kd_tree_map.at() out_of_range");
		return node->value();
	}

	public:
	template <typename Key>
	::std::enable_if_t<!Multi && Node::_SetMap &&
		(::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>), const typename Node::_Value &>
	at (const Key &key)
	const
	{
		const _Node *node = _find(key);
		if(node == &_head) throw ::std::out_of_range("point_kd_tree_map.at() out_of_range");
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
	::std::enable_if_t<!Multi && ::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, size_t>
	count (const Key &key)
	{ return !Multi ? _find(key) != &_head : _count(key); }

	public:
	template <typename Key>
	::std::enable_if_t<!Multi && ::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, size_t>
	count (const Key &key)
	const
	{ return !Multi ? _find(key) != &_head : _count(key); }
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
	template <typename T =  _Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && _is_traversor_v<T>, T>
	find (const Key &key)
	{ return T(_find(key)); }

	public:
	template <typename T =  _Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
	                          && _is_traversor_v<T>, T>
	find (const Key &key)
	const
	{ return T(_find(key)); }
	/* === Find === */


	/* === Equal range === */
	public:
	template <typename Key>
	inline ::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, _Range>
	equal_range (const Key &key)
	{ return _equal_range(key); }

	public:
	template <typename Key>
	inline ::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, _CRange>
	equal_range (const Key &key)
	const
	{ return _equal_range(key); }
	/* === Equal range === */


	/* === Nearest neighbour === */
	public:
	template <typename Measure, typename T = _Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
					   && _is_traversor_v<T>, ::std::pair<T, double>>
	nearest_neighbour (const Key &key, Measure &measure)
	{
		if(size == 0) return {&_head, 0};
		double distance = ::std::numeric_limits<double>::max(); _Node *node;
		_nearest_neighbour(key, measure, distance, node, 0, _head._up);
		return {node, distance};
	}

	public:
	template <typename Measure, typename T = _Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
					   && _is_traversor_v<T>, ::std::pair<T, double>>
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
					   && _is_traversor_v<T>, ::std::pair<T, double>>
	nearest_neighbour (const Key &key, const Measure &measure = Measure())
	{
		if(size == 0) return {&_head, 0};
		double distance = ::std::numeric_limits<double>::max(); _Node *node;
		_nearest_neighbour(key, measure, distance, node, 0, _head._up);
		return {node, distance};
	}

	public:
	template <typename Measure, typename T = _Traversor, typename Key>
	inline ::std::enable_if_t<(std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>)
					   && _is_traversor_v<T>, ::std::pair<T, double>>
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
	{ if(_size > 0) _print<Verbose>(printer, 0, 0, 0, _head._up, 0); }

	template <bool Verbose = false, typename Printer>
	inline void
	print (const Printer &printer = Printer()) const
	{ if(_size > 0) _print<Verbose>(printer, 0, 0, 0, _head._up, 0); }

	template <bool Verbose = false, typename Printer, typename T>
	inline ::std::enable_if_t<_is_traversor_v<T>, void>
	print (const T &tr, Printer &printer) const
	{ _print<Verbose>(printer, 0, 0, 0, tr._node, _get_d(tr.node())); }

	template <bool Verbose = false, typename Printer, typename T>
	inline ::std::enable_if_t<_is_traversor_v<T>, void>
	print (const T &tr, const Printer &printer = Printer()) const
	{ _print<Verbose>(printer, 0, 0, 0, tr._node, _get_d(tr.node())); }
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

	private:
	void
	_update_head ()
	{
		_Node *node;
		for(node = _head._up; node->_down[0] != nullptr; node = node->_down[0]) {} _head._down[1] = node;
		for(node = _head._up; node->_down[1] != nullptr; node = node->_down[1]) {} _head._down[0] = node;
	}
	/* === Head === */


	/* === Node === */
	private:
	template <typename... Args>
	_Node *
	_new_node (_Node *up, Args&&... info)
	{
		++_size; Node *node = _ATraits::allocate(_allocator, 1);
		:: new(node) Node(up); _new_info(node, ::std::forward<Args>(info)...);
		return node;
	}

	private:
	template <typename _Node_Other>
	_Node *
	_new_node_copy (_Node *up, _Node_Other *node_other)
	{
		++_size; Node *node = _ATraits::allocate(_allocator, 1);
		:: new(node) Node(up, node_other->cast()); _new_info(node, node_other->info());
		return node;
	}

	private:
	void
	_del_node (_Node *node)
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
	/* ##################### External Tree Management ###################### */
	/* === Preprocessing === */
	private:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	void
	_prepare_copy (const point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                                    Comparator_Other, Equal_Other, Allocator_Other> &other)
	{ clear(); _copy_comparator(other._comparator); _copy_equal(other._equal); _copy_allocator(other._allocator); }

	private:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	bool
	_prepare_move (point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                              Comparator_Other, Equal_Other, Allocator_Other> &&other)
	{
		clear(); _move_comparator(::std::move(other._comparator)); _move_equal(::std::move(other._equal));
		return _move_allocator(::std::move(other._allocator));
	}

	private:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	bool
	_prepare_swap (point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                              Comparator_Other, Equal_Other, Allocator_Other> &other)
	{ _swap_comparator(other._comparator); _swap_equal(other._equal); return _swap_allocator(other._allocator); }
	/* === Preprocessing === */


	/* === Comparator === */
	private:
	inline void _copy_comparator (const Comparator  &comparator_other) { _comparator = comparator_other;              }
	inline void _move_comparator (      Comparator &&comparator_other) { _comparator = ::std::move(comparator_other); }
	inline void _swap_comparator (      Comparator  &comparator_other) { ::std::swap(_comparator, comparator_other);  }

	template <typename Comparator_Other> constexpr void _copy_comparator (const Comparator_Other  &) {}
	template <typename Comparator_Other> constexpr void _move_comparator (      Comparator_Other &&) {}
	template <typename Comparator_Other> constexpr void _swap_comparator (      Comparator_Other  &) {}
	/* === Comparator === */


	/* === Equal === */
	private:
	inline void _copy_equal (const Equal  &equal_other) { _equal = equal_other;              }
	inline void _move_equal (      Equal &&equal_other) { _equal = ::std::move(equal_other); }
	inline void _swap_equal (      Equal  &equal_other) { ::std::swap(_equal, equal_other);  }

	template <typename Equal_Other> constexpr void _copy_equal (const Equal_Other  &) {}
	template <typename Equal_Other> constexpr void _move_equal (      Equal_Other &&) {}
	template <typename Equal_Other> constexpr void _swap_equal (      Equal_Other  &) {}
	/* === Equal === */


	/* === Allocator === */
	private:
	inline void
	_copy_allocator (const Allocator &other)
	{ if(_ATraits::propagate_on_container_copy_assignment::value) _allocator = other._allocator; }

	private:
	inline bool
	_move_allocator (Allocator &&other)
	{
		if(_ATraits::propagate_on_container_move_assignment::value) {
			_allocator = ::std::move(other._allocator); return true; }
		else return _ATraits::is_always_equal::value || _allocator == other._allocator;
	}

	private:
	inline bool
	_swap_allocator (Allocator &other)
	{
		if(_ATraits::propagate_on_container_swap::value) { ::std::swap(_allocator, other._allocator); return true; }
		else return _ATraits::is_always_equal::value || _allocator == other._allocator;
	}

	private:
	template <typename Allocator_Other> constexpr void _copy_allocator (const Allocator_Other  &) {}
	template <typename Allocator_Other> constexpr bool _move_allocator (      Allocator_Other &&) { return false; }
	template <typename Allocator_Other> constexpr bool _swap_allocator (      Allocator_Other  &) { return false; }
	/* === Allocator === */


	/* === Copy === */
	private:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	inline void
	_copy_structure (const point_kd_tree_base<K, Node_Other, Multi_Other, Comparator, Equal, Allocator_Other> &other)
	{ _copy_structure_routine(other._head._up); }

	private:
	template <typename _Node_Other>
	void
	_copy_structure_routine (const _Node_Other *root_other)
	{ _head._up = _new_node_copy(&_head, root_other); _copy_structure_routine(_head._up, root_other); _update_head(); }

	private:
	template <typename _Node_Other>
	void
	_copy_structure_routine (_Node *node, _Node_Other *node_other)
	{
		for( ; ; node = node->_down[1], node_other = node_other->_down[1]) {
			if(node_other->_down[0] != nullptr) { node->_down[0] = _new_node_copy(node, node_other->_down[0]);
				_copy_structure_routine(node->_down[0], node_other->_down[0]); }
			if(node_other->_down[1] != nullptr)   node->_down[1] = _new_node_copy(node, node_other->_down[1]);
			else return; }
	}

	private:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	inline void
	_copy_nodes (const point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                                  Comparator_Other, Equal_Other, Allocator_Other> &other)
	{ _copy_nodes_routine(other._head._up, other._size); }

	private:
	template <typename _Node_Other>
	void
	_copy_nodes_routine (_Node_Other *root_other, size_t size_other)
	{
		_Node **nodes = _ATraits_Pointer::allocate(_allocator_pointer, size_other + 1);
		size_t size = 0; _flatten_subtree_copy(nodes, size, root_other);
		if(!Multi) size = _remove_duplicates(nodes, size);
		_head._up = _construct_routine<true>(&_head, nodes, 0, 0, size - 1);
		_ATraits_Pointer::deallocate(_allocator_pointer, nodes, size_other + 1);
		_update_head();
	}
	/* === Copy === */


	/* === Move === */
	private:
	template <bool Multi_Other>
	void
	_move_structure (point_kd_tree_base<K, Node, Multi_Other, Comparator, Equal, Allocator> &&other)
	{ _size = other._size; other._head._up->_up = &_head; _head = ::std::move(other._head); }

	private:
	template <ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other>
	inline void
	_move_nodes (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &&other)
	{ _move_nodes_routine(other._head._up, other._size); }

	private:
	void
	_move_nodes_routine (_Node *root_other, size_t size_other)
	{
		_Node **nodes = _ATraits_Pointer::allocate(_allocator_pointer, size_other + 1);
		size_t size = 0; _flatten_subtree(nodes, size, root_other);
		if(!Multi) size = _remove_duplicates(nodes, size);
		_head._up = _construct_routine<false>(&_head, nodes, 0, 0, size - 1);
		_ATraits_Pointer::deallocate(_allocator_pointer, nodes, size_other + 1);
		_update_head();
	}
	/* === Move === */


	/* === Swap === */
	private:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	void
	_swap_copy_structure (point_kd_tree_base<K, Node_Other, Multi_Other, Comparator, Equal, Allocator_Other> &other)
	{
		if(_size == 0) { if(other._size > 0) { _copy_structure(other); other.clear(); } return; }
		else      if(other._size == 0) { other._copy_structure(*this);       clear();   return; }

		_Node                      *root       =       _head._up;       _reset_head();
		typename Node_Other::_Base *root_other = other._head._up; other._reset_head();
		      _copy_structure_routine(root_other);
		other._copy_structure_routine(root);
		_clear(root); other._clear(root_other);
	}

	private:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	void
	_swap_copy_structure_nodes (point_kd_tree_base<K, Node_Other, Multi_Other, Comparator, Equal, Allocator_Other> &other)
	{
		if(_size == 0) { if(other._size > 0) { _copy_structure(other); other.clear(); } return; }
		else      if(other._size == 0) { other._copy_nodes    (*this);       clear();   return; }

		_Node                      *root       =       _head._up;       _reset_head(); size_t size = _size;
		typename Node_Other::_Base *root_other = other._head._up; other._reset_head();
		      _copy_structure_routine(root_other);
		other._copy_nodes_routine(root, size);
		_clear(root); other._clear(root_other);
	}

	private:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	void
	_swap_copy_nodes (point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                                 Comparator_Other, Equal_Other, Allocator_Other> &other)
	{
		if(_size == 0) { if(other._size > 0) { _copy_nodes(other); other.clear(); } return; }
		else      if(other._size == 0) { other._copy_nodes(*this);       clear();   return; }

		_Node                      *root       =       _head._up;       _reset_head(); size_t size = _size;
		typename Node_Other::_Base *root_other = other._head._up; other._reset_head();
		      _copy_nodes_routine(root_other, other._size);
		other._copy_nodes_routine(root, size);
		_clear(root); other._clear(root_other);
	}

	private:
	template <bool Multi_Other>
	void
	_swap_move_structure (point_kd_tree_base<K, Node, Multi_Other, Comparator, Equal, Allocator> &other)
	{
		:: std::swap(_size, other._size);
		:: std::swap(_head._up->_up, other._head._up->_up);
		:: std::swap(_head, other._head);
	}

	private:
	template <bool Multi_Other>
	void
	_swap_move_structure_nodes (point_kd_tree_base<K, Node, Multi_Other, Comparator, Equal, Allocator> &other)
	{
		if(_size == 0) { if(other._size > 0) { _move_structure(::std::move(other)); other._reset(); } return; }
		else      if(other._size == 0) { other._move_nodes    (::std::move(*this));       _reset();   return; }

		_Node *root = _head._up; size_t size = _size;
		_move_structure(::std::move(other));
		other._size = size; other._reset_head(); other._move_nodes_routine(root, size);
	}

	private:
	template <ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other>
	void
	_swap_move_nodes (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other)
	{
		if(_size == 0) { if(other._size > 0) { _move_nodes(::std::move(other)); other._reset(); } return; }
		else      if(other._size == 0) { other._move_nodes(::std::move(*this));       _reset();   return; }

		_Node *root = _head._up, *root_other = other._head._up; _reset_head(); other._reset_head();
		:: std::swap(_size, other._size);
		      _move_nodes_routine(root_other, _size);
		other._move_nodes_routine(root, other._size);
	}
	/* === Swap === */


	/* === Transfer === */
	private:
	template <bool Replace, ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other,
	          bool _ = !Multi, typename = ::std::enable_if_t<_>>
	::std::pair<_Node *, bool>
	_transfer_move (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other,
		            _Node *node_other)
	{
		int side; _Node *place = _place(side, **node_other);
		if(side == -1) {
			if(Replace) { _del_info(place); _new_info(place, node_other->info()); other._erase(node_other, true); }
		    return {place, false}; }
		other._erase(node_other, false); --other._size;
		_reset_node(node_other); return _emplace_place(side, place, node_other);
	}

	private:
	template <ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other,
	          bool _ = !Multi, typename = ::std::enable_if_t<_>>
	_Node *
	_transfer_move (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other,
		            _Node *node_other)
	{ other._erase(node_other, false); --other._size; _reset_node(node_other); return _emplace(node_other).first; }

	private:
	template <bool Replace, ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other,
	          bool _ = !Multi, typename = ::std::enable_if_t<_>>
	::std::pair<_Node *, bool>
	_transfer_copy (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other>
		            &other, typename Node_Other::_Base *node_other)
	{
		::std::pair<_Node *, bool> result = _insert(node_other->info());
		if(result.second) other._erase(node_other, true);
		else if(Replace) {
			_del_info(result.first); _new_info(result.first, node_other->info()); other._erase_(node_other, true); }
		return result;
	}

	private:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other,
	          bool _ = Multi, typename = ::std::enable_if_t<_>>
	_Node *
	_transfer_copy (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other>
					&other, typename Node_Other::_Base *node_other)
	{ _Node *node = _insert(node_other->info()).first; other._erase(node_other, true); return node; }
	/* === Transfer === */


	/* === Merge === */
	private:
	template <bool Replace, bool Multi_Other, typename = ::std::enable_if_t<!Multi && !Multi_Other>>
	size_t
	_merge_move (point_kd_tree_base<K, Node, Multi_Other, Comparator, Equal, Allocator> &other)
	{
		if(_size == 0) { _move_structure(::std::move(other)); other._reset(); return _size; }
		size_t count = 0; return _merge_move_routine<Replace>(other, other._head._up, count); return count;
	}

	private:
	template <bool Multi_Other, bool _ = Multi, typename = ::std::enable_if_t<_>>
	void
	_merge_move (point_kd_tree_base<K, Node, Multi_Other, Comparator, Equal, Allocator> &other)
	{
		if(_size == 0) { _move_structure(::std::move(other)); other._reset(); }
		else _merge_move_routine(other, other._head._up);
	}

	private:
	template <bool Replace, ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other,
	          bool _ = !Multi, typename = ::std::enable_if_t<_>>
	size_t
	_merge_move (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other)
	{
		if(_size == 0) { _move_nodes(::std::move(other)); other._reset(); return _size; }
		size_t count = 0; return _merge_move_routine<Replace>(other, other._head._up, count); return count;
	}

	private:
	template <ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other,
	          bool _ = Multi, typename = ::std::enable_if_t<_>>
	void
	_merge_move (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other)
	{
		if(_size == 0) { _move_nodes(::std::move(other)); other._reset(); }
		else _merge_move_routine(other, other._head._up);
	}

	private:
	template <bool Replace, ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other,
	          bool _ = !Multi, typename = ::std::enable_if_t<_>>
	size_t
	_merge_move_routine (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other,
	                     _Node *node_other, size_t &count)
	{
		if(node_other->_down[0] != nullptr) _merge_move_routine(other, node_other->_down[0], count);
		if(node_other->_down[1] != nullptr) _merge_move_routine(other, node_other->_down[1], count);
		count += _transfer_move<Replace>(other, node_other).second;
		return count;
	}

	private:
	template <ushort K_Other, bool Multi_Other, typename Comparator_Other, typename Equal_Other,
	          bool _ = Multi, typename = ::std::enable_if_t<_>>
	void
	_merge_move_routine (point_kd_tree_base<K_Other, Node, Multi_Other, Comparator_Other, Equal_Other, Allocator> &other,
	                     _Node *node_other)
	{
		if(node_other->_down[0] != nullptr) _merge_move_routine(other, node_other->_down[0]);
		if(node_other->_down[1] != nullptr) _merge_move_routine(other, node_other->_down[1]);
		_transfer_move(other, node_other);
	}

	private:
	template <bool Replace, typename Node_Other, bool Multi_Other, typename Allocator_Other, typename =
	          ::std::enable_if_t<!Multi && !Multi_Other && (!Node::_Balanced || Node_Other::_Balanced)>>
	size_t
	_merge_copy (point_kd_tree_base<K, Node_Other, Multi_Other, Comparator, Equal, Allocator_Other> &other)
	{
		if(_size == 0) { _copy_structure(other); other.renew(); return _size; }
		return _merge_copy_routine<Replace>(other);
	}

	private:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other, typename =
	          ::std::enable_if_t<Multi && (!Node::_Balanced || Node_Other::_Balanced)>>
	void
	_merge_copy (point_kd_tree_base<K, Node_Other, Multi_Other, Comparator, Equal, Allocator_Other> &other)
	{ if(_size == 0) { _copy_structure(other); other.renew(); } else _merge_copy_routine(other); }

	private:
	template <bool Replace, ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other,
	          bool _ = !Multi, typename = ::std::enable_if_t<_>>
	size_t
	_merge_copy (point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                            Comparator_Other, Equal_Other, Allocator_Other> &other)
	{
		if(_size == 0) { _copy_nodes(other); other.renew(); return _size; }
		return _merge_copy_routine<Replace>(other);
	}

	private:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other,
	          bool _ = Multi, typename = ::std::enable_if_t<_>>
	void
	_merge_copy (point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                            Comparator_Other, Equal_Other, Allocator_Other> &other)
	{ if(_size == 0) { _copy_nodes(other); other.renew(); } else _merge_copy_routine(other); }

	private:
	template <bool Replace, ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other,
	          bool _ = !Multi, typename = ::std::enable_if_t<_>>
	size_t
	_merge_copy_routine (point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                                    Comparator_Other, Equal_Other, Allocator_Other> &other)
	{
		size_t count = 0;
		for(typename Node_Other::_Base *node1 = other._begin(), *node2; node1 != &other._head; node1 = node2) {
			node2 = _Iteration::_<1>(node1); count += _transfer_copy<Replace>(other, node1).second; }
		return count;
	}

	private:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other,
	          bool _ = Multi, typename = ::std::enable_if_t<_>>
	void
	_merge_copy_routine (point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                                    Comparator_Other, Equal_Other, Allocator_Other> &other)
	{
		for(typename Node_Other::_Base *node1 = other._begin(), *node2; node1 != &other._head; node1 = node2) {
			node2 = _Iteration::_<1>(node1); _transfer_copy(other, node1).second; }
	}
	/* === Merge === */
	/* ##################### External Tree Management ###################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ####################### Comparison operators ######################## */
	/* === Equal === */
	private:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	bool
	_equal_to (point_kd_tree_base<K_Other, Node_Other, Multi_Other, Comparator_Other, Equal_Other, Allocator_Other> &other)
	{
		if(_size != other._size) return false;
		for(_Node *node = _head._down[1]; node != &_head; node = _Iteration::_<1>(node))
			if(_count(**node) != other._count(**node)) return false;
		return true;
	}

	private:
	template <ushort K_Other, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Equal_Other, typename Allocator_Other>
	bool
	_equal_to (const point_kd_tree_base<K_Other, Node_Other, Multi_Other,
		                                Comparator_Other, Equal_Other, Allocator_Other> &other)
	const
	{
		if(_size != other._size) return false;
		for(const _Node *node = _head._down[1]; node != &_head; node = _Iteration::_<1>(node))
			if(_count(**node) != other._count(**node)) return false;
		return true;
	}
	/* === Equal === */
	/* ####################### Comparison operators ######################## */
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
		for(_Node *save; ; node = save) {
			if(node->_down[0] != nullptr) _clear_routine(node->_down[0]);
			save = node->_down[1];
			_del_node(node);
			if(save == nullptr) return; }
	}
	/* === Clear === */


	/* === Place === */
	private:
	_Node *
	_place (int &side, const typename Node::_Key &key)
	{
		if(_head._up == nullptr) { side = 0; return &_head; }
		_Node *node = _head._up;
		for(ushort d = 0; ; d = (d + 1) % K) {
			if(!Multi && _equal(key, **node)) { side = -1; return node; }
			if(_comparator(d, key, **node))
				 { if(node->_down[0] != nullptr) node = node->_down[0]; else { side = 0; return node; } }
			else { if(node->_down[1] != nullptr) node = node->_down[1]; else { side = 1; return node; } } }
	}

	private:
	const _Node *
	_place (int &side, const typename Node::_Key &key)
	const
	{
		if(_head._up == nullptr) { side = 0; return &_head; }
		const _Node *node = _head._up;
		for(ushort d = 0; ; d = (d + 1) % K) {
			if(!Multi && _equal(**node, key)) { side = -1; return node; }
			if(_comparator(d, key, **node))
				 { if(node->_down[0] != nullptr) node = node->_down[0]; else { side = 0; return node; } }
			else { if(node->_down[1] != nullptr) node = node->_down[1]; else { side = 1; return node; } } }
	}
	/* === Place === */


	/* === Insert === */
	private:
	template <typename Arg, typename = ::std::enable_if_t<!Node::_Balanced>>
	::std::pair<_Node *, bool>
	_insert (Arg &&info)
	{
		int side; _Node *place = _place(side, _Node::key(::std::forward<Arg>(info)));
		if(!Multi && side == -1) return {place, false};
		else                     return {_insert_place(side, place, ::std::forward<Arg>(info)), true};
	}

	private:
	template <typename Arg, typename = ::std::enable_if_t<Node::_Balanced>, typename = void>
	::std::pair<_Node *, bool>
	_insert (Arg &&info)
	{
		int side; _Node *node = _place(side, _Node::key(::std::forward<Arg>(info)));
		if(!Multi && side == -1) return {node, false};
		else { node = _insert_place(side, node, ::std::forward<Arg>(info)); _balance_insert(node); return {node, true}; }
	}

	protected:
	template <typename Arg>
	_Node *
	_insert_place (int side, _Node *place, Arg &&info)
	{
		if(place == &_head) {
			_head._up = _new_node(&_head, ::std::forward<Arg>(info));
			_head._down[0] = _head._up; _head._down[1] = _head._up;
			return _head._up; }
		if(side == 0) {
			_Node *node = _new_node(place, ::std::forward<Arg>(info)); place->_down[0] = node;
			if(_head._down[1] == place) _head._down[1] = node;
			return node; }
		else {
			_Node *node = _new_node(place, ::std::forward<Arg>(info)); place->_down[1] = node;
			if(_head._down[0] == place) _head._down[0] = node;
			return node; }
	}
	/* === Insert === */


	/* === Emplace === */
	private:
	template <typename = ::std::enable_if_t<!Node::_Balanced>>
	::std::pair<_Node *, bool>
	_emplace (_Node *node)
	{
		int side; _Node *place = _place(side, **node);
		if(!Multi && side == -1) return {place, false};
		else { _emplace_place(side, place, node); return {node, true}; }
	}

	private:
	template <typename = ::std::enable_if_t<Node::_Balanced>, typename = void>
	::std::pair<_Node *, bool>
	_emplace (_Node *node)
	{
		int side; _Node *place = _place(side, **node);
		if(!Multi && side == -1) return {place, false};
		else { _emplace_place(side, place, node); _balance_insert(node); return {node, true}; }
	}

	protected:
	void
	_emplace_place (int side, _Node *place, _Node *node)
	{
		if(place == &_head) {
			_head._up = node; node->_up = &_head;
			_head._down[0] = node; _head._down[1] = node; }
		if(side == 0) {
			place->_down[0] = node; node->_up = place;
			if(_head._down[1] == place) _head._down[1] = node; }
		else {
			place->_down[1] = node; node->_up = place;
			if(_head._down[0] == place) _head._down[0] = node; }
	}
	/* === Emplace === */


	/* === Erase === */
	private:
	template <typename = ::std::enable_if_t<!Node::_Balanced>>
	inline void
	_erase (_Node *node, const bool del)
	{ _erase_node(node, _get_d(node), del); }

	private:
	template <typename = ::std::enable_if_t<Node::_Balanced>, typename = void>
	inline void
	_erase (_Node *node, const bool del)
	{ node = _erase_node(node, _get_d(node), del); if(node != &_head) _balance_erase(node); }

	private:
	_Node *
	_erase_node (_Node *node, ushort d, const bool del)
	{
		_Node *parent;
		if(node->_down[0] == nullptr && node->_down[1] == nullptr) {
			parent = node->_up; _remove_leaf(node, del); return parent; }
		bool side = _replacement_side(node);
		_Node *replacement = node->_down[side];
		ushort replacement_d = (d + 1) % K;
		if(node->_down[side]->_down[side^1] != nullptr)
			_find_replacement(side, d, node->_down[side]->_down[side^1], (d + 2) % K, replacement, replacement_d);
		if(K >= 2 && node->_down[side]->_down[side] != nullptr)
			_find_replacement(side, d, node->_down[side]->_down[side  ], (d + 2) % K, replacement, replacement_d);
		parent = _erase_node(replacement, replacement_d, false);
		if(parent == node) parent = replacement;
		_replace_node(node, replacement, del);
		return parent;
	}

	private:
	template <typename = ::std::enable_if_t<!Node::_Balanced>>
	inline bool
	_replacement_side (const _Node *node)
	const
	{ return node->_down[0] == nullptr; }

	private:
	template <typename = ::std::enable_if_t<Node::_Balanced>, typename = void>
	inline bool
	_replacement_side (const _Node *node)
	const
	{
		return (node->_down[1] != nullptr ? node->_down[1]->cast()->_weight : 1) >
			   (node->_down[0] != nullptr ? node->_down[0]->cast()->_weight : 1);
	}

	private:
	void
	_find_replacement (bool side, ushort d, _Node *node, ushort node_d, _Node *&replacement, ushort &replacement_d)
	{
		if(side == 0) { if(_comparator(d, **replacement, **node)) { replacement = node; replacement_d = node_d; } }
		else          { if(_comparator(d, **node, **replacement)) { replacement = node; replacement_d = node_d; } }
		if(node->_down[side^1] != nullptr)
			_find_replacement(side, d, node->_down[side^1], (node_d + 1) % K, replacement, replacement_d);
		if(node_d != d && node->_down[side] != nullptr)
			_find_replacement(side, d, node->_down[side  ], (node_d + 1) % K, replacement, replacement_d);
	}
	/* === Erase === */
	/* ############################# Modifiers ############################# */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################## Balance ############################## */
	/* === Insert === */
	private:
	template <typename = ::std::enable_if_t<Node::_Balanced>>
	void
	_balance_insert (_Node *node)
	{
		ushort depth = 0;
		_Node *parent = node->_up, *save = nullptr;
		for( ; parent != &_head; node = parent, parent = parent->_up, ++depth) {
			++parent->cast()->_weight;
			if(parent->cast()->_weight - node->cast()->_weight < _factor * parent->cast()->_weight) {
				save = parent; depth = 0; } }
		if(save != nullptr) {
			if(save->_up == &_head) _construct_subtree(_head._up, 0);
			else _construct_subtree(save->_up->_down[save == save->_up->_down[1]], (depth - 1) % K); }
	}
	/* === Insert === */


	/* === Erase === */
	private:
	template <typename = ::std::enable_if_t<Node::_Balanced>>
	void
	_balance_erase (_Node *parent)
	{
		ushort depth = 0;
		_Node *node = nullptr, *save = nullptr;
		for( ; parent != &_head; node = parent, parent = parent->_up, ++depth) {
			--parent->cast()->_weight;
			if((node != nullptr ? node->cast()->_weight : 1) < _factor * parent->cast()->_weight) {
				save = parent; depth = 0; } }
		if(save != nullptr) {
			if(save->_up == &_head) _construct_subtree(_head._up, 0);
			else _construct_subtree(save->_up->_down[save == save->_up->_down[1]], (depth - 1) % K); }
	}
	/* === Erase === */
	/* ############################## Balance ############################## */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ########################## Tree Structure ########################### */
	private:
	ushort
	_get_d (const _Node *node)
	const
	{ ushort depth = 0; for(node = node->_up; node != &_head; node = node->_up, ++depth) {} return depth % K; }

	private:
	void
	_remove_leaf (_Node *node, const bool del)
	{
		if(node->_up == &_head)                  _head._up = nullptr;
		else node->_up->_down[node == node->_up->_down[1]] = nullptr;
		if(_head._down[0] == node) _head._down[0] = node->_up;
		if(_head._down[1] == node) _head._down[1] = node->_up;
		if(del) _del_node(node);
	}

	private:
	void
	_replace_node (_Node *node1, _Node *node2, const bool del)
	{
		if(Node::_Balanced) _replace_weight(node1, node2);
		node2->_up = node1->_up;
		node2->_down[0] = node1->_down[0];
		node2->_down[1] = node1->_down[1];
		if(node1->_up == &_head)                    _head._up = node2;
		else node1->_up->_down[node1 == node1->_up->_down[1]] = node2;
		if(node1->_down[0] != nullptr) node1->_down[0]->_up = node2;
		if(node1->_down[1] != nullptr) node1->_down[1]->_up = node2;
		if(_head._down[0] == node1) _head._down[0] = node2;
		if(_head._down[1] == node1) _head._down[1] = node2;
		if(del) _del_node(node1);
	}

	private:
	template <typename = ::std::enable_if_t<!Node::_Balanced>>
	constexpr void
	_replace_weight (_Node *, _Node *) {}

	private:
	template <typename = ::std::enable_if_t<Node::_Balanced>, typename = void>
	void
	_replace_weight (_Node *node1, _Node *node2)
	{ node2->cast()->_weight = node1->cast()->_weight; }
	/* ########################## Tree Structure ########################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################# Construct ############################# */
	/* === Tree === */
	private:
	template <typename T1, typename T2>
	void
	_construct_tree (const T1 &first, const T2 &last)
	{
		size_t i = 0, size = ::std::distance(first, last);
		_Node **nodes = _ATraits_Pointer::allocate(_allocator_pointer, size + 1);
		for(T1 tr = first; i < size; ++i, ++tr) nodes[i] = _new_node(nullptr, *tr);
		if(!Multi) size = _remove_duplicates(nodes, size);
		_head._up = _construct_routine<true>(&_head, nodes, 0, 0, size - 1);
		_ATraits_Pointer::deallocate(_allocator_pointer, nodes, size + 1);
		_update_head();
	}
	/* === Tree === */


	/* === Subtree === */
	private:
	void
	_construct_subtree (_Node *&subroot, ushort d)
	{
		size_t size = _subtree_size(subroot);
		_Node **nodes = _ATraits_Pointer::allocate(_allocator_pointer, size + 1);
		size_t index = 0; _flatten_subtree(nodes, index, subroot);
		subroot = _construct_routine<false>(subroot->_up, nodes, d, 0, size - 1);
		_ATraits_Pointer::deallocate(_allocator_pointer, nodes, size + 1);
		_update_head();
	}

	private:
	template <typename = ::std::enable_if_t<!Node::_Balanced>>
	size_t
	_subtree_size (const _Node *node)
	const
	{
		size_t size = 1;
		if(node->_down[0] != nullptr) size += _subtree_size(node->_down[0]);
		if(node->_down[1] != nullptr) size += _subtree_size(node->_down[1]);
		return size;
	}

	private:
	template <typename = ::std::enable_if_t<Node::_Balanced>, typename = void>
	inline size_t
	_subtree_size (const _Node *node)
	const
	{ return node->cast()->_weight - 1; }
	/* === Subtree === */


	/* === Auxiliary === */
	private:
	void
	_flatten_subtree (_Node **nodes, size_t &index, _Node *node)
	const
	{
		nodes[index] = node; ++index;
		if(node->_down[0] != nullptr) _flatten_subtree(nodes, index, node->_down[0]);
		if(node->_down[1] != nullptr) _flatten_subtree(nodes, index, node->_down[1]);
	}

	private:
	template <typename Node_Other>
	void
	_flatten_subtree_copy (_Node **nodes, size_t &index, Node_Other *node)
	{
		nodes[index] = _new_node_copy(nullptr, node); ++index;
		if(node->_down[0] != nullptr) _flatten_subtree_copy(nodes, index, node->_down[0]);
		if(node->_down[1] != nullptr) _flatten_subtree_copy(nodes, index, node->_down[1]);
	}

	private:
	size_t
	_remove_duplicates (_Node **nodes, size_t size)
	{
		:: std::sort(nodes, &nodes[size], [this](_Node *a, _Node *b) {
			for(ushort d = 0; d < K; ++d) {
				if(_comparator(d, **a, **b)) return true;
				if(_comparator(d, **b, **a)) return false; }
			return false; });
		return size - (&nodes[size] - ::std::unique(nodes, &nodes[size], [this](_Node *a, _Node *b) {
			if(_equal(**a, **b)) { _del_node(b); return true; } return false; }));
	}

	private:
	template <bool New, typename = ::std::enable_if_t<!Node::_Balanced>>
	_Node *
	_construct_routine (_Node *node, _Node **nodes, ushort d, size_t first, size_t last)
	{
		:: std::sort(&nodes[first], &nodes[last + 1], [d, this](_Node *a, _Node *b) { return _comparator(d, **a, **b); });
		size_t median = (first + last + 1) >> 1;
		for( ; median > first && !_comparator(d, **nodes[median - 1], **nodes[median]); --median) {}
		nodes[median]->_up = node;
		if(median != first) {
			nodes[median]->_down[0] = _construct_routine<New>(nodes[median], nodes, (d + 1) % K, first, median - 1); }
		else if(!New) nodes[median]->_down[0] = nullptr;
		if(median != last)  {
			nodes[median]->_down[1] = _construct_routine<New>(nodes[median], nodes, (d + 1) % K, median + 1, last ); }
		else if(!New) nodes[median]->_down[1] = nullptr;
		return nodes[median];
	}

	private:
	template <bool New, typename = ::std::enable_if_t<Node::_Balanced>, typename = void>
	_Node *
	_construct_routine (_Node *node, _Node **nodes, ushort d, size_t first, size_t last)
	{
		:: std::sort(&nodes[first], &nodes[last + 1], [d, this](_Node *a, _Node *b) { return _comparator(d, **a, **b); });
		size_t median = (first + last + 1) >> 1;
		for( ; median > first && !_comparator(d, **nodes[median - 1], **nodes[median]); --median) {}
		nodes[median]->_up = node;
		if(!New) nodes[median]->cast()->_weight = 0;
		if(median != first) {
			nodes[median]->_down[0] = _construct_routine<New>(nodes[median], nodes, (d + 1) % K, first, median - 1);
			nodes[median]->cast()->_weight += nodes[median]->_down[0]->cast()->_weight; }
		else if(!New) { nodes[median]->_down[0] = nullptr; ++nodes[median]->cast()->_weight; }
		if(median != last)  {
			nodes[median]->_down[1] = _construct_routine<New>(nodes[median], nodes, (d + 1) % K, median + 1, last );
			nodes[median]->cast()->_weight += nodes[median]->_down[1]->cast()->_weight; }
		else if(!New) { nodes[median]->_down[1] = nullptr; ++nodes[median]->cast()->_weight; }
		return nodes[median];
	}
	/* === Auxiliary === */
	/* ############################# Construct ############################# */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################## Lookup ############################### */
	/* === Count === */
	private:
	template <typename Key>
	size_t
	_count (const Key &key)
	{
		size_t count = 0;
		_Node *node = _head._up;
		for(ushort d = 0; node != nullptr; node = node->_down[!_comparator(d, key, **node)], d = (d + 1) % K)
			if(_equal(**node, key)) ++count;
		return count;
	}

	private:
	template <typename Key>
	size_t
	_count (const Key &key)
	const
	{
		size_t count = 0;
		const _Node *node = _head._up;
		for(ushort d = 0; node != nullptr; node = node->_down[!_comparator(d, key, **node)], d = (d + 1) % K)
			if(_equal(**node, key)) ++count;
		return count;
	}
	/* === Count === */


	/* === Find === */
	private:
	template <typename Key>
	_Node *
	_find (const Key &key)
	{
		_Node *node = _head._up;
		for(ushort d = 0; node != nullptr; node = node->_down[!_comparator(d, key, **node)], d = (d + 1) % K)
			if(_equal(**node, key)) return node;
		return &_head;
	}

	private:
	template <typename Key>
	const _Node *
	_find (const Key &key)
	const
	{
		const _Node *node = _head._up;
		for(ushort d = 0; node != nullptr; node = node->_down[!_comparator(d, key, **node)], d = (d + 1) % K)
			if(_equal(**node, key)) return node;
		return &_head;
	}
	/* === Find === */


	/* === Equal range === */
	private:
	template <typename Key>
	_Range
	_equal_range (const Key &key)
	{
		_Range range;
		_Node *node = _head._up;
		for(ushort d = 0; node != nullptr; node = node->_down[!_comparator(d, key, **node)], d = (d + 1) % K)
			if(_equal(**node, key)) range._push(node);
		return range;
	}

	private:
	template <typename Key>
	_CRange
	_equal_range (const Key &key)
	const
	{
		_CRange range;
		const _Node *node = _head._up;
		for(ushort d = 0; node != nullptr; node = node->_down[!_comparator(d, key, **node)], d = (d + 1) % K)
			if(_equal(**node, key)) range._push(node);
		return range;
	}
	/* === Equal range === */


	/* === Nearest neighbour === */
	private:
	template <typename Measure, typename Key>
	void
	_nearest_neighbour (const Key &key, Measure &measure,
		                        double &distance, _Node *&nearest, ushort d, _Node *node)
	{
		double tmp = measure(**node, key);
		if(tmp < distance) { distance = tmp, nearest = node; }
		if(!_comparator(d, key, **node)) {
			if(node->_down[1] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]);
			if(node->_down[0] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]); }
		else {
			if(node->_down[0] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]);
			if(node->_down[1] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]); }
	}

	private:
	template <typename Measure, typename Key>
	void
	_nearest_neighbour (const Key &key, Measure &measure,
		                        double &distance, const _Node *&nearest, ushort d, const _Node *node)
	const
	{
		double tmp = measure(**node, key);
		if(tmp < distance) { distance = tmp, nearest = node; }
		if(!_comparator(d, key, **node)) {
			if(node->_down[1] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]);
			if(node->_down[0] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]); }
		else {
			if(node->_down[0] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]);
			if(node->_down[1] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]); }
	}

	private:
	template <typename Measure, typename Key>
	void
	_nearest_neighbour (const Key &key, const Measure &measure,
		                        double &distance, _Node *&nearest, ushort d, _Node *node)
	{
		double tmp = measure(**node, key);
		if(tmp < distance) { distance = tmp, nearest = node; }
		if(!_comparator(d, key, **node)) {
			if(node->_down[1] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]);
			if(node->_down[0] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]); }
		else {
			if(node->_down[0] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]);
			if(node->_down[1] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]); }
	}

	private:
	template <typename Measure, typename Key>
	void
	_nearest_neighbour (const Key &key, const Measure &measure,
		                        double &distance, const _Node *&nearest, ushort d, const _Node *node)
	const
	{
		double tmp = measure(**node, key);
		if(tmp < distance) { distance = tmp, nearest = node; }
		if(!_comparator(d, key, **node)) {
			if(node->_down[1] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]);
			if(node->_down[0] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]); }
		else {
			if(node->_down[0] != nullptr)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[0]);
			if(node->_down[1] != nullptr && measure(d, **node, key) < distance)
				_nearest_neighbour(key, measure, distance, nearest, (d + 1) % K, node->_down[1]); }
	}
	/* === Nearest neighbour === */


	/* === Range search === */
	private:
	template <typename Key1, typename Key2>
	void
	_range_search (_Range &range, const Key1 &min, const Key2 &max, ushort bounds, ushort d, _Node *node)
	{
		if(_range_bounded(bounds)) { _report_subtree(range, node); return; }
		if(!_comparator(d, **node, min)) {
			if(!_comparator(d, max, **node)) {
				if(_range_inside(min, max, d, node)) range._push(node);
			     if(node->_down[0] != nullptr)
				 	_range_search(range, min, max, bounds | (1 << (d * 2 + 1)), (d + 1) % K, node->_down[0]); }
			else if(node->_down[0] != nullptr)
				_range_search(range, min, max, bounds, (d + 1) % K, node->_down[0]);
			if(node->_down[1] != nullptr && _comparator(d, **node, max))
				_range_search(range, min, max, bounds | (1 << (d * 2)), (d + 1) % K, node->_down[1]); }
		else if(node->_down[1] != nullptr && _comparator(d, **node, max))
			_range_search(range, min, max, bounds, (d + 1) % K, node->_down[1]);
	}

	private:
	template <typename Key1, typename Key2>
	void
	_range_search (_CRange &range, const Key1 &min, const Key2 &max, ushort bounds, ushort d, const _Node *node)
	const
	{
		if(_range_bounded(bounds)) { _report_subtree(range, node); return; }
		if(!_comparator(d, **node, min)) {
			if(!_comparator(d, max, **node)) {
				if(_range_inside(min, max, d, node)) range._push(node);
			     if(node->_down[0] != nullptr)
				 	_range_search(range, min, max, bounds | (1 << (d * 2 + 1)), (d + 1) % K, node->_down[0]); }
			else if(node->_down[0] != nullptr)
				_range_search(range, min, max, bounds, (d + 1) % K, node->_down[0]);
			if(node->_down[1] != nullptr && _comparator(d, **node, max))
				_range_search(range, min, max, bounds | (1 << (d * 2)), (d + 1) % K, node->_down[1]); }
		else if(node->_down[1] != nullptr && _comparator(d, **node, max))
			_range_search(range, min, max, bounds, (d + 1) % K, node->_down[1]);
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
	void
	_report_subtree (_Range &range, _Node *node)
	{
		for( ; node != nullptr; node = node->_down[1]) {
			range._push(node);
			if(node->_down[0] != nullptr) _report_subtree(range, node->_down[0]); }
	}

	private:
	void
	_report_subtree (_CRange &range, const _Node *node)
	const
	{
		for( ; node != nullptr; node = node->_down[1]) {
			range._push(node);
			if(node->_down[0] != nullptr) _report_subtree(range, node->_down[0]); }
	}
	/* === Range search === */
	/* ############################## Lookup ############################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################### Print ############################### */
	private:
	template <bool Verbose, typename Printer>
	void
	_print (Printer &printer, long long int branches, ushort depth, bool side, const _Node *node, ushort d)
	const
	{
		if(node->_down[1] != nullptr)
			_print<Verbose>
				(printer, side == 0 ? branches | (1 << (depth - 1)) : branches, depth + 1, 1, node->_down[1], (d + 1) % K);
		if(depth == 0) printf("%s\u2574", node->_up == &_head ? "\u2500" : "\u2504");
		else           printf("  ");
		if(depth > 1) {
			for(ushort i = 0; i < depth - 1; ++i) {
				if((branches >> i) & 1) printf("\u2502   ");
				else                    printf("    "); } }
		if(depth > 0) {
			if(side == 0) printf("\u2514\u2500\u2500\u2574");
			else          printf("\u250c\u2500\u2500\u2574"); }
		if(Verbose) { printf("\x1B[90m%lu", d); node->cast()->print(); printf("\x1B[0m "); }
		printer(node->info()); printf("\n");
		if(node->_down[0] != nullptr)
			_print<Verbose>
				(printer, side == 1 ? branches | (1 << (depth - 1)) : branches, depth + 1, 0, node->_down[0], (d + 1) % K);
	}

	private:
	template <bool Verbose, typename Printer>
	void
	_print (const Printer &printer, long long int branches, ushort depth, bool side, const _Node *node, ushort d)
	const
	{
		if(node->_down[1] != nullptr)
			_print<Verbose>
				(printer, side == 0 ? branches | (1 << (depth - 1)) : branches, depth + 1, 1, node->_down[1], (d + 1) % K);
		if(depth == 0) printf("%s\u2574", node->_up == &_head ? "\u2500" : "\u2504");
		else           printf("  ");
		if(depth > 1) {
			for(ushort i = 0; i < depth - 1; ++i) {
				if((branches >> i) & 1) printf("\u2502   ");
				else                    printf("    "); } }
		if(depth > 0) {
			if(side == 0) printf("\u2514\u2500\u2500\u2574");
			else          printf("\u250c\u2500\u2500\u2574"); }
		if(Verbose) { printf("\x1B[90m%lu", d); node->cast()->print(); printf("\x1B[0m "); }
		printer(node->info()); printf("\n");
		if(node->_down[0] != nullptr)
			_print<Verbose>
				(printer, side == 1 ? branches | (1 << (depth - 1)) : branches, depth + 1, 0, node->_down[0], (d + 1) % K);
	}
	/* ############################### Print ############################### */
	/* ##################################################################### */
};

#endif
