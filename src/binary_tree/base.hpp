#ifndef _GMD_BINARY_TREE_BASE_
#define _GMD_BINARY_TREE_BASE_

template <typename Node, typename Key, typename Value, typename Info, bool SetMap>
struct binary_tree_node_superbase
{
	/* === Cast === */
	protected:
	constexpr       Node *cast ()       { return reinterpret_cast<      Node *>(this); }
	constexpr const Node *cast () const { return reinterpret_cast<const Node *>(this); }
	/* === Cast === */

	/* === Key === */
	protected:
	template <bool _ = !SetMap, typename = ::std::enable_if_t<_>>
	static inline const Key &key (const Info &info) { return info; }

	template <bool _ =  SetMap, typename = ::std::enable_if_t<_>, typename = void>
	static inline const Key &key (const Info &info) { return info.first; }

	protected:
	template <bool _ = !SetMap, typename = ::std::enable_if_t<_>>
	inline const Key &operator* () const { return *cast()->_info._M_ptr(); }

	template <bool _ =  SetMap, typename = ::std::enable_if_t<_>, typename = void>
	inline const Key &operator* () const { return  cast()->_info._M_ptr()->first; }
	/* === Key === */

	/* === Value === */
	protected:
	template <bool _ = SetMap, typename = ::std::enable_if_t<_>>
	inline       Value &value ()       { return cast()->_info._M_ptr()->second; }

	template <bool _ = SetMap, typename = ::std::enable_if_t<_>>
	inline const Value &value () const { return cast()->_info._M_ptr()->second; }
	/* === Value === */

	/* === Info === */
	protected:
	inline       Info &info ()       { return *cast()->_info._M_ptr(); }
	inline const Info &info () const { return *cast()->_info._M_ptr(); }
	/* === Info === */
};

template <typename Node, typename Key, typename Value, typename Info, bool SetMap, bool Threaded>
struct binary_tree_node_base;

template <typename Node, typename Key, typename Value, typename Info, bool SetMap>
struct binary_tree_node_base<Node, Key, Value, Info, SetMap, false>
: public binary_tree_node_superbase<Node, Key, Value, Info, SetMap>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <bool, typename, bool> friend struct binary_tree_traversor;
	friend struct binary_tree_iteration;

	private:
	using _Node = binary_tree_node_base<Node, Key, Value, Info, SetMap, false>;

	static constexpr bool _Threaded = false;

	/* === Variables === */
	private:
	_Node *_up, *_down[2] = {nullptr, nullptr};
	/* === Variables === */

	/* === Constructor & Destructor === */
	protected:
	binary_tree_node_base (_Node *up) : _up(up) {}
	/* === Constructor & Destructor === */
};

template <typename Node, typename Key, typename Value, typename Info, bool SetMap>
struct binary_tree_node_base<Node, Key, Value, Info, SetMap, true>
: public binary_tree_node_superbase<Node, Key, Value, Info, SetMap>
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;
	template <bool, typename, bool> friend struct binary_tree_traversor;
	friend struct binary_tree_iteration;

	private:
	using _Node = binary_tree_node_base<Node, Key, Value, Info, SetMap, true>;

	static constexpr bool _Threaded = true;

	/* === Variables === */
	private:
	_Node *_up, *_down[2] = {nullptr, nullptr}, *_thread[2];
	/* === Variables === */

	/* === Constructor & Destructor === */
	protected:
	binary_tree_node_base (_Node *up) : _up(up), _thread{nullptr, nullptr} {}
	binary_tree_node_base (_Node *up, _Node *prev, _Node *next) : _up(up), _thread{prev, next} {}
	/* === Constructor & Destructor === */
};

template <typename Node, bool Multi, typename Comparator, typename Allocator>
struct binary_tree_base
{
	template <typename, bool, typename, typename> friend struct binary_tree_base;
	template <binary_tree_type, typename, bool, typename, typename> friend struct binary_tree_subbase;

	private:
	using _Node = typename Node::_Base;
	using _SubBase = binary_tree_subbase<Node::_Tree, Node, Multi, Comparator, Allocator>;

	using _Allocator = typename ::std::allocator_traits<Allocator>::template rebind_alloc<Node>;
	using _ATraits   = typename ::std::allocator_traits<_Allocator>;

	using   _Traversor = binary_tree_traversor<false, Node, 1>;
	using  _CTraversor = binary_tree_traversor<true , Node, 1>;
	using  _RTraversor = binary_tree_traversor<false, Node, 0>;
	using _CRTraversor = binary_tree_traversor<true , Node, 0>;

	using _Iteration = binary_tree_iteration;

	// Perhaps use ::std::disjunction for this
	template <typename T> static constexpr bool _is_traversor_v = ::std::is_same_v<T, _Traversor> ||
		::std::is_same_v<T, _RTraversor> || ::std::is_same_v<T, _CTraversor> || ::std::is_same_v<T, _CRTraversor>;
	template <typename T> static constexpr bool _is_non_const_traversor_v =
		::std::is_same_v<T, _Traversor> || ::std::is_same_v<T, _RTraversor>;

	public:
	using        key_type = typename Node::_Key;
	using      value_type = typename Node::_Info;
	using       size_type = size_t;
	using difference_type = ::std::ptrdiff_t;
	using     key_compare = Comparator;
	using  allocator_type = Allocator;
	using       reference =       value_type &;
	using const_reference = const value_type &;
	using         pointer =       value_type *;
	using   const_pointer = const value_type *;
	// using         pointer = typename _ATraits::      pointer;
	// using   const_pointer = typename _ATraits::const_pointer;

	using               traversor =   _Traversor; using               iterator =   _Traversor;
	using         const_traversor =  _CTraversor; using         const_iterator =  _CTraversor;
	using       reverse_traversor =  _RTraversor; using       reverse_iterator =  _RTraversor;
	using const_reverse_traversor = _CRTraversor; using const_reverse_iterator = _CRTraversor;


	/* === Variables === */
	protected:
	Comparator _comparator;
	_Allocator _allocator;
	size_t _size = 0;
	_Node _head = _Node(nullptr);
	/* === Variables === */


	/* === Cast === */
	private:
	constexpr       _SubBase &cast ()       { return reinterpret_cast<      _SubBase &>(*this); }
	constexpr const _SubBase &cast () const { return reinterpret_cast<const _SubBase &>(*this); }
	/* === Cast === */


	/* ##################################################################### */
	/* ##################### Constructor & Destructor ###################### */
	/* === Default === */
	public:
	binary_tree_base (const Comparator &c = Comparator(), const Allocator &a = Allocator())
		: _comparator(c),            _allocator(_Allocator(a)) { _reset_head(); }

	binary_tree_base (                                    const Allocator &a)
		: _comparator(Comparator()), _allocator(_Allocator(a)) { _reset_head(); }
	/* === Default === */


	/* === Copy === */
	public:
	binary_tree_base (const binary_tree_base &other)
	    : _comparator(other._comparator), _allocator(_ATraits::select_on_container_copy_construction(other._allocator))
	{ _reset_head(); _copy_structure(other); }

	binary_tree_base (const binary_tree_base &other, const Comparator &c)
	    : _comparator(c),                 _allocator(_ATraits::select_on_container_copy_construction(other._allocator))
	{ _reset_head(); _copy_structure(other); }

	binary_tree_base (const binary_tree_base &other,                      const Allocator &a)
	    : _comparator(other._comparator), _allocator(_Allocator(a))
	{ _reset_head(); _copy_structure(other); }

	binary_tree_base (const binary_tree_base &other, const Comparator &c, const Allocator &a)
	    : _comparator(c),                 _allocator(_Allocator(a))
	{ _reset_head(); _copy_structure(other); }
	/* === Copy === */


	/* === Move === */
	public:
	binary_tree_base (binary_tree_base &&other)
		: _comparator(::std::move(other._comparator)), _allocator(::std::move(other._allocator))
	{ _reset_head(); _move_structure(::std::move(other)); other._reset(); }

	binary_tree_base (binary_tree_base &&other, const Comparator &c)
		: _comparator(c),                              _allocator(::std::move(other._allocator))
	{ _reset_head(); _move_structure(::std::move(other)); other._reset(); }

	binary_tree_base (binary_tree_base &&other, const Allocator &a)
		: _comparator(::std::move(other._comparator)), _allocator(_Allocator(a))
	{ _reset_head();
		if(_ATraits::is_always_equal::value || _allocator == other._allocator) {
			_move_structure(::std::move(other)); other._reset(); }
		else { _copy_structure(other); other.clear(); } }

	binary_tree_base (binary_tree_base &&other, const Comparator &c, const Allocator &a)
		: _comparator(c),                              _allocator(_Allocator(a))
	{ _reset_head();
		if(_ATraits::is_always_equal::value || _allocator == other._allocator) {
			_move_structure(::std::move(other)); other._reset(); }
	  	else { _copy_structure(other); other.clear(); } }
	/* === Move === */


	/* === Destructor === */
	protected:
	~binary_tree_base () { if(_size > 0) _clear(); }
	/* === Destructor === */
	/* ##################### Constructor & Destructor ###################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ########################## Assign operator ########################## */
	/* === Copy === */
	public:
	binary_tree_base &
	operator= (const binary_tree_base &other)
	{ if(this != &other) { _prepare_copy(other); if(other._size > 0) _copy_structure(other); } return *this; }

	public:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info> && (Multi || !Multi_Other) &&
	                   (Node::_Tree == Node_Other::_Tree || _binary_tree_use_structure_v<Node::_Tree>), binary_tree_base &>
	operator= (const binary_tree_base<Node_Other, Multi_Other, Comparator, Allocator_Other> &other)
	{ _prepare_copy(other); if(other._size > 0) _copy_structure(other); return *this; }

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, binary_tree_base &>
	operator= (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ _prepare_copy(other); if(other._size > 0) _copy_nodes(other); return *this; }
	/* === Copy === */


	/* === Move === */
	public:
	binary_tree_base &
	operator= (binary_tree_base &&other)
	{
		if(this != &other) {
			if(_prepare_move(::std::move(other))) {
				 if(other._size > 0) { _move_structure(::std::move(other)); other._reset(); } }
			else if(other._size > 0) { _copy_structure(other);              other.clear();  } }
		return *this;
	}

	public:
	template <bool Multi_Other>
	::std::enable_if_t<Multi || !Multi_Other, binary_tree_base &>
	operator= (binary_tree_base<Node, Multi_Other, Comparator, Allocator> &&other)
	{
		if(_prepare_move(::std::move(other))) {
			 if(other._size > 0) { _move_structure(::std::move(other)); other._reset(); } }
		else if(other._size > 0) { _copy_structure(other);              other.clear();  }
		return *this;
	}

	public:
	template <bool Multi_Other, typename Comparator_Other>
	binary_tree_base &
	operator= (binary_tree_base<Node, Multi_Other, Comparator_Other, Allocator> &&other)
	{
		if(_prepare_move(::std::move(other))) {
			 if(other._size > 0) { _move_nodes(::std::move(other)); other._reset(); } }
		else if(other._size > 0) { _copy_nodes(other);              other.clear();  }
		return *this;
	}

	public:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info> && (Multi || !Multi_Other) &&
	                   (Node::_Tree == Node_Other::_Tree || _binary_tree_use_structure_v<Node::_Tree>), binary_tree_base &>
	operator= (binary_tree_base<Node_Other, Multi_Other, Comparator, Allocator_Other> &&other)
	{ _prepare_move(::std::move(other)); if(other._size > 0) { _copy_structure(other); other.clear(); } return *this; }

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, binary_tree_base &>
	operator= (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &&other)
	{ _prepare_move(::std::move(other)); if(other._size > 0) { _copy_nodes(other); other.clear(); } return *this; }
	/* === Move === */


	/* === Initializer List === */
	public:
	binary_tree_base &
	operator= (const ::std::initializer_list<typename Node::_Info> &il)
	{ clear(); insert(il); return *this; }
	/* === Initializer List === */
	/* ########################## Assign operator ########################## */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ####################### Comparison operators ######################## */
	/* === Equal === */
	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator== (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ return _equal_to(other); }

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator== (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{ return _equal_to(other); }
	/* === Equal === */


	/* === Not Equal === */
	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator!= (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ return !_equal_to(other); }

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator!= (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{ return !_equal_to(other); }
	/* === Not Equal === */


	/* === Lesser === */
	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator< (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ return _lesser_than(other); }

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator< (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{ return _lesser_than(other); }
	/* === Lesser === */


	/* === Greater === */
	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator> (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ return _greater_than(other); /* other._lesser_than(*this); */ }

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator> (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{ return _greater_than(other); /* other._lesser_than(*this); */ }
	/* === Greater === */


	/* === Lesser or Equal === */
	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator<= (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ return !_greater_than(other); /* !other._lesser_than(*this); */ }

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator<= (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{ return !_greater_than(other); /* !other._lesser_than(*this); */ }
	/* === Lesser or Equal === */


	/* === Greater or Equal === */
	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator>= (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ return !_lesser_than(other); }

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, bool>
	operator>= (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{ return !_lesser_than(other); }
	/* === Greater or Equal === */


	/* === Spaceship === */ /* Operator <=> */
	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, int>
	spaceship (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ return _spaceship(other); }

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<::std::is_same_v<typename Node::_Key, typename Node_Other::_Key> ||
	                          _is_transparent_v<Comparator, typename Node_Other::_Key>, int>
	spaceship (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{ return _spaceship(other); }
	/* === Spaceship === */ /* Operator <=> */
	/* ####################### Comparison operators ######################## */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################# Observers ############################# */
	/* === Comparator === */
	public:
	inline Comparator key_comp () const { return _comparator; }

	public:
	struct Info_Comparator {
		template <typename, bool, typename, typename> friend struct binary_tree_base;
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


	/* === Allocator === */
	public:
	inline Allocator get_allocator () const { return Allocator(_allocator); }
	/* === Allocator === */
	/* ############################# Observers ############################# */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ###################### Traversors / Iterators ####################### */
	public:
	inline   _Traversor   root ()       { return   _Traversor(_head._up); }
	inline  _CTraversor   root () const { return  _CTraversor(_head._up); }
	inline  _CTraversor  croot () const { return  _CTraversor(_head._up); }
	inline  _RTraversor  rroot ()       { return  _RTraversor(_head._up); }
	inline _CRTraversor  rroot () const { return _CRTraversor(_head._up); }
	inline _CRTraversor crroot () const { return _CRTraversor(_head._up); }

	inline   _Traversor   begin ()       { return   _Traversor( _begin()); }
	inline  _CTraversor   begin () const { return  _CTraversor( _begin()); }
	inline  _CTraversor  cbegin () const { return  _CTraversor( _begin()); }
	inline  _RTraversor  rbegin ()       { return  _RTraversor(_rbegin()); }
	inline _CRTraversor  rbegin () const { return _CRTraversor(_rbegin()); }
	inline _CRTraversor crbegin () const { return _CRTraversor(_rbegin()); }

	inline   _Traversor   end ()       { return   _Traversor(&_head); }
	inline  _CTraversor   end () const { return  _CTraversor(&_head); }
	inline  _CTraversor  cend () const { return  _CTraversor(&_head); }
	inline  _RTraversor  rend ()       { return  _RTraversor(&_head); }
	inline _CRTraversor  rend () const { return _CRTraversor(&_head); }
	inline _CRTraversor crend () const { return _CRTraversor(&_head); }
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
	template <bool Replace = false>
	::std::enable_if_t<!Multi && Replace == Replace, ::std::pair<_Traversor, bool>>
	insert (const typename Node::_Info &info)
	{
		if(!Replace) return cast()._insert_(info);
		else {
			::std::pair<_Node *, bool> result = cast()._insert_(info);
			if(!result.second) { _del_info(result.first); _new_info(result.first, info); }
			return result; }
	}

	public:
	template <bool Replace = false>
	::std::enable_if_t<!Multi && Replace == Replace, ::std::pair<_Traversor, bool>>
	insert (typename Node::_Info &&info)
	{
		if(!Replace) return cast()._insert_(::std::move(info));
		else {
			::std::pair<_Node *, bool> result = cast()._insert_(::std::move(info));
			if(!result.second) { _del_info(result.first); _new_info(result.first, ::std::move(info)); }
			return result; }
	}

	public:
	template <int _ = 0>
	inline ::std::enable_if_t<Multi && _ == _, _Traversor>
	insert (const typename Node::_Info &info)
	{ return cast()._insert_(info).first; }

	public:
	template <int _ = 0>
	inline ::std::enable_if_t<Multi && _ == _, _Traversor>
	insert (typename Node::_Info &&info)
	{ return cast()._insert_(::std::move(info)).first; }

	public:
	template <bool Replace = false, typename T1, typename T2>
	::std::enable_if_t<!Multi && Replace == Replace, size_t>
	insert (const T1 &first, const T2 &last)
	{
		size_t count = 0;
		if(!Replace) for(T1 tr = first; tr != last; ++tr) count += cast()._insert_(*tr).second;
		else {
			for(T1 tr = first; tr != last; ++tr) {
				::std::pair<_Node *, bool> result = cast()._insert_(*tr); count += result.second;
				if(!result.second) { _del_info(result.first); _new_info(result.first, *tr); } } }
		return count;
	}

	public:
	template <typename T1, typename T2>
	::std::enable_if_t<Multi && ::std::is_same_v<T1, T1>, void>
	insert (const T1 &first, const T2 &last)
	{ for(T1 tr = first; tr != last; ++tr) cast()._insert_(*tr); }

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

	public:
	template <bool Replace = false, typename T>
	inline ::std::enable_if_t<!Multi && _is_non_const_traversor_v<T>, ::std::pair<_Traversor, bool>>
	insert (const T &hint, const typename Node::_Info &info)
	{ return insert_hint<Replace>(hint, info); }

	public:
	template <bool Replace = false, typename T>
	inline ::std::enable_if_t<!Multi && _is_non_const_traversor_v<T>, ::std::pair<_Traversor, bool>>
	insert (const T &hint, typename Node::_Info &&info)
	{ return insert_hint<Replace>(hint, ::std::move(info)); }

	public:
	template <typename T>
	inline ::std::enable_if_t<Multi && _is_non_const_traversor_v<T>, _Traversor>
	insert (const T &hint, const typename Node::_Info &info)
	{ return insert_hint(hint, info); }

	public:
	template <typename T>
	inline ::std::enable_if_t<Multi && _is_non_const_traversor_v<T>, _Traversor>
	insert (const T &hint, typename Node::_Info &&info)
	{ return insert_hint(hint, ::std::move(info)); }

	public:
	template <bool Replace = false, typename T>
	::std::enable_if_t<!Multi && _is_non_const_traversor_v<T>, ::std::pair<_Traversor, bool>>
	insert_hint (const T &hint, const typename Node::_Info &info)
	{
		if(!Replace) return cast()._insert_hint_(hint._node, info);
		else {
			::std::pair<_Node *, bool> result = cast()._insert_hint_(hint._node, info);
			if(!result.second) { _del_info(result.first); _new_info(result.first, info); }
			return result; }
	}

	public:
	template <bool Replace = false, typename T>
	::std::enable_if_t<!Multi && _is_non_const_traversor_v<T>, ::std::pair<_Traversor, bool>>
	insert_hint (const T &hint, typename Node::_Info &&info)
	{
		if(!Replace) return cast()._insert_hint_(hint._node, ::std::move(info));
		else {
			::std::pair<_Node *, bool> result = cast()._insert_hint_(hint._node, ::std::move(info));
			if(!result.second) { _del_info(result.first); _new_info(result.first, ::std::move(info)); }
			return result; }
	}

	public:
	template <typename T>
	inline ::std::enable_if_t<Multi && _is_non_const_traversor_v<T>, _Traversor>
	insert_hint (const T &hint, const typename Node::_Info &info)
	{ return cast()._insert_hint_(hint._node, info).first; }

	public:
	template <typename T>
	inline ::std::enable_if_t<Multi && _is_non_const_traversor_v<T>, _Traversor>
	insert_hint (const T &hint, typename Node::_Info &&info)
	{ return cast()._insert_hint_(hint._node, ::std::move(info)).first; }
	/* === Insert === */


	/* === Emplace === */
	public:
	template <bool Replace = false, typename... Args>
	::std::enable_if_t<!Multi && Replace == Replace, ::std::pair<_Traversor, bool>>
	emplace (Args&&... info)
	{
		_Node *node = _new_node_threadless(nullptr, ::std::forward<Args>(info)...);
		::std::pair<_Node *, bool> result = cast()._emplace_(node);
		if(!result.second) { if(Replace) { _del_info(result.first); _new_info(result.first, node->info()); }
		                     _del_node(node); }
		return result;
	}

	public:
	template <int _ = 0, typename... Args>
	inline ::std::enable_if_t<Multi && _ == _, _Traversor>
	emplace (Args&&... info)
	{ return cast()._emplace_(_new_node_threadless(nullptr, ::std::forward<Args>(info)...)).first; }

	public:
	template <bool Replace = false, typename T, typename... Args>
	::std::enable_if_t<!Multi && _is_non_const_traversor_v<T>, ::std::pair<_Traversor, bool>>
	emplace_hint (const T &hint, Args&&... info)
	{
		_Node *node = _new_node_threadless(nullptr, ::std::forward<Args>(info)...);
		::std::pair<_Node *, bool> result = cast()._emplace_hint_(hint._node, node);
		if(!result.second) { if(Replace) { _del_info(result.first); _new_info(result.first, node->info()); }
		                     _del_node(node); }
		return result;
	}

	public:
	template <typename T, typename... Args>
	inline ::std::enable_if_t<Multi && _is_non_const_traversor_v<T>, _Traversor>
	emplace_hint (const T &hint, Args&&... info)
	{ return cast()._emplace_hint_(hint._node, _new_node_threadless(nullptr, ::std::forward<Args>(info)...)).first; }

	public:
	template <int _ = 0, typename... Args>
	::std::enable_if_t<!Multi && Node::_SetMap && _ == _, ::std::pair<_Traversor, bool>>
	try_emplace (const typename Node::_Key &key, Args&&... value)
	{
		int side; _Node *place = _place(side, key);
		if(side == -1) return {place, false};
		return cast()._emplace_hint_(place, _new_node_threadless(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(key), ::std::forward_as_tuple(::std::forward<Args>(value)...)));
	}

	public:
	template <int _ = 0, typename... Args>
	::std::enable_if_t<!Multi && Node::_SetMap && _ == _, ::std::pair<_Traversor, bool>>
	try_emplace (typename Node::_Key &&key, Args&&... value)
	{
		int side; _Node *place = _place(side, ::std::move(key));
		if(side == -1) return {place, false};
		return cast()._emplace_hint_(place, _new_node_threadless(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(::std::move(key)), ::std::forward_as_tuple(::std::forward<Args>(value)...)));
	}

	public:
	template <typename T, typename... Args>
	inline ::std::enable_if_t<!Multi && Node::_SetMap && _is_non_const_traversor_v<T>,
		::std::pair<_Traversor, bool>>
	try_emplace (const T &hint, const typename Node::_Key &key, Args&&... value)
	{ return try_emplace_hint(hint, key, ::std::forward<Args>(value)...); }

	public:
	template <typename T, typename... Args>
	inline ::std::enable_if_t<!Multi && Node::_SetMap && _is_non_const_traversor_v<T>,
		::std::pair<_Traversor, bool>>
	try_emplace (const T &hint, typename Node::_Key &&key, Args&&... value)
	{ return try_emplace_hint(hint, ::std::move(key), ::std::forward<Args>(value)...); }

	public:
	template <typename T, typename... Args>
	inline ::std::enable_if_t<!Multi && Node::_SetMap && _is_non_const_traversor_v<T>,
		::std::pair<_Traversor, bool>>
	try_emplace_hint (const T &hint, const typename Node::_Key &key, Args&&... value)
	{
		int side; _Node *place = _place_hint(hint._node, side, key);
		if(side == -1) return {place, false};
		return cast()._emplace_hint_(place, _new_node_threadless(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(key), ::std::forward_as_tuple(::std::forward<Args>(value)...)));
	}

	public:
	template <typename T, typename... Args>
	inline ::std::enable_if_t<!Multi && Node::_SetMap && _is_non_const_traversor_v<T>,
		::std::pair<_Traversor, bool>>
	try_emplace_hint (const T &hint, typename Node::_Key &&key, Args&&... value)
	{
		int side; _Node *place = _place_hint(hint._node, side, ::std::move(key));
		if(side == -1) return {place, false};
		return cast()._emplace_hint_(place, _new_node_threadless(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(::std::move(key)), ::std::forward_as_tuple(::std::forward<Args>(value)...)));
	}
	/* === Emplace === */


	/* === Erase === */
	public:
	template <bool _ = 0>
	::std::enable_if_t<!Multi && _ == _, bool>
	erase (const typename Node::_Key &key)
	{ _Node *node = _find(key); if(node == &_head) return false; cast()._erase_(node, true); return true; }

	public:
	template <bool _ = 0>
	::std::enable_if_t<Multi && _ == _, size_t>
	erase (const typename Node::_Key &key)
	{
		_Node *begin = _find(key); if(begin == &_head) return 0;
		_Node *node, *end = _upper_bound(key);
		size_t count = 0;
		if(begin == _begin() && end == &_head) { count = _size; clear(); return count; }
		for( ; begin != end; begin = node, ++count) { node = _Iteration::_<1>(begin); cast()._erase_(begin, true); }
		return count;
	}

	public:
	template <typename T>
	inline ::std::enable_if_t<_is_non_const_traversor_v<T>, void>
	erase (const T &tr)
	{ cast()._erase_(tr._node, true); }

	public:
	template <typename T1, typename T2>
	::std::enable_if_t<_is_non_const_traversor_v<T1> && _is_traversor_v<T2>, void>
	erase (const T1 &first, const T2 &last)
	{
		if(first._node == _begin() && last._node == &_head && _size > 0) { clear(); return; }
		for(_Node *node1 = first._node, *node2; node1 != last._node; node1 = node2) {
			node2 = _Iteration::_<1>(node1); cast()._erase_(node1, true); }
	}

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
	template <bool Replace = false, typename Node_Other, bool Multi_Other,
	          typename Comparator_Other, typename Allocator_Other, typename T>
	inline ::std::enable_if_t<!Multi && ::std::is_same_v<typename Node::_Info, typename Node_Other::_Info> &&
		binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other>::template _is_non_const_traversor_v<T>,
		::std::pair<_Traversor, bool>>
	transfer (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other, const T &tr)
	{
		if constexpr(::std::is_same_v<Node, Node_Other> && ::std::is_same_v<Allocator, Allocator_Other>)
			if(_ATraits::is_always_equal::value || _allocator == other._allocator)
				return _transfer_move<Replace>(other, tr._node);
		return _transfer_copy<Replace>(other, tr._node);
	}

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other, typename T>
	inline ::std::enable_if_t<Multi && ::std::is_same_v<typename Node::_Info, typename Node_Other::_Info> &&
		binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other>::template _is_non_const_traversor_v<T>,
		_Traversor>
	transfer (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other, const T &tr)
	{
		if constexpr(::std::is_same_v<Node, Node_Other> && ::std::is_same_v<Allocator, Allocator_Other>)
			if(_ATraits::is_always_equal::value || _allocator == other._allocator)
				return _Traversor(_transfer_move(other, tr._node));
		return _Traversor(_transfer_copy(other, tr._node));
	}
	/* === Transfer === */


	/* === Merge === */
	public:
	template <bool Replace = false, typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<!Multi && ::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, size_t>
	merge (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		if(this == reinterpret_cast<binary_tree_base *>(&other) || other._size == 0) return 0;
		if constexpr(::std::is_same_v<Node, Node_Other> && ::std::is_same_v<Allocator, Allocator_Other>)
			if(_ATraits::is_always_equal::value || _allocator == other._allocator)
				return _merge_move<Replace>(other);
		return _merge_copy<Replace>(other);
	}

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	inline ::std::enable_if_t<Multi && ::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, void>
	merge (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		if(this == reinterpret_cast<binary_tree_base *>(&other) || other._size == 0) return 0;
		if constexpr(::std::is_same_v<Node, Node_Other> && ::std::is_same_v<Allocator, Allocator_Other>)
			if(_ATraits::is_always_equal::value || _allocator == other._allocator)
				{ _merge_move(other); return; }
		_merge_copy(other);
	}
	/* === Merge === */


	/* === Swap === */
	public:
	void
	swap (binary_tree_base &other)
	{ if(this != &other) { if(_prepare_swap(other)) _swap_move_structure(other); else _swap_copy_structure(other); } }

	public:
	template <bool Multi_Other>
	void
	swap (binary_tree_base<Node, Multi_Other, Comparator, Allocator> &other)
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
	template <bool Multi_Other, typename Comparator_Other>
	void
	swap (binary_tree_base<Node, Multi_Other, Comparator_Other, Allocator> &other)
	{ if(_prepare_swap(other)) _swap_move_nodes(other); else _swap_copy_nodes(other); }

	public:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, void>
	swap (binary_tree_base<Node_Other, Multi_Other, Comparator, Allocator_Other> &other)
	{
		_prepare_swap(other);
		constexpr bool in = _binary_tree_use_structure_v<Node::_Tree>, out = _binary_tree_use_structure_v<Node_Other::_Tree>;
		if(Multi == Multi_Other) {
			if(Node::_Tree == Node_Other::_Tree) _swap_copy_structure(other);
			else if(in) { if(out) _swap_copy_structure(other); else       _swap_copy_structure_nodes(other); }
			else         if(!out) _swap_copy_nodes    (other); else other._swap_copy_structure_nodes(*this); }
		else if( Multi && (Node::_Tree == Node_Other::_Tree ||  in))       _swap_copy_structure_nodes(other);
		else if(!Multi && (Node::_Tree == Node_Other::_Tree || out)) other._swap_copy_structure_nodes(*this);
		else _swap_copy_nodes(other);
	}

	public:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, void>
	swap (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ _prepare_swap(other); _swap_copy_nodes(other); }
	/* === Swap === */
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
		return cast()._emplace_hint_(place, _new_node_threadless(nullptr, ::std::piecewise_construct,
			:: std::forward_as_tuple(key), ::std::tuple<>())).first->value();
	}

	public:
	template <int _ = 0>
	::std::enable_if_t<!Multi && Node::_SetMap && _ == _, typename Node::_Value &>
	operator[] (typename Node::_Key &&key)
	{
		int side; _Node *place = _place(side, ::std::move(key));
		if(side == -1) return place->value();
		return cast()._emplace_hint_(place, _new_node_threadless(nullptr, ::std::piecewise_construct,
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
		if(node == &_head) throw ::std::out_of_range("binary_tree_map.at() out_of_range");
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
		if(node == &_head) throw ::std::out_of_range("binary_tree_map.at() out_of_range");
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
	::std::enable_if_t<::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, size_t>
	count (const Key &key)
	{
		if(!Multi) return _find(key) != &_head;
		else {
			size_t count = 0;
			_Node *lower = _lower_bound(key), *upper = _upper_bound(key);
			for( ; lower != upper; lower = _Iteration::_<1>(lower), ++count) {}
			return count; }
	}

	public:
	template <typename Key>
	::std::enable_if_t<::std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, size_t>
	count (const Key &key)
	const
	{
		if(!Multi) return _find(key) != &_head;
		else {
			size_t count = 0;
			const _Node *lower = _lower_bound(key), *upper = _upper_bound(key);
			for( ; lower != upper; lower = _Iteration::_<1>(lower), ++count) {}
			return count; }
	}
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
	template <typename Key>
	inline ::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, _Traversor>
	find (const Key &key)
	{ return _Traversor(_find(key)); }

	public:
	template <typename Key>
	inline ::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, _CTraversor>
	find (const Key &key)
	const
	{ return _CTraversor(_find(key)); }
	/* === Find === */


	/* === Find (short) === */
	public:
	template <typename Key>
	inline ::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, _Traversor>
	find_short (const Key &key)
	{ return _Traversor(_find_short(key)); }

	public:
	template <typename Key>
	inline ::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, _CTraversor>
	find_short (const Key &key)
	const
	{ return _CTraversor(_find_short(key)); }
	/* === Find (short) === */


	/* === Lower bound === */
	public:
	template <typename Key>
	inline ::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, _Traversor>
	lower_bound (const Key &key)
	{ return _Traversor(_lower_bound(key)); }

	public:
	template <typename Key>
	inline ::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, _CTraversor>
	lower_bound (const Key &key)
	const
	{ return _CTraversor(_lower_bound(key)); }
	/* === Lower bound === */


	/* === Upper bound === */
	public:
	template <typename Key>
	inline ::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, _Traversor>
	upper_bound (const Key &key)
	{ return _Traversor(_upper_bound(key)); }

	public:
	template <typename Key>
	inline ::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>, _CTraversor>
	upper_bound (const Key &key)
	const
	{ return _CTraversor(_upper_bound(key)); }
	/* === Upper bound === */


	/* === Equal range === */
	public:
	template <typename Key>
	::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>,
		::std::pair<_Traversor, _Traversor>>
	equal_range (const Key &key)
	{
		_Node* lower = _lower_bound(key);
		if(lower == &_head || _comparator(key, **lower))
			 return {_Traversor(lower), _Traversor(lower)};
		else return {_Traversor(lower), _Traversor(!Multi ? _Iteration::_<1>(lower) : _upper_bound(key))};
	}

	public:
	template <typename Key>
	::std::enable_if_t<std::is_same_v<typename Node::_Key, Key> || _is_transparent_v<Comparator, Key>,
		::std::pair<_CTraversor, _CTraversor>>
	equal_range (const Key &key)
	const
	{
		const _Node* lower = _lower_bound(key);
		if(lower == &_head || _comparator(key, **lower))
			 return {_CTraversor(lower), _CTraversor(lower)};
		else return {_CTraversor(lower), _CTraversor(!Multi ? _Iteration::_<1>(lower) : _upper_bound(key))};
	}
	/* === Equal range === */
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
	{
		if constexpr(!Node::_Threaded) { _head._down  [0] = &_head; _head._down  [1] = &_head; }
		else                           { _head._thread[0] = &_head; _head._thread[1] = &_head; }
	}

	private:
	template <typename = ::std::enable_if_t<!Node::_Threaded>>
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
	template <typename... Args, typename = ::std::enable_if_t<!Node::_Threaded>>
	_Node *
	_new_node (_Node *up, Args&&... info)
	{
		++_size; Node *node = _ATraits::allocate(_allocator, 1);
		:: new(node) Node(up); _new_info(node, ::std::forward<Args>(info)...);
		return node;
	}

	private:
	template <typename... Args, typename = ::std::enable_if_t<Node::_Threaded>>
	_Node *
	_new_node (_Node *up, _Node *pred, _Node *succ, Args&&... info)
	{
		++_size; Node *node = _ATraits::allocate(_allocator, 1);
		:: new(node) Node(up, pred, succ); _new_info(node, ::std::forward<Args>(info)...);
		return node;
	}

	private:
	template <typename... Args>
	inline _Node *
	_new_node_threadless (_Node *up, Args&&... info)
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

	private:
	template <typename = ::std::enable_if_t<Node::_Threaded>>
	void
	_update_node (_Node *node, _Node *up, _Node *pred, _Node *succ)
	{ node->_up = up; node->_thread[0] = pred; node->_thread[1] = succ; }
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
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	void
	_prepare_copy (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ clear(); _copy_comparator(other._comparator); _copy_allocator(other._allocator); }

	private:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	bool
	_prepare_move (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &&other)
	{ clear(); _move_comparator(::std::move(other._comparator)); return _move_allocator(::std::move(other._allocator)); }

	private:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	bool
	_prepare_swap (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ _swap_comparator(other._comparator); return _swap_allocator(other._allocator); }
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
	_copy_structure (const binary_tree_base<Node_Other, Multi_Other, Comparator, Allocator_Other> &other)
	{ _copy_structure_routine(other._head._up); }

	private:
	template <typename _Node_Other>
	void
	_copy_structure_routine (const _Node_Other *root_other)
	{
		_head._up = _new_node_copy(&_head, root_other);
		if constexpr(!Node::_Threaded) { _copy_structure_routine(_head._up, root_other); _update_head(); }
		else {
			_Node *thread = &_head;
			_copy_structure_routine(_head._up, root_other, thread);
			thread->_thread[1] = &_head; _head._thread[0] = thread; }
	}

	private:
	template <typename _Node_Other, typename = ::std::enable_if_t<!Node::_Threaded>>
	void
	_copy_structure_routine (_Node *node, const _Node_Other *node_other)
	{
		for( ; ; node = node->_down[1], node_other = node_other->_down[1]) {
			if(node_other->_down[0] != nullptr) { node->_down[0] = _new_node_copy(node, node_other->_down[0]);
				_copy_structure_routine(node->_down[0], node_other->_down[0]); }
			if(node_other->_down[1] != nullptr)   node->_down[1] = _new_node_copy(node, node_other->_down[1]);
			else return; }
	}

	private:
	template <typename _Node_Other, typename = ::std::enable_if_t<Node::_Threaded>, typename = void>
	void
	_copy_structure_routine (_Node *node, const _Node_Other *node_other, _Node *&thread)
	{
		for( ; ; node = node->_down[1], node_other = node_other->_down[1]) {
			if(node_other->_down[0] != nullptr) { node->_down[0] = _new_node_copy(node, node_other->_down[0]);
				_copy_structure_routine(node->_down[0], node_other->_down[0], thread); }
			thread->_thread[1] = node; node->_thread[0] = thread; thread = node;
			if(node_other->_down[1] != nullptr)   node->_down[1] = _new_node_copy(node, node_other->_down[1]);
			else return; }
	}

	private:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	void
	_copy_nodes (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{ _copy_nodes_routine(other._begin(), &other._head); }

	private:
	template <typename _Node_Other>
	void
	_copy_nodes_routine (const _Node_Other *begin_other, const _Node_Other *end_other)
	{
		for(; begin_other != end_other; begin_other = _Iteration::_<1>(begin_other))
			cast()._insert_hint_(&_head, begin_other->info());
	}
	/* === Copy === */


	/* === Move === */
	private:
	template <bool Multi_Other>
	void
	_move_structure (binary_tree_base<Node, Multi_Other, Comparator, Allocator> &&other)
	{
		_size = other._size; other._head._up->_up = &_head;
		if constexpr(Node::_Threaded) {
			other._head._thread[0]->_thread[1] = &_head;
			other._head._thread[1]->_thread[0] = &_head; }
		_head = ::std::move(other._head);
	}

	private:
	template <bool Multi_Other, typename Comparator_Other>
	void
	_move_nodes (binary_tree_base<Node, Multi_Other, Comparator_Other, Allocator> &&other)
	{ _size = other._size; _move_nodes_routine(other._begin(), &other._head); }

	private:
	void
	_move_nodes_routine (_Node *begin_other, _Node *end_other)
	{
		for(_Node *node_other; begin_other != end_other; begin_other = node_other) {
			node_other = _Iteration::_<1>(begin_other); _reset_node(begin_other); cast()._emplace_hint_(&_head, begin_other); }
	}
	/* === Move === */


	/* === Swap === */
	private:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	void
	_swap_copy_structure (binary_tree_base<Node_Other, Multi_Other, Comparator, Allocator_Other> &other)
	{
		if(_size == 0) { if(other._size > 0) { _copy_structure(other); other.clear(); } return; }
		else      if(other._size == 0) { other._copy_structure(*this);       clear();   return; }

		_Node                      *root       =       _head._up, *begin       =       _begin();       _reset_head();
		typename Node_Other::_Base *root_other = other._head._up, *begin_other = other._begin(); other._reset_head();
		      _copy_structure_routine(root_other);
		other._copy_structure_routine(root);
		      _swap_copy_clear(root,       begin);
		other._swap_copy_clear(root_other, begin_other);
	}

	private:
	template <typename Node_Other, bool Multi_Other, typename Allocator_Other>
	void
	_swap_copy_structure_nodes (binary_tree_base<Node_Other, Multi_Other, Comparator, Allocator_Other> &other)
	{
		if(_size == 0) { if(other._size > 0) { _copy_structure(other); other.clear(); } return; }
		else      if(other._size == 0) { other._copy_nodes    (*this);       clear();   return; }

		_Node                      *root       =       _head._up, *begin       =       _begin();       _reset_head();
		typename Node_Other::_Base *root_other = other._head._up, *begin_other = other._begin(); other._reset_head();
		      _copy_structure_routine(root_other);
		other._copy_nodes_routine(begin, &_head);
			  _swap_copy_clear(root,       begin);
		other._swap_copy_clear(root_other, begin_other);
	}

	private:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	void
	_swap_copy_nodes (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		if(_size == 0) { if(other._size > 0) { _copy_nodes(other); other.clear(); } return; }
		else      if(other._size == 0) { other._copy_nodes(*this);       clear();   return; }

		_Node                      *root       =       _head._up, *begin       =       _begin();       _reset_head();
		typename Node_Other::_Base *root_other = other._head._up, *begin_other = other._begin(); other._reset_head();
		      _copy_nodes_routine(begin_other, &other._head);
		other._copy_nodes_routine(begin,             &_head);
			  _swap_copy_clear(root,       begin);
		other._swap_copy_clear(root_other, begin_other);
	}

	private:
	template <typename = ::std::enable_if_t<!Node::_Threaded>>
	inline void _swap_copy_clear (_Node *root, _Node *)  { _clear_routine(root); }

	template <typename = ::std::enable_if_t<Node::_Threaded>, typename = void>
	inline void _swap_copy_clear (_Node *, _Node *begin) { _clear_routine(begin, &_head); }


	private:
	template <bool Multi_Other>
	void
	_swap_move_structure (binary_tree_base<Node, Multi_Other, Comparator, Allocator> &other)
	{
		:: std::swap(_size, other._size);
		:: std::swap(_head._up->_up, other._head._up->_up);
		if constexpr(Node::_Threaded) {
			:: std::swap(_head._thread[0]->_thread[1], other._head._thread[0]->_thread[1]);
			:: std::swap(_head._thread[1]->_thread[0], other._head._thread[1]->_thread[0]); }
		:: std::swap(_head, other._head);
	}

	private:
	template <bool Multi_Other>
	void
	_swap_move_structure_nodes (binary_tree_base<Node, Multi_Other, Comparator, Allocator> &other)
	{
		if(_size == 0) { if(other._size > 0) { _move_structure(::std::move(other)); other._reset(); } return; }
		else      if(other._size == 0) { other._move_nodes    (::std::move(*this));       _reset();   return; }

		_Node *begin = _begin(); size_t size = _size;
		_move_structure(::std::move(other));
		other._size = size; other._reset_head(); other._move_nodes_routine(begin, &_head);
	}

	private:
	template <bool Multi_Other, typename Comparator_Other>
	void
	_swap_move_nodes (binary_tree_base<Node, Multi_Other, Comparator_Other, Allocator> &other)
	{
		if(_size == 0) { if(other._size > 0) { _move_nodes(::std::move(other)); other._reset(); } return; }
		else      if(other._size == 0) { other._move_nodes(::std::move(*this));       _reset();   return; }

		_Node *begin = _begin(), *begin_other = other._begin(); _reset_head(); other._reset_head();
		:: std::swap(_size, other._size);
		      _move_nodes_routine(begin_other, &other._head);
		other._move_nodes_routine(begin,             &_head);
	}
	/* === Swap === */


	/* === Transfer === */
	private:
	template <bool Replace, bool Multi_Other, typename Comparator_Other, bool _ = !Multi, typename = ::std::enable_if_t<_>>
	::std::pair<_Node *, bool>
	_transfer_move (binary_tree_base<Node, Multi_Other, Comparator_Other, Allocator> &other, _Node *node_other)
	{
		int side; _Node *place = _place(side, **node_other);
		if(side == -1) {
			if(Replace) { _del_info(place); _new_info(place, node_other->info()); other.cast()._erase_(node_other, true); }
		    return {place, false}; }
		other.cast()._erase_(node_other, false); --other._size; ++_size;
		_reset_node(node_other); return cast()._emplace_hint_(place, node_other);
	}

	private:
	template <bool Multi_Other, typename Comparator_Other, bool _ = Multi, typename = ::std::enable_if_t<_>>
	_Node *
	_transfer_move (binary_tree_base<Node, Multi_Other, Comparator_Other, Allocator> &other, _Node *node_other)
	{ other.cast()._erase_(node_other, false); --other._size; ++_size; _reset_node(node_other); return cast()._emplace_(node_other).first; }

	private:
	template <bool Replace, typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other,
	          bool _ = !Multi, typename = ::std::enable_if_t<_>>
	::std::pair<_Node *, bool>
	_transfer_copy (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other,
		            typename Node_Other::_Base *node_other)
	{
		::std::pair<_Node *, bool> result = cast()._insert_(node_other->info());
		if(result.second) other.cast()._erase_(node_other, true);
		else if(Replace) {
			_del_info(result.first); _new_info(result.first, node_other->info()); other.cast()._erase_(node_other, true); }
		return result;
	}

	private:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other,
	          bool _ = Multi, typename = ::std::enable_if_t<_>>
	_Node *
	_transfer_copy (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other,
		            typename Node_Other::_Base *node_other)
	{ _Node *node = cast()._insert_(node_other->info()).first; other.cast()._erase_(node_other, true); return node; }
	/* === Transfer === */


	/* === Merge === */
	private:
	template <bool Replace, bool Multi_Other, typename Comparator_Other, bool _ = !Multi, typename = ::std::enable_if_t<_>>
	size_t
	_merge_move (binary_tree_base<Node, Multi_Other, Comparator_Other, Allocator> &other)
	{
		if(_size == 0) {
			if constexpr(::std::is_same_v<Comparator, Comparator_Other>) _move_structure(::std::move(other));
			else                                                         _move_nodes    (::std::move(other));
			other._reset(); return _size; }
		return _merge_move_routine<Replace>(other);
	}

	private:
	template <bool Multi_Other, typename Comparator_Other, bool _ = Multi, typename = ::std::enable_if_t<_>>
	void
	_merge_move (binary_tree_base<Node, Multi_Other, Comparator_Other, Allocator> &other)
	{
		if(_size == 0) {
			if constexpr(::std::is_same_v<Comparator, Comparator_Other>) _move_structure(::std::move(other));
			else                                                         _move_nodes    (::std::move(other));
			other._reset(); }
		else _merge_move_routine(other);
	}

	private:
	template <bool Replace, bool Multi_Other, typename Comparator_Other, bool _ = !Multi, typename = ::std::enable_if_t<_>>
	size_t
	_merge_move_routine (binary_tree_base<Node, Multi_Other, Comparator_Other, Allocator> &other)
	{
		size_t count = 0;
		for(_Node *node1 = other._begin(), *node2; node1 != &other._head; node1 = node2) {
			node2 = _Iteration::_<1>(node1); count += _transfer_move<Replace>(other, node1).second; }
		return count;
	}

	private:
	template <bool Multi_Other, typename Comparator_Other, bool _ = Multi, typename = ::std::enable_if_t<_>>
	void
	_merge_move_routine (binary_tree_base<Node, Multi_Other, Comparator_Other, Allocator> &other)
	{
		for(_Node *node1 = other._begin(), *node2; node1 != &other._head; node1 = node2) {
			node2 = _Iteration::_<1>(node1); _transfer_move(other, node1); }
	}

	private:
	template <bool Replace, typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other,
	          bool _ = !Multi, typename = ::std::enable_if_t<_>>
	size_t
	_merge_copy (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		if(_size == 0) {
			if constexpr(::std::is_same_v<Comparator, Comparator_Other>) _copy_structure(other);
			else                                                         _copy_nodes    (other);
			other.clear(); return _size; }
		return _merge_copy_routine<Replace>(other);
	}

	private:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other,
	          bool _ = Multi, typename = ::std::enable_if_t<_>>
	void
	_merge_copy (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		if(_size == 0) {
			if constexpr(::std::is_same_v<Comparator, Comparator_Other>) _copy_structure(other);
			else                                                         _copy_nodes    (other);
			other.clear(); }
		else _merge_copy_routine(other);
	}

	private:
	template <bool Replace, typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other,
	          bool _ = !Multi, typename = ::std::enable_if_t<_>>
	size_t
	_merge_copy_routine (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		size_t count = 0;
		for(typename Node_Other::_Base *node1 = other._begin(), *node2; node1 != &other._head; node1 = node2) {
			node2 = _Iteration::_<1>(node1); count += _transfer_copy<Replace>(other, node1).second; }
		return count;
	}

	private:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other,
	          bool _ = Multi, typename = ::std::enable_if_t<_>>
	void
	_merge_copy_routine (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		for(typename Node_Other::_Base *node1 = other._begin(), *node2; node1 != &other._head; node1 = node2) {
			node2 = _Iteration::_<1>(node1); _transfer_copy(other, node1); }
	}
	/* === Merge === */
	/* ##################### External Tree Management ###################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ####################### Comparison operators ######################## */
	/* === Equal === */
	protected:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	bool
	_equal_to (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		if(_size != other._size) return false;
		_Node *node = _begin(); typename Node_Other::_Base *node_other = other._begin();
		for( ; node != &_head && node_other != &other._head;
			   node = _Iteration::_<1>(node), node_other = _Iteration::_<1>(node_other))
			if(_comparator(**node, **node_other) || _comparator(**node_other, **node)) return false;
		return true;
	}

	protected:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	bool
	_equal_to (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{
		if(_size != other._size) return false;
		const _Node *node = _begin(); const typename Node_Other::_Base *node_other = other._begin();
		for( ; node != &_head && node_other != &other._head;
			   node = _Iteration::_<1>(node), node_other = _Iteration::_<1>(node_other))
			if(_comparator(**node, **node_other) || _comparator(**node_other, **node)) return false;
		return true;
	}
	/* === Equal === */


	/* === Lesser === */
	protected:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	bool
	_lesser_than (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		_Node *node = _begin(); typename Node_Other::_Base *node_other = other._begin();
		for( ; node != &_head && node_other != &other._head;
			   node = _Iteration::_<1>(node), node_other = _Iteration::_<1>(node_other)) {
			if(_comparator(**node, **node_other)) return true;
			if(_comparator(**node_other, **node)) return false; }
		return node == &_head && node_other != &other._head;
	}

	protected:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	bool
	_lesser_than (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{
		const _Node *node = _begin(); const typename Node_Other::_Base *node_other = other._begin();
		for( ; node != &_head && node_other != &other._head;
			   node = _Iteration::_<1>(node), node_other = _Iteration::_<1>(node_other)) {
			if(_comparator(**node, **node_other)) return true;
			if(_comparator(**node_other, **node)) return false; }
		return node == &_head && node_other != &other._head;
	}
	/* === Lesser === */


	/* === Greater === */
	protected:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	bool
	_greater_than (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		_Node *node = _begin(); typename Node_Other::_Base *node_other = other._begin();
		for( ; node != &_head && node_other != &other._head;
			   node = _Iteration::_<1>(node), node_other = _Iteration::_<1>(node_other)) {
			if(_comparator(**node_other, **node)) return true;
			if(_comparator(**node, **node_other)) return false; }
		return node != &_head && node_other == &other._head;
	}

	protected:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	bool
	_greater_than (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{
		const _Node *node = _begin(); const typename Node_Other::_Base *node_other = other._begin();
		for( ; node != &_head && node_other != &other._head;
			   node = _Iteration::_<1>(node), node_other = _Iteration::_<1>(node_other)) {
			if(_comparator(**node_other, **node)) return true;
			if(_comparator(**node, **node_other)) return false; }
		return node != &_head && node_other == &other._head;
	}
	/* === Greater === */


	/* === Spaceship === */
	protected:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	int
	_spaceship (binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	{
		_Node *node = _begin(); typename Node_Other::_Base *node_other = other._begin();
		for( ; node != &_head && node_other != &other._head;
			   node = _Iteration::_<1>(node), node_other = _Iteration::_<1>(node_other)) {
			if(_comparator(**node, **node_other)) return -1;
			if(_comparator(**node_other, **node)) return 1; }
		return node == &_head ? (node_other != &other._head ? -1 : 0) : 1;
	}

	protected:
	template <typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	int
	_spaceship (const binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &other)
	const
	{
		const _Node *node = _begin(); const typename Node_Other::_Base *node_other = other._begin();
		for( ; node != &_head && node_other != &other._head;
			   node = _Iteration::_<1>(node), node_other = _Iteration::_<1>(node_other)) {
			if(_comparator(**node, **node_other)) return -1;
			if(_comparator(**node_other, **node)) return 1; }
		return node == &_head ? (node_other != &other._head ? -1 : 0) : 1;
	}
	/* === Spaceship === */
	/* ####################### Comparison operators ######################## */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ###################### Traversors / Iterators ####################### */
	protected:
	inline       _Node * _begin ()       { if constexpr(!Node::_Threaded) return _head._down[1]; else return _head._thread[1];}
	inline const _Node * _begin () const { if constexpr(!Node::_Threaded) return _head._down[1]; else return _head._thread[1];}
	inline       _Node *_rbegin ()       { if constexpr(!Node::_Threaded) return _head._down[0]; else return _head._thread[0];}
	inline const _Node *_rbegin () const { if constexpr(!Node::_Threaded) return _head._down[0]; else return _head._thread[0];}
	/* ###################### Traversors / Iterators ####################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################# Modifiers ############################# */
	/* === Clear === */
	protected:
	inline void
	_clear ()
	{ if constexpr(!Node::_Threaded) _clear_routine(_head._up); else _clear_routine(_head._thread[1], &_head); }

	private:
	template <typename = ::std::enable_if_t<!Node::_Threaded>>
	void
	_clear_routine (_Node *node)
	{
		for(_Node *save; node != nullptr; node = save) {
			if(node->_down[0] != nullptr) _clear_routine(node->_down[0]);
			save = node->_down[1];
			_del_node(node); }
	}

	private:
	template <typename = ::std::enable_if_t<Node::_Threaded>, typename = void>
	void
	_clear_routine (_Node *begin, _Node *end)
	{ for(_Node *node; begin != end; begin = node) { node = begin->_thread[1]; _del_node(begin); } }
	/* === Clear === */


	/* === Place === */
	protected:
	template <bool _ = !Multi, typename = ::std::enable_if_t<_>>
	_Node *
	_place (int &side, const typename Node::_Key &key)
	{
		if(_head._up == nullptr) { side = 0; return &_head; }
		_Node *node = _head._up, *save = nullptr;
		for( ; ; ) {
			if(_comparator(key, **node))
				 {              if(node->_down[0]) node = node->_down[0]; else { side = 0; break; } }
			else { save = node; if(node->_down[1]) node = node->_down[1]; else { side = 1; break; } } }
		if(save == nullptr) { side = 0; return node; }
		if(_comparator(**save, key)) return node;
		side = -1; return save;
	}

	protected:
	template <bool _ = !Multi, typename = ::std::enable_if_t<_>>
	const _Node *
	_place (int &side, const typename Node::_Key &key)
	const
	{
		if(_head._up == nullptr) { side = 0; return &_head; }
		const _Node *node = _head._up, *save = nullptr;
		for( ; ; ) {
			if(_comparator(key, **node))
				 {              if(node->_down[0]) node = node->_down[0]; else { side = 0; break; } }
			else { save = node; if(node->_down[1]) node = node->_down[1]; else { side = 1; break; } } }
		if(save == nullptr) { side = 0; return node; }
		if(_comparator(**save, key)) return node;
		side = -1; return save;
	}

	protected:
	template <bool _ = Multi, typename = ::std::enable_if_t<_>, typename = void>
	_Node *
	_place (int &side, const typename Node::_Key &key)
	{
		if(_head._up == nullptr) { side = 0; return &_head; }
		for(_Node *node = _head._up; ; ) {
			if(_comparator(key, **node))
				 { if(node->_down[0]) node = node->_down[0]; else { side = 0; return node; } }
			else { if(node->_down[1]) node = node->_down[1]; else { side = 1; return node; } } }
	}

	protected:
	template <bool _ = Multi, typename = ::std::enable_if_t<_>, typename = void>
	const _Node *
	_place (int &side, const typename Node::_Key &key)
	const
	{
		if(_head._up == nullptr) { side = 0; return &_head; }
		for(const _Node *node = _head._up; ; ) {
			if(_comparator(key, **node))
				 { if(node->_down[0]) node = node->_down[0]; else { side = 0; return node; } }
			else { if(node->_down[1]) node = node->_down[1]; else { side = 1; return node; } } }
	}

	protected:
	template <bool _ = !Multi, typename = ::std::enable_if_t<_>>
	_Node *
	_place_hint (_Node *hint, int &side, const typename Node::_Key &key)
	{
		if(_head._up == nullptr) { side = 0; return &_head; }
		_Node *node1 = _Iteration::_<0>(hint), *node2 = _Iteration::_<1>(hint);
		if(hint == &_head) {
			if( _comparator(**node1, key)) { side =  1; return node1; }
			if( _comparator(key, **node2)) { side =  0; return node2; }
			if(!_comparator(key, **node1)) { side = -1; return node1; }
			if(!_comparator(**node2, key)) { side = -1; return node2; }
											  return _place(side, key); }
		else if(_comparator(key, **hint)) {
			if(node1 == &_head)            { side =  0; return hint;  }
			if( _comparator(key, **node1))    return _place(side, key);
			if(!_comparator(**node1, key)) { side = -1; return node1; }
			if(hint->_down[0] == nullptr)  { side =  0; return hint;  }
			                                 side =  1; return node1; }
		else if(_comparator(**hint, key)) {
			if(node2 == &_head)            { side =  1; return hint;  }
			if( _comparator(**node2, key))    return _place(side, key);
			if(!_comparator(key, **node2)) { side = -1; return node2; }
			if(hint->_down[1] == nullptr)  { side =  1; return hint;  }
			                                 side =  0; return node2; }
		else                               { side = -1; return hint;  }
	}

	protected:
	template <bool _ = !Multi, typename = ::std::enable_if_t<_>>
	const _Node *
	_place_hint (const _Node *hint, int &side, const typename Node::_Key &key)
	const
	{
		if(_head._up == nullptr) { side = 0; return &_head; }
		const _Node *node1 = _Iteration::_<0>(hint), *node2 = _Iteration::_<1>(hint);
		if(hint == &_head) {
			if( _comparator(**node1, key)) { side =  1; return node1; }
			if( _comparator(key, **node2)) { side =  0; return node2; }
			if(!_comparator(key, **node1)) { side = -1; return node1; }
			if(!_comparator(**node2, key)) { side = -1; return node2; }
											  return _place(side, key); }
		else if(_comparator(key, **hint)) {
			if(node1 == &_head)            { side =  0; return hint;  }
			if( _comparator(key, **node1))    return _place(side, key);
			if(!_comparator(**node1, key)) { side = -1; return node1; }
			if(hint->_down[0] == nullptr)  { side =  0; return hint;  }
			                                 side =  1; return node1; }
		else if(_comparator(**hint, key)) {
			if(node2 == &_head)            { side =  1; return hint;  }
			if( _comparator(**node2, key))    return _place(side, key);
			if(!_comparator(key, **node2)) { side = -1; return node2; }
			if(hint->_down[1] == nullptr)  { side =  1; return hint;  }
			                                 side =  0; return node2; }
		else                               { side = -1; return hint;  }
	}

	protected:
	template <bool _ = Multi, typename = ::std::enable_if_t<_>, typename = void>
	_Node *
	_place_hint (_Node *hint, int &side, const typename Node::_Key &key)
	{
		if(_head._up == nullptr) { side = 0; return &_head; }
		_Node *node1 = _Iteration::_<0>(hint), *node2 = _Iteration::_<1>(hint);
		if(hint == &_head) {
			if(!_comparator(key, **node1)) { side = 1; return node1; }
			if( _comparator(key, **node2)) { side = 0; return node2; }
			                                 return _place(side, key); }
		else if(_comparator(key, **hint)) {
			if(node1 == &_head)            { side = 0; return hint;  }
			if( _comparator(key, **node1))   return _place(side, key);
			if(hint->_down[0] == nullptr)  { side = 0; return hint;  }
			                                 side = 1; return node1; }
		else {
			if(node2 == &_head)            { side = 1; return hint;  }
			if(!_comparator(key, **node2))   return _place(side, key);
			if(hint->_down[1] == nullptr)  { side = 1; return hint;  }
			                                 side = 0; return node2; }
	}

	protected:
	template <bool _ = Multi, typename = ::std::enable_if_t<_>, typename = void>
	const _Node *
	_place_hint (const _Node *hint, int &side, const typename Node::_Key &key)
	const
	{
		if(_head._up == nullptr) { side = 0; return &_head; }
		const _Node *node1 = _Iteration::_<0>(hint), *node2 = _Iteration::_<1>(hint);
		if(hint == &_head) {
			if(!_comparator(key, **node1)) { side = 1; return node1; }
			if( _comparator(key, **node2)) { side = 0; return node2; }
			                                 return _place(side, key); }
		else if(_comparator(key, **hint)) {
			if(node1 == &_head)            { side = 0; return hint;  }
			if( _comparator(key, **node1))   return _place(side, key);
			if(hint->_down[0] == nullptr)  { side = 0; return hint;  }
			                                 side = 1; return node1; }
		else {
			if(node2 == &_head)            { side = 1; return hint;  }
			if(!_comparator(key, **node2))   return _place(side, key);
			if(hint->_down[1] == nullptr)  { side = 1; return hint;  }
			                                 side = 0; return node2; }
	}
	/* === Place === */


	/* === Insert === */
	protected:
	template <typename Arg>
	::std::pair<_Node *, bool>
	_insert_bottom (Arg &&info)
	{
		int side; _Node *place = _place(side, _Node::key(::std::forward<Arg>(info)));
		if(!Multi && side == -1) return {place, false};
		else                     return {_insert_place_bottom(side, place, ::std::forward<Arg>(info)), true};
	}

	protected:
	template <typename Arg>
	::std::pair<_Node *, bool>
	_insert_hint_bottom (_Node *hint, Arg &&info)
	{
		int side; _Node *place = _place_hint(hint, side, _Node::key(::std::forward<Arg>(info)));
		if(!Multi && side == -1) return {place, false};
		else                     return {_insert_place_bottom(side, place, ::std::forward<Arg>(info)), true};
	}

	protected:
	template <typename Arg, typename = ::std::enable_if_t<!Node::_Threaded>>
	_Node *
	_insert_place_bottom (int side, _Node *place, Arg &&info)
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

	protected:
	template <typename Arg, typename = ::std::enable_if_t<Node::_Threaded>, typename = void>
	_Node *
	_insert_place_bottom (int side, _Node *place, Arg &&info)
	{
		if(place == &_head) {
			_head._up = _new_node(&_head, &_head, &_head, ::std::forward<Arg>(info));
			_head._thread[0] = _head._up; _head._thread[1] = _head._up;
			return _head._up; }
		if(side == 0) {
			_Node *node = _new_node(place, place->_thread[0], place, ::std::forward<Arg>(info)); place->_down[0] = node;
			place->_thread[0]->_thread[1] = node; place->_thread[0] = node;
			return node; }
		else {
			_Node *node = _new_node(place, place, place->_thread[1], ::std::forward<Arg>(info)); place->_down[1] = node;
			place->_thread[1]->_thread[0] = node; place->_thread[1] = node;
			return node; }
	}
	/* === Insert === */


	/* === Emplace === */
	protected:
	::std::pair<_Node *, bool>
	_emplace_bottom (_Node *node)
	{
		int side; _Node *place = _place(side, **node);
		if(!Multi && side == -1) return {place, false};
		else { _emplace_place_bottom(side, place, node); return {node, true}; }
	}

	protected:
	::std::pair<_Node *, bool>
	_emplace_hint_bottom (_Node *hint, _Node *node)
	{
		int side; _Node *place = _place_hint(hint, side, **node);
		if(!Multi && side == -1) return {place, false};
		else { _emplace_place_bottom(side, place, node); return {node, true}; }
	}

	protected:
	template <typename = ::std::enable_if_t<!Node::_Threaded>>
	void
	_emplace_place_bottom (int side, _Node *place, _Node *node)
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

	protected:
	template <typename = ::std::enable_if_t<Node::_Threaded>, typename = void>
	void
	_emplace_place_bottom (int side, _Node *place, _Node *node)
	{
		if(place == &_head) {
			_head._up = node; _update_node(node, &_head, &_head, &_head);
			_head._thread[0] = node; _head._thread[1] = node; }
		if(side == 0) {
			place->_down[0] = node; _update_node(node, place, place->_thread[0], place);
			place->_thread[0]->_thread[1] = node; place->_thread[0] = node; }
		else {
			place->_down[1] = node; _update_node(node, place, place, place->_thread[1]);
			place->_thread[1]->_thread[0] = node; place->_thread[1] = node; }
	}
	/* === Emplace === */
	/* ############################# Modifiers ############################# */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ########################### Node rotation ########################### */
	protected:
	void
	_rotate_left (_Node *parent)
	{ _rotate_left(parent, parent->_down[1]); }

	protected:
	void
	_rotate_left (_Node *parent, _Node *son)
	{
		parent->_down[1] = son->_down[0];
		son->_down[0] = parent;
		son->_up = parent->_up;
		parent->_up = son;
		if(parent->_down[1] != nullptr) parent->_down[1]->_up = parent;
		if(son->_up == &_head)                   _head._up = son;
		else son->_up->_down[parent == son->_up->_down[1]] = son;
	}

	protected:
	void
	_rotate_right (_Node *parent)
	{ _rotate_right(parent, parent->_down[0]); }

	protected:
	void
	_rotate_right (_Node *parent, _Node *son)
	{
		parent->_down[0] = son->_down[1];
		son->_down[1] = parent;
		son->_up = parent->_up;
		parent->_up = son;
		if(parent->_down[0] != nullptr) parent->_down[0]->_up = parent;
		if(son->_up == &_head)                   _head._up = son;
		else son->_up->_down[parent == son->_up->_down[1]] = son;
	}

	protected:
	void
	_rotate_left_right (_Node *grandparent)
	{ _rotate_left_right(grandparent, grandparent->_down[0], grandparent->_down[0]->_down[1]); }

	protected:
	void
	_rotate_left_right (_Node *grandparent, _Node *parent, _Node *son)
	{
		son->_up = grandparent->_up;
		parent->_up = son; grandparent->_up = son;
		grandparent->_down[0] = son->_down[1];
		parent->_down[1] = son->_down[0];
		son->_down[0] = parent;
		son->_down[1] = grandparent;
		if(     parent->_down[1] != nullptr)      parent->_down[1]->_up =      parent;
		if(grandparent->_down[0] != nullptr) grandparent->_down[0]->_up = grandparent;
		if(son->_up == &_head)                        _head._up = son;
		else son->_up->_down[grandparent == son->_up->_down[1]] = son;
	}

	protected:
	void
	_rotate_right_left (_Node *grandparent)
	{ _rotate_right_left(grandparent, grandparent->_down[1], grandparent->_down[1]->_down[0]); }

	protected:
	void
	_rotate_right_left (_Node *grandparent, _Node *parent, _Node *son)
	{
		son->_up = grandparent->_up;
		parent->_up = son; grandparent->_up = son;
		grandparent->_down[1] = son->_down[0];
		parent->_down[0] = son->_down[1];
		son->_down[1] = parent;
		son->_down[0] = grandparent;
		if(     parent->_down[0] != nullptr)      parent->_down[0]->_up =      parent;
		if(grandparent->_down[1] != nullptr) grandparent->_down[1]->_up = grandparent;
		if(son->_up == &_head)                        _head._up = son;
		else son->_up->_down[grandparent == son->_up->_down[1]] = son;
	}
	/* ########################### Node rotation ########################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ########################## Tree Structure ########################### */
	protected:
	void
	_cut_node (_Node *node, _Node *son)
	{
		if(node->_up == &_head)                  _head._up = son;
		else node->_up->_down[node == node->_up->_down[1]] = son;
		if(son != nullptr) son->_up = node->_up;
	}

	protected:
	void
	_remove_node (_Node *node, _Node *son, const bool del)
	{
		_cut_node(node, son);
		if constexpr(!Node::_Threaded) {
			if(_head._down[0] == node) _head._down[0] = _Iteration::_<0>(node);
			if(_head._down[1] == node) _head._down[1] = _Iteration::_<1>(node); }
		else {
			node->_thread[0]->_thread[1] = node->_thread[1];
			node->_thread[1]->_thread[0] = node->_thread[0]; }
		if(del) _del_node(node);
	}

	// protected:
	// void
	// _remove_leaf (_Node *node, const bool del)
	// { _remove_node(node, nullptr, del); }

	protected:
	void
	_remove_leaf (_Node *node, const bool del)
	{
		if(node->_up == &_head)                  _head._up = nullptr;
		else node->_up->_down[node == node->_up->_down[1]] = nullptr;
		if constexpr(!Node::_Threaded) {
			if(_head._down[0] == node) _head._down[0] = node->_up;
			if(_head._down[1] == node) _head._down[1] = node->_up; }
		else {
			node->_thread[0]->_thread[1] = node->_thread[1];
			node->_thread[1]->_thread[0] = node->_thread[0]; }
		if(del) _del_node(node);
	}

	protected:
	void
	_replace_node (_Node *node1, _Node *node2, const bool del)
	{
		node2->_up = node1->_up;
		node2->_down[0] = node1->_down[0];
		node2->_down[1] = node1->_down[1];
		if(node1->_up == &_head)                    _head._up = node2;
		else node1->_up->_down[node1 == node1->_up->_down[1]] = node2;
		if(node1->_down[0] != nullptr) node1->_down[0]->_up = node2;
		if(node1->_down[1] != nullptr) node1->_down[1]->_up = node2;
		if constexpr(!Node::_Threaded) {
			if(_head._down[0] == node1) _head._down[0] = node2;
			if(_head._down[1] == node1) _head._down[1] = node2; }
		else {
			node1->_thread[0]->_thread[1] = node1->_thread[1];
			node1->_thread[1]->_thread[0] = node1->_thread[0]; }
		if(del) _del_node(node1);
	}
	/* ########################## Tree Structure ########################### */
	/* ##################################################################### */


	/* ##################################################################### */
	/* ############################## Lookup ############################### */
	/* === Find === */
	protected:
	template <typename Key>
	_Node *
	_find (const Key &key)
	{
		_Node *node = _head._up, *save = &_head;
		while(node != nullptr) {
			if(_comparator(**node, key)) node = node->_down[1];
			else          { save = node; node = node->_down[0]; } }
		return save == &_head || _comparator(key, **save) ? &_head : save;
	}

	protected:
	template <typename Key>
	const _Node *
	_find (const Key &key)
	const
	{
		const _Node *node = _head._up, *save = &_head;
		while(node != nullptr) {
			if(_comparator(**node, key)) node = node->_down[1];
			else          { save = node; node = node->_down[0]; } }
		return save == &_head || _comparator(key, **save) ? &_head : save;
	}
	/* === Find === */


	/* === Find (short) === */
	protected:
	template <typename Key>
	_Node *
	_find_short (const Key &key)
	{
		_Node *node = _head._up;
		while(node != nullptr) {
			if     (_comparator(**node, key)) node = node->_down[1];
			else if(_comparator(key, **node)) node = node->_down[0];
			else                              return node; }
		return &_head;
	}

	protected:
	template <typename Key>
	const _Node *
	_find_short (const Key &key)
	const
	{
		const _Node *node = _head._up;
		while(node != nullptr) {
			if     (_comparator(**node, key)) node = node->_down[1];
			else if(_comparator(key, **node)) node = node->_down[0];
			else                              return node; }
		return &_head;
	}
	/* === Find (short) === */


	/* === Lower bound === */
	protected:
	template <typename Key>
	_Node *
	_lower_bound (const Key &key)
	{
		_Node *node = _head._up, *save = &_head;
		while(node != nullptr) {
			if(_comparator(**node, key)) node = node->_down[1];
			else          { save = node; node = node->_down[0]; } }
		return save;
	}

	protected:
	template <typename Key>
	const _Node *
	_lower_bound (const Key &key)
	const
	{
		const _Node *node = _head._up, *save = &_head;
		while(node != nullptr) {
			if(_comparator(**node, key)) node = node->_down[1];
			else          { save = node; node = node->_down[0]; } }
		return save;
	}
	/* === Lower bound === */


	/* === Upper bound === */
	protected:
	template <typename Key>
	_Node *
	_upper_bound (const Key &key)
	{
		_Node *node = _head._up, *save = &_head;
		while(node != nullptr) {
			if(!_comparator(key, **node)) node = node->_down[1];
			else           { save = node; node = node->_down[0]; } }
		return save;
	}

	protected:
	template <typename Key>
	const _Node *
	_upper_bound (const Key &key)
	const
	{
		const _Node *node = _head._up, *save = &_head;
		while(node != nullptr) {
			if(!_comparator(key, **node)) node = node->_down[1];
			else           { save = node; node = node->_down[0]; } }
		return save;
	}
	/* === Upper bound === */
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
		if(node->_down[1] != nullptr)
			_print<Verbose>(printer, side == 0 ? branches | (1 << (depth - 1)) : branches, depth + 1, 1, node->_down[1]);
		if(depth == 0) printf("%s\u2574", node->_up == &_head ? "\u2500" : "\u2504");
		else           printf("  ");
		if(depth > 1) {
			for(ushort i = 0; i < depth - 1; ++i) {
				if((branches >> i) & 1) printf("\u2502   ");
				else                    printf("    "); } }
		if(depth > 0) {
			if(side == 0) printf("\u2514\u2500\u2500\u2574");
			else          printf("\u250c\u2500\u2500\u2574"); }
		if(Verbose) node->cast()->print();
		printer(node->info()); printf("\n");
		if(node->_down[0] != nullptr)
			_print<Verbose>(printer, side == 1 ? branches | (1 << (depth - 1)) : branches, depth + 1, 0, node->_down[0]);
	}

	private:
	template <bool Verbose, typename Printer>
	void
	_print (const Printer &printer, int_fast64_t branches, ushort depth, bool side, const _Node *node)
	const
	{
		if(node->_down[1] != nullptr)
			_print<Verbose>(printer, side == 0 ? branches | (1 << (depth - 1)) : branches, depth + 1, 1, node->_down[1]);
		if(depth == 0) printf("%s\u2574", node->_up == &_head ? "\u2500" : "\u2504");
		else           printf("  ");
		if(depth > 1) {
			for(ushort i = 0; i < depth - 1; ++i) {
				if((branches >> i) & 1) printf("\u2502   ");
				else                    printf("    "); } }
		if(depth > 0) {
			if(side == 0) printf("\u2514\u2500\u2500\u2574");
			else          printf("\u250c\u2500\u2500\u2574"); }
		if(Verbose) node->cast()->print();
		printer(node->info()); printf("\n");
		if(node->_down[0] != nullptr)
			_print<Verbose>(printer, side == 1 ? branches | (1 << (depth - 1)) : branches, depth + 1, 0, node->_down[0]);
	}
	/* ############################### Print ############################### */
	/* ##################################################################### */
};

#endif
