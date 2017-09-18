#ifndef _GMD_TREE_
#define _GMD_TREE_

namespace gmd {

/* ######################################################################### */
/* ############################## Binary Tree ############################## */
enum binary_tree_type {
	tree_bs,            // Binary search tree
	tree_splay,         // Splay tree
	tree_gsplay,        // Gradual splay tree
	tree_streap,        // Streap tree
	tree_treap,         // Treap tree
	tree_random,        // Random tree
	tree_wb,            // Weight-balanced tree
	tree_scapegoat,     // Scapegoat tree
	tree_aa,            // Arne Andersson tree
	tree_rb,            // Red-black tree
	tree_avl,           // Adelson-Velsky and Landis tree
};

template <binary_tree_type T> constexpr bool _binary_tree_use_structure_v =
	T == tree_bs || T == tree_splay || T == tree_gsplay || T == tree_streap;

#include "binary_tree/traversor.hpp"
#include "binary_tree/base.hpp"

template <binary_tree_type Tree, typename Key, typename Value, typename Info, bool SetMap, bool Threaded>
struct binary_tree_node;

template <binary_tree_type Tree, typename Node, bool Multi, typename Comparator, typename Allocator>
struct binary_tree_subbase;

#include "binary_tree/bs.hpp"
#include "binary_tree/splay.hpp"
#include "binary_tree/gsplay.hpp"
#include "binary_tree/streap.hpp"
#include "binary_tree/treap.hpp"
#include "binary_tree/random.hpp"
#include "binary_tree/wb.hpp"
#include "binary_tree/scapegoat.hpp"
#include "binary_tree/aa.hpp"
#include "binary_tree/rb.hpp"
#include "binary_tree/avl.hpp"

template <binary_tree_type Tree, typename Key, bool Threaded = false, typename Comparator = ::std::less<Key>,
		  typename Allocator = ::std::allocator<Key>>
struct binary_tree_set
:  public binary_tree_subbase<Tree, binary_tree_node<Tree, Key, Key, Key, 0, Threaded>, false, Comparator, Allocator>
{
	private: using _Base = binary_tree_subbase<Tree, binary_tree_node<Tree, Key, Key, Key, 0, Threaded>, false, Comparator, Allocator>;
	public: using _Base::_Base; using _Base::operator=;
	using value_compare = Comparator;
};

template <binary_tree_type Tree, typename Key, bool Threaded = false, typename Comparator = ::std::less<Key>,
		  typename Allocator = ::std::allocator<Key>>
struct binary_tree_multiset
: public binary_tree_subbase<Tree, binary_tree_node<Tree, Key, Key, Key, 0, Threaded>, true, Comparator, Allocator>
{
	private: using _Base = binary_tree_subbase<Tree, binary_tree_node<Tree, Key, Key, Key, 0, Threaded>, true, Comparator, Allocator>;
	public: using _Base::_Base; using _Base::operator=;
	using value_compare = Comparator;
};

template <binary_tree_type Tree, typename Key, typename Value, bool Threaded = false, typename Comparator = ::std::less<Key>,
		  typename Allocator = ::std::allocator<::std::pair<Key, Value>>>
struct binary_tree_map
: public binary_tree_subbase<Tree, binary_tree_node<Tree, Key, Value, ::std::pair<Key, Value>, 1, Threaded>,
                             false, Comparator, Allocator>
{
	private: using _Base = binary_tree_subbase<Tree, binary_tree_node<Tree, Key, Value, ::std::pair<Key, Value>, 1, Threaded>,
	                                           false, Comparator, Allocator>;
	public: using _Base::_Base; using _Base::operator=;
	using mapped_type = Value;
	using value_compare = typename _Base::Info_Comparator;
};

template <binary_tree_type Tree, typename Key, typename Value, bool Threaded = false, typename Comparator = ::std::less<Key>,
		  typename Allocator = ::std::allocator<::std::pair<Key, Value>>>
struct binary_tree_multimap
: public binary_tree_subbase<Tree, binary_tree_node<Tree, Key, Value, ::std::pair<Key, Value>, 1, Threaded>,
                             true, Comparator, Allocator>
{
	private: using _Base = binary_tree_subbase<Tree, binary_tree_node<Tree, Key, Value, ::std::pair<Key, Value>, 1, Threaded>,
	                                           true, Comparator, Allocator>;
	public: using _Base::_Base; using _Base::operator=;
	using mapped_type = Value;
	using value_compare = typename _Base::Info_Comparator;
};

template <binary_tree_type Tree, typename Key, typename Comparator = ::std::less<Key>,
		  typename Allocator = ::std::allocator<Key>>
	using binary_tree = binary_tree_set<Tree, Key, false, Comparator, Allocator>;

/* Best choice would be a B-tree */
// template <typename Key,                 typename Comparator = ::std::less<Key>,
// 	      typename Allocator = ::std::allocator<Key>>
// 	using      set = binary_tree_set     <tree_avl, Key, false, Comparator, Allocator>;
// template <typename Key,                 typename Comparator = ::std::less<Key>,
// 	      typename Allocator = ::std::allocator<Key>>
// 	using multiset = binary_tree_multiset<tree_avl, Key, false, Comparator, Allocator>;
// template <typename Key, typename Value, typename Comparator = ::std::less<Key>,
// 	      typename Allocator = ::std::allocator<::std::pair<Key, Value>>>
// 	using      map = binary_tree_map     <tree_avl, Key, Value, false, Comparator, Allocator>;
// template <typename Key, typename Value, typename Comparator = ::std::less<Key>,
// 	      typename Allocator = ::std::allocator<::std::pair<Key, Value>>>
// 	using multimap = binary_tree_multimap<tree_avl, Key, Value, false, Comparator, Allocator>;
/* ############################## Binary Tree ############################## */
/* ######################################################################### */


/* ######################################################################### */
/* ################################ B-Tree ################################# */
// #include "btree/traversor.hpp"
// #include "btree/btree.hpp"
/* ################################ B-Tree ################################# */
/* ######################################################################### */


/* ######################################################################### */
/* ############################### K-D Tree ################################ */
#include "kd_tree/point_traversor.hpp"
#include "kd_tree/point_kd_tree.hpp"

template <size_t K, typename Key, typename Comparator, bool Balanced = false, typename Equal = ::std::equal_to<Key>,
		  typename Allocator = ::std::allocator<Key>, typename = ::std::enable_if_t<(K >= 1)>>
struct point_kd_tree_set
: public point_kd_tree_base<K, point_kd_tree_node<Key, Key, Key, 0, Balanced>, false, Comparator, Equal, Allocator>
{
	private:
	using _Base = point_kd_tree_base<K, point_kd_tree_node<Key, Key, Key, 0, Balanced>, false, Comparator, Equal, Allocator>;
	public: using _Base::_Base; using _Base::operator=;
	using value_compare = Comparator;
	using value_equal   = Equal;
};

template <size_t K, typename Key, typename Comparator, bool Balanced = false, typename Equal = ::std::equal_to<Key>,
		  typename Allocator = ::std::allocator<Key>, typename = ::std::enable_if_t<(K >= 1)>>
struct point_kd_tree_multiset
: public point_kd_tree_base<K, point_kd_tree_node<Key, Key, Key, 0, Balanced>, true, Comparator, Equal, Allocator>
{
	private:
	using _Base = point_kd_tree_base<K, point_kd_tree_node<Key, Key, Key, 0, Balanced>, true, Comparator, Equal, Allocator>;
	public: using _Base::_Base; using _Base::operator=;
	using value_compare = Comparator;
	using value_equal   = Equal;
};

template <size_t K, typename Key, typename Value, typename Comparator, bool Balanced = false,
		  typename Equal = ::std::equal_to<Key>, typename Allocator = ::std::allocator<::std::pair<Key, Value>>,
		  typename = ::std::enable_if_t<(K >= 1)>>
struct point_kd_tree_map
: public point_kd_tree_base<K, point_kd_tree_node<Key, Value, ::std::pair<Key, Value>, 1, Balanced>,
                            false, Comparator, Equal, Allocator>
{
	private:
	using _Base = point_kd_tree_base<K, point_kd_tree_node<Key, Value, ::std::pair<Key, Value>, 1, Balanced>,
	                                 false, Comparator, Equal, Allocator>;
	public: using _Base::_Base; using _Base::operator=;
	using mapped_type = Value;
	using value_compare = typename _Base::Info_Comparator;
	using value_equal   = typename _Base::Info_Equal;
};

template <size_t K, typename Key, typename Value, typename Comparator, bool Balanced = false,
		  typename Equal = ::std::equal_to<Key>, typename Allocator = ::std::allocator<::std::pair<Key, Value>>,
		  typename = ::std::enable_if_t<(K >= 1)>>
struct point_kd_tree_multimap
: public point_kd_tree_base<K, point_kd_tree_node<Key, Value, ::std::pair<Key, Value>, 1, Balanced>,
                            true, Comparator, Equal, Allocator>
{
	private:
	using _Base = point_kd_tree_base<K, point_kd_tree_node<Key, Value, ::std::pair<Key, Value>, 1, Balanced>,
	                                 true, Comparator, Equal, Allocator>;
	public: using _Base::_Base; using _Base::operator=;
	using mapped_type = Value;
	using value_compare = typename _Base::Info_Comparator;
	using value_equal   = typename _Base::Info_Equal;
};

// #include "kd_tree/region_kd_tree.hpp"
/* ############################### K-D Tree ################################ */
/* ######################################################################### */


/* ######################################################################### */
/* ############################### Orthtree ################################ */
// #include "orthtree/traversor.hpp"
// #include "orthtree/point_orthtree.hpp"

// template <size_t K, typename Key, typename Comparator, typename Equal = ::std::equal_to<Key>,
// 		  typename Allocator = ::std::allocator<Key>, typename = ::std::enable_if_t<(K >= 1)>>
// struct point_orthtree_set
// : public point_orthtree_base<point_orthtree_node<K, Key, Key, Key, 0>, false, Comparator, Equal, Allocator>
// {
// 	private:
// 	using _Base = point_orthtree_base<point_orthtree_node<K, Key, Key, Key, 0>, false, Comparator, Equal, Allocator>;
// 	using value_compare = Comparator;
// 	using value_equal   = Equal;
// 	public: using _Base::_Base; using _Base::operator=;
// };

// template <size_t K, typename Key, typename Comparator, typename Equal = ::std::equal_to<Key>,
// 		  typename Allocator = ::std::allocator<Key>, typename = ::std::enable_if_t<(K >= 1)>>
// struct point_orthtree_multiset
// : public point_orthtree_base<point_orthtree_node<K, Key, Key, Key, 0>, true, Comparator, Equal, Allocator>
// {
// 	private:
// 	using _Base = point_orthtree_base<point_orthtree_node<K, Key, Key, Key, 0>, true, Comparator, Equal, Allocator>;
// 	using value_compare = Comparator;
// 	using value_equal   = Equal;
// 	public: using _Base::_Base; using _Base::operator=;
// };

// template <size_t K, typename Key, typename Value, typename Comparator,
// 		  typename Equal = ::std::equal_to<Key>, typename Allocator = ::std::allocator<::std::pair<Key, Value>>,
// 		  typename = ::std::enable_if_t<(K >= 1)>>
// struct point_orthtree_map
// : public point_orthtree_base<point_orthtree_node<K, Key, Value, ::std::pair<Key, Value>, 1>,
//                              false, Comparator, Equal, Allocator>
// {
// 	private:
// 	using _Base = point_orthtree_base<point_orthtree_node<K, Key, Value, ::std::pair<Key, Value>, 1>,
// 	                                  false, Comparator, Equal, Allocator>;
// 	using mapped_type = Value;
// 	using value_compare = typename _Base::Info_Comparator;
// 	using value_equal   = typename _Base::Info_Equal;
// 	public: using _Base::_Base; using _Base::operator=;
// };

// template <size_t K, typename Key, typename Value, typename Comparator,
// 		  typename Equal = ::std::equal_to<Key>, typename Allocator = ::std::allocator<::std::pair<Key, Value>>,
// 		  typename = ::std::enable_if_t<(K >= 1)>>
// struct point_orthtree_multimap
// : public point_orthtree_base<point_orthtree_node<K, Key, Value, ::std::pair<Key, Value>, 1>,
//                              true, Comparator, Equal, Allocator>
// {
// 	private:
// 	using _Base = point_orthtree_base<point_orthtree_node<K, Key, Value, ::std::pair<Key, Value>, 1>,
// 	                                  true, Comparator, Equal, Allocator>;
// 	using mapped_type = Value;
// 	using value_compare = typename _Base::Info_Comparator;
// 	using value_equal   = typename _Base::Info_Equal;
// 	public: using _Base::_Base; using _Base::operator=;
// };

// #include "orthtree/region_orthtree.hpp"
/* ############################### Orthtree ################################ */
/* ######################################################################### */

}

/* === Non-member functions === */
namespace std
{
	template <typename Node,       bool Multi,       typename Comparator,       typename Allocator,
	          typename Node_Other, bool Multi_Other, typename Comparator_Other, typename Allocator_Other>
	::std::enable_if_t<::std::is_same_v<typename Node::_Info, typename Node_Other::_Info>, void>
	swap (::gmd::binary_tree_base<Node,       Multi,       Comparator,       Allocator>       &a,
	      ::gmd::binary_tree_base<Node_Other, Multi_Other, Comparator_Other, Allocator_Other> &b)
	{ a.swap(b); }

}
/* === Non-member functions === */

#endif
