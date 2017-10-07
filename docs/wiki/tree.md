# Tree Library

## Binary Trees

* [`gmd::binary_tree_set`](binary_tree/set.md)
* [`gmd::binary_tree_multiset`](binary_tree/multiset.md)
* [`gmd::binary_tree_map`](binary_tree/map.md)
* [`gmd::binary_tree_multimap`](binary_tree/multimap.md)

#### Tree types

<table>
<tr><td><code>tree_bs</code></td>
<td>A <b>binary search tree</b> is the basic binary tree structure, with no specific behaviour.</td>
</tr>
<tr><td><code>tree_splay</code></td>
<td>A <b>splay tree</b> is a basic binary tree with an additional <i>splaying</i> procedure, performed every time an element is accessed. This procedure re-arranges the tree so that a specific element stands at the root.</td>
</tr>
<tr><td><code>tree_gsplay</code></td>
<td>A <b>gradual splay tree</b> is a variant of the <i>splay tree</i>, the difference being that the <i>splaying</i> procedure places the element one level above, rather than at the root.</td>
</tr>
<tr><td><code>tree_streap</code></td>
<td>A <b>streap tree</b> is a combination of the <i>splay</i> and <i>treap</i> trees. Each element contains an additional variable <i>key</i>, whose value is used to control the element's position in the tree (<i>treap</i>) and incremented whenever the element is accessed (<i>splay</i>).</td>
</tr>
<tr><td><code>tree_treap</code></td>
<td>A <b>treap tree</b> is a binary tree implementation of a <i>heap</i>. Each element contains an additional variable <i>key</i>, whose value is randomly set at creation and used to control the element's position in the tree.</td>
</tr>
<tr><td><code>tree_random</code></td>
<td>A <b>random tree</b> is a basic binary tree with a probabilistic placement criteria at element insertion. When traversing the tree to find the place for the new element, the inserting method checks if the new element should be placed at the current level, based on the size of the subtree. The larger the size, the lower the probability.</td>
</tr>
<tr><td><code>tree_wb</code></td>
<td>A <b>weight-balanced tree</b> keeps its balance by limiting the ratio between the weights of the left and right sub-trees of every node, which can be controlled by a factor &#945;. In this implementation, &#945; is set to 0.25.</td>
</tr>
<tr><td><code>tree_scapegoat</code></td>
<td>A <b>scapegoat tree</b> keeps its balance by limiting the ratio between the height and the logarithm of the weight of the tree, the base of which can be controlled by a factor &#945;. In this implementation, &#945; is set to 0.575.</td>
</tr>
<tr><td><code>tree_aa</code></td>
<td>An <b>Arne Andersson tree</b> is a binary tree implementation of a <i>2-3 tree</i>. It is a height-balanced tree.</td>
</tr>
<tr><td><code>tree_rb</code></td>
<td>A <b>red-black tree</b> is a binary tree implementation of a <i>2-3-4 tree</i>. It is a height-balanced tree.</td>
</tr>
<tr><td><code>tree_avl</code></td>
<td>An <b>Adelson-Velsky and Landis tree</b> is a height-balanced tree. It keeps its balance by limiting the height difference of the left and right sub-trees of every node to at most 1.</td>
</tr>
</table>

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
