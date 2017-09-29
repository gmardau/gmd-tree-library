# gmd: Binary tree traversal

## Traversor

The binary tree traversor is a structure that allows the iteration and traversal of a binary tree structure (*`binary_tree`*). It satisfies the requirements of [BidirectionalIterator](http://en.cppreference.com/w/cpp/concept/BidirectionalIterator).

---

| Member type | Definition |
|:-|:-|
| *`value_type`* | <code>(const) <i>binary_tree</i>::<i>value_type</i></code> |
| *`reference`*  | <code><i>value_type</i> &</code> |
| *`pointer`*    | <code><i>value_type</i> *</code> |
| *`iterator_category`* | [`std::bidirectional_iterator_tag`](http://en.cppreference.com/w/cpp/iterator/iterator_tags) |
| *`difference_type`* | [`std::ptrdiff_t`](http://en.cppreference.com/w/cpp/types/ptrdiff_t) |

---

Traversors can be implicitly converted to their reverse and/or const counterparts using constructors. However const traversors cannot be converted to non-const traversors.

**<u>Note</u>:** For the remainder of the document, please consider *`traversor`* as the type of the current object and *`reverse_traversor`* its reverse counterpart.

---

<a name="reverse" href="#reverse">#</a> *`reverse_traversor`* **reverse** () `const` [<>](../../../src/binary_tree/traversor.hpp#L)

Returns a reversed traversor to the same element in the container.

<a name="call" href="#call">#</a> `bool` **operator()** () `const` [<>](../../../src/binary_tree/traversor.hpp#L)

Checks if the traversor is valid, returning `true` if it is; `false` otherwise.

---

### Comparison operators

<a name="same" href="#same">#</a> `bool` **same** (<code>const <i>binary_tree_traversor</i> &<b>tr</b></code>) `const` [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="equal" href="#equal">#</a> `bool` **operator==** (<code>const <i>binary_tree_traversor</i> &<b>tr</b></code>) `const` [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="notequal" href="#notequal">#</a> `bool` **operator!=** (<code>const <i>binary_tree_traversor</i> &<b>tr</b></code>) `const` [<>](../../../src/binary_tree/traversor.hpp#L)

Checks if the traversor references the same element as `tr`. Returns `true` if it does; `false` otherwise.

**<u>Note</u>:** All four variants of *`binary_tree_traversor`* (*`traversor`*, *`reverse_traversor`*, *`const_traversor`*, *`const_reverse_traversor`*) are accepted. Functions
[`same()`](#same) and [`operator==()`](#equal) are equivalent.

---

### Element

<a name="dereference1" href="#dereference1">#</a> *`reference`* **operator*** () `const` [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="dereference2" href="#dereference2">#</a> *`pointer`* **operator->** () `const` [<>](../../../src/binary_tree/traversor.hpp#L)

Returns the element referenced by the traversor.

**<u>Note</u>:** Invalid traversors must not be dereferenced. Otherwise, it can lead to [*undefined behaviour*](http://en.cppreference.com/w/cpp/language/ub#Null_pointer_dereference). The same applies to (valid) ***past-the-end*** traversors.

---

### Traversal

<a name="goup" href="#go_p">#</a> <code><i>traversor</i> &</code> **go_up** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="goleft" href="#goleft">#</a> <code><i>traversor</i> &</code> **go_left** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="goright" href="#goright">#</a> <code><i>traversor</i> &</code> **go_right** () [<>](../../../src/binary_tree/traversor.hpp#L)

Moves the traversor within the binary tree structure.
Returns `*this`.

<a name="up" href="#up">#</a> *`traversor`* **up** () `const` [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="left" href="#left">#</a> *`traversor`* **left** () `const` [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="right" href="#right">#</a> *`traversor`* **right** () `const` [<>](../../../src/binary_tree/traversor.hpp#L)

Returns a traversor referencing another element in the binary tree structure.

---

### Iteration


<a name="decrement1" href="#decrement1">#</a> <code><i>traversor</i> &</code> **operator--** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="increment1" href="#increment1">#</a> <code><i>traversor</i> &</code> **operator++** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="goprev" href="#goprev">#</a> <code><i>traversor</i> &</code> **go_prev** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="gonext" href="#gonext">#</a> <code><i>traversor</i> &</code> **go_next** () [<>](../../../src/binary_tree/traversor.hpp#L)

*Pre-increment*&emsp;Moves the traversor within the binary tree structure, following the ***in-order*** traversal formalization. Returns `*this`.

**<u>Note:</u>** Functions [`go_prev()`](#goprev) and [`go_next()`](#gonext) are equivalent to [`operator--()`](#decrement1) and [`operator++()`](#increment1), respectively.

<a name="decrement1" href="#decrement1">#</a> <code><i>traversor</i></code> **operator--** (int) [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="increment1" href="#increment1">#</a> <code><i>traversor</i></code> **operator++** (int) [<>](../../../src/binary_tree/traversor.hpp#L)

*Post-increment*&emsp;Returns a copy of the traversor, moving it afterwards within the binary tree structure, following the ***in-order*** traversal formalization.

<a name="prev" href="#prev">#</a> *`traversor`* **prev** () `const` [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="next" href="#next">#</a> *`traversor`* **next** () `const` [<>](../../../src/binary_tree/traversor.hpp#L)

Returns a traversor referencing the previous or next element in the binary tree structure, following the ***in-order*** traversal formalization.

**<u>Note:</u>** Functions [`prev()`](#prev) and [`next()`](#next) are equivalent to [`std::prev()`](http://en.cppreference.com/w/cpp/iterator/prev) and [`std::next()`](http://en.cppreference.com/w/cpp/iterator/next), respectively.
