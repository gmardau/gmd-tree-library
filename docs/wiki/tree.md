# Tree Library

## Binary Trees

* [`gmd::binary_tree_set`](binary_tree/set.md)
* [`gmd::binary_tree_multiset`](binary_tree/multiset.md)
* [`gmd::binary_tree_map`](binary_tree/map.md)
* [`gmd::binary_tree_multimap`](binary_tree/multimap.md)

---

### Tree types

```cpp
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
```

<!-- `tree_bs`&emsp;A **binary search tree** is the

`tree_splay`&emsp;A **splay tree** is the

`tree_gsplay`&emsp;

`tree_streap`&emsp;

`tree_treap`&emsp;

`tree_random`&emsp;

`tree_wb`&emsp;

`tree_scapegoat`&emsp;

`tree_aa`&emsp;

`tree_rb`&emsp;

`tree_avl`&emsp; -->

### Type conversion

Whenever there is a transferral of multiple elements between two containers, it can be advantageous to replicate the structure of the source container into the destination container, as it avoids the additional self-balancing procedures that normal element insertion usually implies.

For a container to be able to accept a tree structure from another container either the tree types need to be the same or the type of the destination container needs to be one of the first four (`bs`, `splay`, `gsplay`, `streap`). Additionally, either both containers must be of the same `multi`-type or the destination container must allow duplicate elements.

Also note that during `swap()`, when the transferral of elements is performed both ways, the implementation allows structure replication to be done one way and not the other.

<!-- ## Space Partitioning Trees -->
