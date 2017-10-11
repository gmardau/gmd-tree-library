# gmd: Binary tree traversal

## Traversor

The binary tree traversor is a structure that allows the iteration and traversal of a binary tree structure. It satisfies the requirements of [BidirectionalIterator](http://en.cppreference.com/w/cpp/concept/BidirectionalIterator).

---

| Member type | Definition |
|:-|:-|
| *`value_type`* | <code>(const) <i>binary_tree</i>::<i>value_type</i></code> |
| *`reference`* | <code><i>value_type</i> &</code> |
| *`pointer`* | <code><i>value_type</i> *</code> |
| *`iterator_category`* | [`std::bidirectional_iterator_tag`](http://en.cppreference.com/w/cpp/iterator/iterator_tags) |
| *`difference_type`* | [`std::ptrdiff_t`](http://en.cppreference.com/w/cpp/types/ptrdiff_t) |

---

Traversors can be implicitly converted to their reverse and/or const counterparts using constructors. However const traversors cannot be converted to non-const traversors.

**<u>Note</u>:** For the remainder of the document, please consider *`traversor`* as the type of the current object and *`reverse_traversor`* its reverse counterpart.

---

<a name="reverse" href="#reverse">#</a> *`reverse_traversor`* **reverse** () `const` [<>](../../../src/binary_tree/traversal.hpp#L)

Returns a reversed traversor to the same element in the container.

<a name="call" href="#call">#</a> `bool` **operator()** () `const` [<>](../../../src/binary_tree/traversal.hpp#L)

Checks if the traversor is valid, returning `true` if it is; `false` otherwise.

---

<a name="equal" href="#equal">#</a> `bool` **operator==** (<code>const <i>binary_tree_traversor</i> &<b>tr</b></code>) `const` [<>](../../../src/binary_tree/traversal.hpp#L)<br>
<a name="not_equal" href="#not_equal">#</a> `bool` **operator!=** (<code>const <i>binary_tree_traversor</i> &<b>tr</b></code>) `const` [<>](../../../src/binary_tree/traversal.hpp#L)

Checks if the traversor references the same element as `tr`.

**<u>Note</u>:** All four variants of *`binary_tree_traversor`* (*`traversor`*, *`reverse_traversor`*, *`const_traversor`*, *`const_reverse_traversor`*) are accepted.

---

<a name="go_up" href="#go_up">#</a> <code><i>traversor</i> &</code> **go_up** () [<>](../../../src/binary_tree/traversal.hpp#L)<br>
<a name="go_left" href="#go_left">#</a> <code><i>traversor</i> &</code> **go_left** () [<>](../../../src/binary_tree/traversal.hpp#L)<br>
<a name="go_right" href="#go_right">#</a> <code><i>traversor</i> &</code> **go_right** () [<>](../../../src/binary_tree/traversal.hpp#L)

Moves the traversor within the binary tree structure.
Returns `*this`.

<a name="up" href="#up">#</a> *`traversor`* **up** () `const` [<>](../../../src/binary_tree/traversal.hpp#L)<br>
<a name="left" href="#left">#</a> *`traversor`* **left** () `const` [<>](../../../src/binary_tree/traversal.hpp#L)<br>
<a name="right" href="#right">#</a> *`traversor`* **right** () `const` [<>](../../../src/binary_tree/traversal.hpp#L)

Returns a traversor referencing another element in the binary tree structure.

---

<a name="go_prev" href="#go_prev">#</a> <code><i>traversor</i> &</code> **go_prev** () [<>](../../../src/binary_tree/traversal.hpp#L)<br>
<a name="go_next" href="#go_next">#</a> <code><i>traversor</i> &</code> **go_next** () [<>](../../../src/binary_tree/traversal.hpp#L)

Moves the traversor within the binary tree structure, following the ***in-order*** traversal formalization. Returns `*this`.

**<u>Note:</u>** Functions <code><i>traversor</i>.<a href="#go_prev">go_prev()</a></code> and <code><i>traversor</i>.<a href="#go_next">go_next()</a></code> are equivalent to <code>--<i>traversor</i></code> and <code>++<i>traversor</i></code>, respectively.

<a name="prev" href="#prev">#</a> *`traversor`* **prev** () `const` [<>](../../../src/binary_tree/traversal.hpp#L)<br>
<a name="next" href="#next">#</a> *`traversor`* **next** () `const` [<>](../../../src/binary_tree/traversal.hpp#L)

Returns a traversor referencing the previous or next element in the binary tree structure, following the ***in-order*** traversal formalization.

**<u>Note:</u>** Functions <code><i>traversor</i>.<a href="#prev">prev()</a></code> and <code><i>traversor</i>.<a href="#next">next()</a></code> are equivalent to <code><a href="http://en.cppreference.com/w/cpp/iterator/prev">std::prev</a>(<i>traversor</i>)</code> and <code><a href="http://en.cppreference.com/w/cpp/iterator/next">std::next</a>(<i>traversor</i>)</code>, respectively.
