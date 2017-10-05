# gmd: Point k-d tree range

## Range

The point k-d tree range is a collection of references to elements on a point k-d tree container. In essence, it functions as an [`std::vector`](http://en.cppreference.com/w/cpp/container/vector) wrapper class.

---

| Member type | Definition |
|:-|:-|
| *`value_type`* | <code>(const) <i>point_kd_tree</i>::<i>value_type</i></code> |
| *`difference_type`* | [`std::ptrdiff_t`](http://en.cppreference.com/w/cpp/types/ptrdiff_t) |
| *`iterator`* | [Point k-d tree range iterator](#range-iterator) |
| *`const_iterator`*  | Constant [Point k-d tree range iterator](#range-iterator) |

---

### Iterators

<a name="begin-0" href="#begin-0">#</a> *`iterator`* **begin** () [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="begin-1" href="#begin-1">#</a> *`const_iterator`* **begin** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="cbegin" href="#cbegin">#</a> *`const_iterator`* **cbegin** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Returns an iterator to the first element of the container.
If the container is empty, the returned iterator will be equivalent to [`end()`](#end-0).

<a name="end-0" href="#end-0">#</a> *`iterator`* **end** () [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="end-1" href="#end-1">#</a> *`const_iterator`* **end** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="cend" href="#cend">#</a> *`const_iterator`* **cend** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Returns an iterator to the element following the last element of the container (***past-the-end***). As such, it cannot be dereferenced.

**<u>Note</u>:** The first [`begin()`](#begin-0) and [`end()`](#end-0) functions are ***valid*** only if the range is not constant.

---

### Capacity

<a name="empty" href="#empty">#</a> `bool` **empty** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Returns `true` if the container is empty; `false` otherwise.

<a name="size" href="#size">#</a> *`size_type`* **size** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Returns the number of elements in the container.

---

## Range Iterator

The point k-d tree range iterator is a structure that allows the iteration of a point k-d tree range. It satisfies the requirements of [RandomAccessIterator](http://en.cppreference.com/w/cpp/concept/RandomAccessIterator). In essence, it functions as a random-access iterator wrapper class for an [`std::vector`](http://en.cppreference.com/w/cpp/container/vector).

---

| Member type | Definition |
|:-|:-|
| *`value_type`* | <code>(const) <i>point_kd_tree</i>::<i>value_type</i></code> |
| *`reference`* | <code><i>value_type</i> &</code> |
| *`pointer`* | <code><i>value_type</i> *</code> |
| *`iterator_category`* | [`std::random_access_iterator_tag`](http://en.cppreference.com/w/cpp/iterator/iterator_tags) |
| *`difference_type`* | [`std::ptrdiff_t`](http://en.cppreference.com/w/cpp/types/ptrdiff_t) |

---

Range iterators can be implicitly converted to their const counterparts using constructors. However const traversors cannot be converted to non-const traversors. They can also be converted to Point k-d tree traversors through constructors.

---

<a name="traversor" href="#traversor">#</a> *`point_kd_tree_traversor`* **traversor** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Returns a point k-d tree traversor to the same element.

<a name="call" href="#call">#</a> `bool` **operator()** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Checks if the iterator is valid, returning `true` if it is; `false` otherwise.

---

<a name="equal-1" href="#equal-1">#</a> `bool` **operator==** (<code>const <i>point_kd_tree_traversor</i> &<b>tr</b></code>) `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="equal-0" href="#equal-0">#</a> `bool` **operator==** (<code>const <i>point_kd_tree_range_iterator</i> &<b>it</b></code>) `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="not_equal" href="#not_equal">#</a> `bool` **operator!=** (<code>const <i>point_kd_tree_range_iterator</i> &<b>it</b></code>) `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Checks if the iterator references the same element as `tr`/`it`.

**<u>Note</u>:** Both variants of *`point_kd_tree_traversor`* (*`traversor`*, *`const_traversor`*) and of *`point_kd_tree_range_iterator`* (*`iterator`*, *`const_iterator`*) are accepted.

---

<a name="go_prev" href="#go_prev">#</a> <code><i>iterator</i> &</code> **go_prev** () [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="go_next" href="#go_next">#</a> <code><i>iterator</i> &</code> **go_next** () [<>](../../../src/point_kd_tree/traversal.hpp#L)

Moves the iterator within the point k-d tree range.

**<u>Note:</u>** Functions <code><i>iterator</i>.<a href="#go_prev">go_prev()</a></code> and <code><i>iterator</i>.<a href="#go_next">go_next()</a></code> are equivalent to <code>--<i>iterator</i></code> and <code>++<i>iterator</i></code>, respectively.

<a name="prev" href="#prev">#</a> *`iterator`* **prev** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)<br>
<a name="next" href="#next">#</a> *`iterator`* **next** () `const` [<>](../../../src/point_kd_tree/traversal.hpp#L)

Returns an iterator referencing the previous or next element in the point k-d tree range.

**<u>Note:</u>** Functions <code><i>iterator</i>.<a href="#prev">prev()</a></code> and <code><i>iterator</i>.<a href="#next">next()</a></code> are equivalent to <code><a href="http://en.cppreference.com/w/cpp/iterator/prev">std::prev</a>(<i>iterator</i>)</code> and <code><a href="http://en.cppreference.com/w/cpp/iterator/next">std::next</a>(<i>iterator</i>)</code>, respectively.
