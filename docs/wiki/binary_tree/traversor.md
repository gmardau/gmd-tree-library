# gmd: Binary tree traversor

A binary tree traversor is a structure that allows the iteration and traversal of a binary tree structure (*`binary_tree`*). It satisfies the requirements of [BidirectionalIterator](http://en.cppreference.com/w/cpp/concept/BidirectionalIterator). Additionally, the following member functions are provided:

<a name="reverse" href="#reverse">#</a> *`reverse_traversor`* **reverse** () [<>](../../../src/binary_tree/traversor.hpp#L)

Returns a reversed traversor to the same element in the container. Note that if the object is of type *`reverse_traversor`* the returned traversor is of the type *`traversor`*.

<a name="call" href="#call">#</a> `bool` **operator()** () [<>](../../../src/binary_tree/traversor.hpp#L)

Checks if the traversor is valid, returning `true` if it is; `false` otherwise.

<sub>template <<code>typename T</code>></sub><br>
<a name="same" href="#same">#</a> `bool` **same** (<code>const T &<b>tr</b></code>) [<>](../../../src/binary_tree/traversor.hpp#L)

Checks if the traversor references the same element as `tr`. Returns `true` if it does; `false` otherwise.

<a name="goup" href="#go_p">#</a> <code><i>traversor</i> &</code> **go_up** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="goleft" href="#goleft">#</a> <code><i>traversor</i> &</code> **go_left** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="goright" href="#goright">#</a> <code><i>traversor</i> &</code> **go_right** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="goprev" href="#goprev">#</a> <code><i>traversor</i> &</code> **go_prev** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="gonext" href="#gonext">#</a> <code><i>traversor</i> &</code> **go_next** () [<>](../../../src/binary_tree/traversor.hpp#L)

Moves the traversor within the binary tree structure.
Returns `*this`.

**<u>Note:</u>** <code><i>traversor</i>.<a href="#goprev">go_prev()</a></code> and <code><i>traversor</i>.<a href="gonext">go_next()</a></code> are equivalent to <code>--<i>traversor</i></code> and <code>++<i>traversor</i></code>, respectively.

<a name="up" href="#up">#</a> *`traversor`* **up** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="left" href="#left">#</a> *`traversor`* **left** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="right" href="#right">#</a> *`traversor`* **right** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="prev" href="#prev">#</a> *`traversor`* **prev** () [<>](../../../src/binary_tree/traversor.hpp#L)<br>
<a name="next" href="#next">#</a> *`traversor`* **next** () [<>](../../../src/binary_tree/traversor.hpp#L)

Returns a traversor referencing another element in the binary tree structure.

**<u>Note:</u>** <code><i>traversor</i>.<a href="prev">prev()</a></code> and <code><i>traversor</i>.<a href="next">next()</a></code> are equivalent to <code><a href="http://en.cppreference.com/w/cpp/iterator/prev">std::prev</a>(<i>traversor</i>)</code> and <code><a href="http://en.cppreference.com/w/cpp/iterator/next">std::next</a>(<i>traversor</i>)</code>, respectively.
