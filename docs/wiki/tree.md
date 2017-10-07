# Tree Library

## Binary Trees

* [`gmd::binary_tree_set`](binary_tree/set.md)
* [`gmd::binary_tree_multiset`](binary_tree/multiset.md)
* [`gmd::binary_tree_map`](binary_tree/map.md)
* [`gmd::binary_tree_multimap`](binary_tree/multimap.md)

#### Tree types

`tree_bs`&emsp;A **binary search tree** is the basic binary tree structure, with no specific behaviour.

`tree_splay`&emsp;A **splay tree** is a basic binary tree with an additional *splaying* procedure, performed every time an element is accessed. This procedure re-arranges the tree so that a specific element stands at the root.

`tree_gsplay`&emsp;A **gradual splay tree** is a variant of the *splay tree*, the difference being that the *splaying* procedure places the element one level above, rather than at the root.

`tree_streap`&emsp;A **streap tree** is a combination of the *splay* and *treap* trees. Each element contains an additional variable *key*, whose value is used to control the element's position in the tree (*treap*) and incremented whenever the element is accessed (*splay*).

`tree_treap`&emsp;A **treap tree** is a binary tree implementation of a *heap*. Each element contains an additional variable *key*, whose value is randomly set at creation and used to control the element's position in the tree.

`tree_random`&emsp;A **random tree** is a basic binary tree with a probabilistic placement criteria at element insertion. When traversing the tree to find the place for the new element, the inserting method checks if the new element should be placed at the current level, based on the size of the subtree. The larger the size, the lower the probability.

`tree_wb`&emsp;A **weight-balanced tree** keeps its balance by limiting the ratio between the weights of the left and right sub-trees of every node, which can be controlled by a factor &#945;. In this implementation, &#945; is set to 0.25.

`tree_scapegoat`&emsp;A **scapegoat tree** keeps its balance by limiting the ratio between the height and the logarithm of the weight of the tree, the base of which can be controlled by a factor &#945;. In this implementation, &#945; is set to 0.575.

`tree_aa`&emsp;An **Arne Andersson tree** is a binary tree implementation of a *2-3 tree*. It is a height-balanced tree.

`tree_rb`&emsp;A **red-black tree** is a binary tree implementation of a *2-3-4 tree*. It is a height-balanced tree.

`tree_avl`&emsp;An **Adelson-Velsky and Landis tree** is a height-balanced tree. It keeps it balancing by limiting the height difference of the left and right sub-trees of every node to at most 1.

#### Type conversion

A tree structure can be replicated between containers if either both tree types are the same or the type of the destination container is one of the first four (`bs`, `splay`, `gsplay`, `streap`). Additionally, either both containers must be of the same `multi`-type or the destination container must allow duplicate elements. Also note that during `swap()`, when the transferral of elements is performed both ways, the implementation allows structure replication to be done one way only.

---

## Space Partitioning Trees

### Point K-D Trees

* [`gmd::point_kd_tree_set`](point_kd_tree/set.md)
* [`gmd::point_kd_tree_multiset`](point_kd_tree/multiset.md)
* [`gmd::point_kd_tree_map`](point_kd_tree/map.md)
* [`gmd::point_kd_tree_multimap`](point_kd_tree/multimap.md)

#### Type conversion

A tree structure can be replicated between containers if both tree types are of the same `Balanced`-type or the destination container is not self-balancing. Additionally, either both containers must be of the same `multi`-type or the destination container must allow duplicate elements. Also note that during `swap()`, when the transferral of elements is performed both ways, the implementation allows structure replication to be done one way only.
