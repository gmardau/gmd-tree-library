# gmd: Point k-d tree traversal

## Traversor

The point k-d tree traversor is a structure that allows the iteration and traversal of a point k-d tree structure. It satisfies the requirements of [BidirectionalIterator](http://en.cppreference.com/w/cpp/concept/BidirectionalIterator).

---

| Member type | Definition |
|:-|:-|
| *`value_type`* | <code>(const) <i>point_kd_tree</i>::<i>value_type</i></code> |
| *`reference`* | <code><i>value_type</i> &</code> |
| *`pointer`* | <code><i>value_type</i> *</code> |
| *`iterator_category`* | [`std::bidirectional_iterator_tag`](http://en.cppreference.com/w/cpp/iterator/iterator_tags) |
| *`difference_type`* | [`std::ptrdiff_t`](http://en.cppreference.com/w/cpp/types/ptrdiff_t) |

---

Traversors can be implicitly converted to their const counterparts using constructors. However const traversors cannot be converted to non-const traversors.

---

<a name="call" href="#call">#</a> `bool` **operator()** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Checks if the traversor is valid, returning `true` if it is; `false` otherwise.

---

<a name="equal-1" href="#equal-1">#</a> `bool` **operator==** (<code>const <i>point_kd_tree_range_iterator</i> &<b>it</b></code>) `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="equal-0" href="#equal-0">#</a> `bool` **operator==** (<code>const <i>point_kd_tree_traversor</i> &<b>tr</b></code>) `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="not_equal" href="#not_equal">#</a> `bool` **operator!=** (<code>const <i>point_kd_tree_traversor</i> &<b>tr</b></code>) `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Checks if the traversor references the same element as `tr`/`it`.

**<u>Note</u>:** Both variants of *`point_kd_tree_traversor`* (*`traversor`*, *`const_traversor`*) and of *`point_kd_tree_range_iterator`* (*`iterator`*, *`const_iterator`*) are accepted.

---

<a name="go_up" href="#go_up">#</a> <code><i>traversor</i> &</code> **go_up** () [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="go_lesser" href="#go_lesser">#</a> <code><i>traversor</i> &</code> **go_lesser** () [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="go_greater" href="#go_greater">#</a> <code><i>traversor</i> &</code> **go_greater** () [<>](../../../src/point_kd_tree/traversal.hpp#L)

Moves the traversor within the point k-d tree structure.
Returns `*this`.

<a name="up" href="#up">#</a> *`traversor`* **up** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="lesser" href="#lesser">#</a> *`traversor`* **lesser** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="greater" href="#greater">#</a> *`traversor`* **greater** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Returns a traversor referencing another element in the point k-d tree structure.

---

<a name="go_prev" href="#go_prev">#</a> <code><i>traversor</i> &</code> **go_prev** () [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="go_next" href="#go_next">#</a> <code><i>traversor</i> &</code> **go_next** () [<>](../../../src/point_kd_tree/traversal.hpp#L)

Moves the traversor within the point k-d tree structure, following the ***in-order*** traversal formalization. Returns `*this`.

**<u>Note:</u>** Functions <code><i>traversor</i>.<a href="#go_prev">go_prev()</a></code> and <code><i>traversor</i>.<a href="#go_next">go_next()</a></code> are equivalent to <code>--<i>traversor</i></code> and <code>++<i>traversor</i></code>, respectively.

<a name="prev" href="#prev">#</a> *`traversor`* **prev** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="next" href="#next">#</a> *`traversor`* **next** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Returns a traversor referencing the previous or next element in the point k-d tree structure, following the ***in-order*** traversal formalization.

**<u>Note:</u>** Functions <code><i>traversor</i>.<a href="#prev">prev()</a></code> and <code><i>traversor</i>.<a href="#next">next()</a></code> are equivalent to <code><a href="http://en.cppreference.com/w/cpp/iterator/prev">std::prev</a>(<i>traversor</i>)</code> and <code><a href="http://en.cppreference.com/w/cpp/iterator/next">std::next</a>(<i>traversor</i>)</code>, respectively.

---

<a name="range-" href="#range-">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>traversor</i>, <i>traversor</i>></code> **range** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Returns a range containing all the elements within the subtree headed by the traversor's element.
