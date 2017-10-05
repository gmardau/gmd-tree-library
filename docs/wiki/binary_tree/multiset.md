# gmd::binary_tree_multiset

```cpp
template <
	binary_tree_type Tree,
	typename Key,
	bool Threaded = false,
	typename Comparator = std::less<Key>,
	typename Allocator = std::allocator<Key>
> struct binary_tree_multiset;
```

`gmd::binary_tree_multiset` is a container that stores a sorted collection of elements of type `Key` in a binary tree structure. The type of tree is defined by the template parameter `Tree`, while the sorting is done by using a key comparison function/object of type `Comparator`, which gets defaulted to [`std::less`](http://en.cppreference.com/w/cpp/utility/functional/less). The comparison mechanism follows the *strict weak ordering* formalization. As such, and because this container allows duplicates, the adopted definition is <code><i>left</i> < node <= <i>right</i></code>, meaning that in the case of duplicate elements, these appear by order of insertion when iterating through the container. The template parameter `Allocator` defines the type of allocator that will be used to allocate the elements in the container, and it is defaulted to [`std::allocator`](http://en.cppreference.com/w/cpp/memory/allocator).

The `Threaded` parameter specifies whether the binary tree elements should have pointers to their in-order predecessors and successors. This allows for a faster iteration through the elements of the container (guaranteed *O*(1) time complexity), but it comes at the expense of additional memory and a slight time overhead whenever element insertion or removal is performed. This parameter gets defaulted to `false`, as in the STL/C++ Standard Library's [`std::multiset`](http://en.cppreference.com/w/cpp/container/multiset) implementation.

---

| Member type | Definition |
|:-|:-|
| *`key_type`* | `Key` |
| *`value_type`* | `Key` |
| *`size_type`* | [`std::size_t`](http://en.cppreference.com/w/cpp/types/size_t) |
| *`difference_type`* | [`std::ptrdiff_t`](http://en.cppreference.com/w/cpp/types/ptrdiff_t) |
| *`key_compare`* | `Comparator` |
| *`value_compare`* | `Comparator` |
| *`allocator_type`* | `Allocator` |
| *`reference`* | <code><i>value_type</i> &</code> |
| *`const_reference`* | <code>const <i>value_type</i> &</code> |
| *`pointer`* | <code><i>value_type</i> *</code> |
| *`const_pointer`* | <code>const <i>value_type</i> *</code> |
| *`iterator`*<br>*`traversor`*<br>*`reverse_iterator`*<br>*`reverse_traversor`* | [Binary tree traversor](traversal.md) |
| *`const_iterator`*<br>*`const_traversor`*<br>*`const_reverse_iterator`*<br>*`const_reverse_traversor`* | Constant [Binary tree traversor](traversal.md) |

---

### Constructor

<a name="constructor-0" href="#constructor-0">#</a> **binary_tree_multiset** ([<code>const <i>key_compare</i> &<b>c</b>, const <i>allocator_type</i> &<b>a</b></code>]) [<>](../../../src/binary_tree/base.hpp#L)

*Default constructor*&emsp;Constructs an empty container.

<sub>template <<code>typename T1, typename T2</code>></sub><br>
<a name="constructor-1" href="#constructor-1">#</a> **binary_tree_multiset** (<code>const T1 &<b>first</b>, const T2 &<b>last</b></code> [<code>, const <i>key_compare</i> &<b>c</b>, const <i>allocator_type</i> &<b>a</b></code>]) [<>](../../../src/binary_tree/base.hpp#L)

*Range constructor*&emsp;Constructs the container with the contents of the range [`first`, `last`). It is equivalent to call the *default constructor* followed by [`insert(first, last)`](#insert-2).

<a name="constructor-2" href="#constructor-2">#</a> **binary_tree_multiset** (<code>const <i>binary_tree_multiset</i> &<b>other</b></code> [<code>, const <i>key_compare</i> &<b>c</b>, const <i>allocator_type</i> &<b>a</b></code>]) [<>](../../../src/binary_tree/base.hpp#L)

*Copy constructor*&emsp;Constructs the container with the copy of the contents of `other`. If a comparator or an allocator are not provided, they are obtained by copy from the ones in `other`. In the case of the allocator, the following is used: <code><a href="http://en.cppreference.com/w/cpp/memory/allocator_traits">std::allocator_traits</a><<i>allocator_type</i>>::select_on_container_copy_construction()</code>.

<a name="constructor-3" href="#constructor-3">#</a> **binary_tree_multiset** (<code><i>binary_tree_multiset</i> &&<b>other</b></code> [<code>, const <i>key_compare</i> &<b>c</b>, const <i>allocator_type</i> &<b>a</b></code>]) [<>](../../../src/binary_tree/base.hpp#L)

*Move constructor*&emsp;Constructs the container with the contents of `other`, using move semantics. If a comparator or an allocator are not provided, they are obtained by move-construction from the ones in `other`.

<a name="constructor-4" href="#constructor-4">#</a> **binary_tree_multiset** (<code>const <a href="http://en.cppreference.com/w/cpp/utility/initializer_list">std::initializer_list</a><<i>value_type</i>> &<b>il</b></code> [<code>, const <i>key_compare</i> &<b>c</b>, const <i>allocator_type</i> &<b>a</b></code>]) [<>](../../../src/binary_tree/base.hpp#L)

*Initializer list constructor*&emsp;Constructs the container with the contents of the initializer list `il`. It is equivalent to call the *default constructor* followed by [`insert(il)`](#insert-3).

#### Example
```cpp
int main (const int, const char **)
{
	// (1) Default constructor
	gmd::binary_tree_multiset<gmd::tree_avl, int> a;
	a.insert({1, 3, 5, 3});
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	// (2) Range constructor
	gmd::binary_tree_multiset<gmd::tree_avl, int> b(++a.begin(), a.end());
	std::cout << "b: "; for(int &x: b) std::cout << x << ' '; std::cout << '\n';

	// (3) Copy constructor
	gmd::binary_tree_multiset<gmd::tree_avl, int> c(a);
	c.insert(2);
	std::cout << "c: "; for(int &x: c) std::cout << x << ' '; std::cout << '\n';

	// (4) Move constructor
	gmd::binary_tree_multiset<gmd::tree_avl, int> d(std::move(b));
	std::cout << "b: "; for(int &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(int &x: d) std::cout << x << ' '; std::cout << '\n';

	// (5) Initializer list constructor
	gmd::binary_tree_multiset<gmd::tree_avl, int> e{4, 4, 6, 5};
	std::cout << "e: "; for(int &x: e) std::cout << x << ' '; std::cout << '\n';
}
```
##### Output
```
a: 1 3 3 5
b: 3 3 5
c: 1 2 3 3 5
b:
d: 3 3 5
e: 4 4 5 6
```

---

### Destructor

<a name="destructor-" href="#destructor-">#</a> **~binary_tree_multiset** () [<>](../../../src/binary_tree/base.hpp#L)

Destructs and deallocates the container and all its elements.

---

### Assign operator

<a name="assign-0" href="#assign-0">#</a> <code><i>binary_tree_multiset</i> &</code>**operator=** (<code>const <i>binary_tree</i> &<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

*Copy assignment*&emsp;Replaces the contents of the containers with a copy of the contents of `other`. The allocator is replaced only if <code><a href="http://en.cppreference.com/w/cpp/memory/allocator_traits">std::allocator_traits</a><<i>allocator_type</i>>::propagate_on_container_copy_assignment::value</code> is set to `true`.

<a name="assign-1" href="#assign-1">#</a> <code><i>binary_tree_multiset</i> &</code>**operator=** (<code><i>binary_tree</i> &&<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

*Move assignment*&emsp;Replaces the contents with those of `other` using move semantics. The allocator is replaced only if <code><a href="http://en.cppreference.com/w/cpp/memory/allocator_traits">std::allocator_traits</a><<i>allocator_type</i>>::propagate_on_container_move_assignment::value</code> is set to `true`. If not, and neither <code><a href="http://en.cppreference.com/w/cpp/memory/allocator_traits">std::allocator_traits</a><<i>allocator_type</i>>::is_always_equal::value</code> is set `true` nor the allocators compare equal, then the elements are copied instead.

<a name="assign-2" href="#assign-2">#</a> <code><i>binary_tree_multiset</i> &</code>**operator=** (<code><a href="http://en.cppreference.com/w/cpp/utility/initializer_list">std::initializer_list</a><<i>value_type</i>> &<b>il</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

*Initializer list assignment*&emsp;Replaces the contents with those of the initializer list `il`.

**<u>Note</u>:** All four variants of *`binary_tree`* (*`set`*, *`map`*, *`multiset`*, *`multimap`*) are accepted, as well as any template signature, as long as *`value_type`* is the same. When copying the elements, if the tree types of `*this` and `other` are conversion compatible, then the structure of `other` is replicated; otherwise, the elements are copied one by one. For more information, refer to [tree type conversion](../tree.md#type-conversion).

#### Example
```cpp
int main (const int, const char **)
{
	// (1) Copy assignment
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{3, 5, 2, 5};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
	gmd::binary_tree_multiset<gmd::tree_avl, int> b; b = a;
	std::cout << "b: "; for(int &x: b) std::cout << x << ' '; std::cout << '\n';

	// (2) Move assignment
	gmd::binary_tree_set<gmd::tree_avl, int> c{1, 6};
	std::cout << "c: "; for(int &x: c) std::cout << x << ' '; std::cout << '\n';
	gmd::binary_tree_multiset<gmd::tree_rb, int> d; d = std::move(c);
	std::cout << "c: "; for(int &x: c) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(int &x: d) std::cout << x << ' '; std::cout << '\n';

	// (3) Initializer list assignment
	a = {7, 4, 7};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
}
```
##### Output
```
a: 2 3 5 5
b: 2 3 5 5
c: 1 6
c:
d: 1 6
a: 4 7 7
```

---

### Comparison operators

<a name="equal-0" href="#equal-0">#</a> `bool` **operator==** (<code><i>binary_tree</i> &<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="equal-1" href="#equal-1">#</a> `bool` **operator==** (<code>const <i>binary_tree</i> &<b>other</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="not_equal-0" href="#not_equal-0">#</a> `bool` **operator!=** (<code><i>binary_tree</i> &<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="not_equal-1" href="#not_equal-1">#</a> `bool` **operator!=** (<code>const <i>binary_tree</i> &<b>other</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="lesser-0" href="#lesser-0">#</a> `bool` **operator<** (<code><i>binary_tree</i> &<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="lesser-1" href="#lesser-1">#</a> `bool` **operator<** (<code>const <i>binary_tree</i> &<b>other</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="greater-0" href="#greater-0">#</a> `bool` **operator>** (<code><i>binary_tree</i> &<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="greater-1" href="#greater-1">#</a> `bool` **operator>** (<code>const <i>binary_tree</i> &<b>other</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="lesser_or_equal-0" href="#lesser_or_equal-0">#</a> `bool` **operator<=** (<code><i>binary_tree</i> &<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="lesser_or_equal-1" href="#lesser_or_equal-1">#</a> `bool` **operator<=** (<code>const <i>binary_tree</i> &<b>other</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="greater_or_equal-0" href="#greater_or_equal-0">#</a> `bool` **operator>=** (<code><i>binary_tree</i> &<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="greater_or_equal-1" href="#greater_or_equal-1">#</a> `bool` **operator>=** (<code>const <i>binary_tree</i> &<b>other</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="spaceship-0" href="#spaceship-0">#</a> `int` **spaceship** (<code><i>binary_tree</i> &<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="spaceship-1" href="#spaceship-1">#</a> `int` **spaceship** (<code>const <i>binary_tree</i> &<b>other</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)

Compares the contents of `*this` and `other` lexicographically.
The `spaceship` function returns `-1` if the contents of the `*this` are lexicographically ***lesser*** than the contents of `other`; `0` if ***equal***; `1` if ***greater***.

**<u>Note</u>:** All four variants of *`binary_tree`* (*`set`*, *`map`*, *`multiset`*, *`multimap`*) are accepted, as well as any template signature, as long as either *`key_type`* is the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
int main (const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 5};
	gmd::binary_tree_multiset<gmd::tree_rb, int> b{1, 3, 3, 4, 5};
	gmd::binary_tree_multiset<gmd::tree_avl, int> c{2, 3, 4, 2};

	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(int &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(int &x: c) std::cout << x << ' '; std::cout << '\n';
	std::cout << "a == b: " << (a == b ? "true" : "false") << '\n';
	std::cout << "b != c: " << (b != c ? "true" : "false") << '\n';
	std::cout << "a < b: " << (a < b ? "true" : "false") << '\n';
	std::cout << "b > c: " << (b > c ? "true" : "false") << '\n';
	std::cout << "a <=> c: " << a.spaceship(c) << '\n';
}
```
##### Output
```
a: 1 3 4 5
b: 1 3 3 4 5
c: 2 2 3 4
a == b: false
b != c: true
a < b: false
b > c: false
a <=> c: -1
```

---

## Observers

<a name="key_comp" href="#key_comp">#</a> *`key_compare`* **key_comp** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a copy of the function object used to compare the keys.

<a name="value_comp" href="#value_comp">#</a> *`value_compare`* **value_comp** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a copy of the function object that compares the values.

<a name="get_comparator" href="#get_comparator">#</a> <code><i>key_compare</i> &</code> **get_comparator** () [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="get_comparator" href="#get_comparator">#</a> <code>const <i>key_compare</i> &</code> **get_comparator** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns the comparator associated with the container.

<a name="get_allocator" href="#value_comp">#</a> *`allocator_type`* **get_allocator** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a copy of the allocator associated with the container.

#### Example
```cpp
struct Info {
	int v[2];
	Info(int w) : v{w, w+1} {}
	bool operator< (const Info &i) const {
		return v[0] < i.v[0];
	}
};

int main(const int, const char **)
{
	using btmset_a = gmd::binary_tree_multiset<gmd::tree_avl, int>;
	using btmset_b = gmd::binary_tree_multiset<gmd::tree_avl, int, false, std::greater<int>>;
	using btmset_c = gmd::binary_tree_multiset<gmd::tree_avl, Info>;
	btmset_a a;
	btmset_b b;
	btmset_c c;

	btmset_a::key_compare x = a.key_comp();
	btmset_b::value_compare y = b.value_comp();
	std::cout << "a (1 < 2): " << (x(1, 2) ? "true" : "false") << '\n';
	std::cout << "b (1 > 2): " << (y(1, 2) ? "true" : "false") << '\n';
	std::cout << "b (1 <= 2): " << (!y(1, 2) ? "true" : "false") << '\n';

	btmset_c::allocator_type z = c.get_allocator();
	Info *i = std::allocator_traits<btmset_c::allocator_type>::allocate(z, 2);
	new(&i[0]) Info(1);
	new(&i[1]) Info(3);
	std::cout << "i[0]: v = {" << i[0].v[0] << ", " << i[0].v[1] << "}\n";
	std::cout << "i[1]: v = {" << i[1].v[0] << ", " << i[1].v[1] << "}\n";
	i[0].~Info();
	i[1].~Info();
	std::allocator_traits<btmset_c::allocator_type>::deallocate(z, i, 2);
}
```
##### Output
```
a (1 < 2): true
b (1 > 2): false
b (1 <= 2): true
i[0]: v = {1, 2}
i[1]: v = {3, 4}
```

---

## Traversors

<a name="root-0" href="#root-0">#</a> *`traversor`* **root** () [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="root-1" href="#root-1">#</a> *`const_traversor`* **root** () `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="croot" href="#croot">#</a> *`const_traversor`* **croot** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a traversor to the root element of the container.
If the container is empty, the returned traversor will be empty (***invalid***) and cannot be dereferenced.

<a name="rroot-0" href="#rroot-0">#</a> *`reverse_traversor`* **rroot** () [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="rroot-1" href="#rroot-1">#</a> *`const_reverse_traversor`* **rroot** () `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="crroot" href="#crroot">#</a> *`const_reverse_traversor`* **crroot** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a reverse traversor to the root element of the container.
If the container is empty, the returned traversor will be empty (***invalid***) and cannot be dereferenced.

<a name="begin-0" href="#begin-0">#</a> *`traversor`* **begin** () [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="begin-1" href="#begin-1">#</a> *`const_traversor`* **begin** () `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="cbegin" href="#cbegin">#</a> *`const_traversor`* **cbegin** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a traversor to the first element of the container.
If the container is empty, the returned traversor will be equivalent to [`end()`](#end-0).

<a name="rbegin-0" href="#rbegin-0">#</a> *`reverse_traversor`* **rbegin** () [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="rbegin-1" href="#rbegin-1">#</a> *`const_reverse_traversor`* **rbegin** () `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="crbegin" href="#crbegin">#</a> *`const_reverse_traversor`* **crbegin** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a reverse traversor to the first element of the container.
If the container is empty, the returned traversor will be equivalent to [`rend()`](#rend-0).

<a name="end-0" href="#end-0">#</a> *`traversor`* **end** () [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="end-1" href="#end-1">#</a> *`const_traversor`* **end** () `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="cend" href="#cend">#</a> *`const_traversor`* **cend** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a traversor to the element following the last element of the container (***past-the-end***). As such, it cannot be dereferenced.

<a name="rend-0" href="#rend-0">#</a> *`reverse_traversor`* **rend** () [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="rend-1" href="#rend-1">#</a> *`const_reverse_traversor`* **rend** () `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="crend" href="#crend">#</a> *`const_reverse_traversor`* **crend** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a reverse traversor to the element following the last element of the container (***past-the-end***). As such, it cannot be dereferenced.

#### Example

```cpp
int main(const int, const char **)
{
	using btmset = gmd::binary_tree_multiset<gmd::tree_avl, int>;
	btmset a{1, 8, 4, 3, 7, 4};

	std::cout << "a: ";
	for(btmset::traversor x = a.begin(); x != a.end(); ++x)
		std::cout << *x << " ";
	std::cout << "\n";

	btmset::traversor x = a.root();
	std::cout << "root: " << *x << "\n";
	if(x.right()())
		std::cout << "right: " << *x.right() << "\n";

	std::cout << "reverse from root: ";
	for(btmset::const_reverse_traversor y = x.reverse(); y != a.crend(); ++y)
		std::cout << *y << " ";
	std::cout << "\n";
}
```
##### Output
```
a: 1 3 4 4 7 8
root: 4
right: 7
reverse from root: 4 3 1
```

---

## Capacity

<a name="empty" href="#empty">#</a> `bool` **empty** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns `true` if the container is empty; `false` otherwise.

<a name="size" href="#size">#</a> *`size_type`* **size** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns the number of elements in the container.

<a name="max_size" href="#max_size">#</a> *`size_type`* **max_size** () `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns the maximum number of elements the container is able to hold due to system or library implementation limitations. However, the size of the container may be limited to a smaller value at runtime.

#### Example
```cpp
int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a;

	std::cout << "empty: " << (a.empty() ? "true" : "false") << "\n";
	std::cout << "size: " << a.size() << "\n";
	a.insert({3, 1, 2, 3});
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "empty: " << (a.empty() ? "true" : "false") << "\n";
	std::cout << "size: " << a.size() << "\n";

	std::cout << "max_size: " << a.max_size() << "\n";
}
```
##### Output
```
empty: true
size: 0
a: 1 2 3 3
empty: false
size: 4
max_size: 576460752303423487
```

---

## Modifiers

### Clear

<a name="clear" href="#clear">#</a> `void` **clear** () [<>](../../../src/binary_tree/base.hpp#L)

Removes all elements from the container.

#### Example
```cpp
int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{4, 2, 3, 1, 2};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	a.clear();
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "size: " << a.size() << "\n";
}
```
##### Output
```
a: 1 2 2 3 4
a:
size: 0
```

---

### Insert

<a name="insert-0" href="#insert-0">#</a> *`traversor`* **insert** (<code>const <i>value_type</i> &<b>info</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<a name="insert-1" href="#insert-1">#</a> *`traversor`* **insert** (<code><i>value_type</i> &&<b>info</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Inserts `info` in the container.
Returns a traversor to the inserted element.

<sub>template <<code>typename T1, typename T2</code>></sub><br>
<a name="insert-2" href="#insert-2">#</a> `void` **insert** (<code>const T1 &<b>first</b>, const T2 &<b>last</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Inserts elements from range [`first`, `last`).
Even though `first` and `last` can be of different types, `last` must be reachable from `first` and `T1` needs to satisfy [EqualityComparable](http://en.cppreference.com/w/cpp/concept/EqualityComparable) towards `T2`.

<a name="insert-3" href="#insert-3">#</a> `void` **insert** (<code><a href="http://en.cppreference.com/w/cpp/utility/initializer_list">std::initializer_list</a><<i>value_type</i>> &<b>il</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Inserts elements from the initializer list `il`.

<sub>template <<code>typename T</code>></sub><br>
<a name="insert_hint-0" href="#insert_hint-0">#</a> *`traversor`* **insert_hint** (<code>const T &<b>hint</b>, const <i>value_type</i> &<b>info</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>typename T</code>></sub><br>
<a name="insert_hint-1" href="#insert_hint-1">#</a> *`traversor`* **insert_hint** (<code>const T &<b>hint</b>, <i>value_type</i> &&<b>info</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Inserts `info` in the container, taking `hint` as a possible location for the new element.
Returns a traversor to the inserted element. `hint` must be a non const traversor. This function can also be called as [`insert(hint, info)`](#insert_hint-0).

#### Example
```cpp
struct Info {
	Info (int a, int b) : v{a, b} {}
	int v[2];
	bool operator< (const Info &i) const { return v[0] < i.v[0]; }
};

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, Info> a;
	gmd::binary_tree_multiset<gmd::tree_rb, Info> b;

	auto y = a.insert(Info(2,0));
	std::cout << "element: " << (*y).v[0] << ',' << y->v[1] << "\n";
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	a.insert({Info(1,0), Info(2,1), Info(3,0), Info(4,0)});
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	a.insert(Info(2,1));
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	b.insert(a.root(), a.cend());
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	b.insert_hint(b.end(), Info(5,0));
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
}
```
##### Output
```
element: 2,0
a: 2,0
a: 1,0 2,0 2,1 3,0 4,0
a: 1,0 2,0 2,1 2,1 3,0 4,0
b: 2,1 2,1 3,0 4,0
b: 2,1 2,1 3,0 4,0 5,0
```

---

### Emplace

<sub>template <<code>typename... Args</code>></sub><br>
<a name="emplace-" href="#emplace-">#</a> *`traversor`* **emplace** (<code>Args&&... <b>info</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Inserts a new element in the container constructed *in-place* with `info`.
Returns a traversor to the inserted element.

<sub>template <<code>typename T, typename... Args</code>></sub><br>
<a name="emplace_hint" href="#emplace_hint">#</a> *`traversor`* **emplace_hint** (<code>const T &<b>hint</b>, Args&&... <b>info</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Inserts a new element in the container constructed *in-place* with `info`, taking `hint` as a possible location for the new element.
Returns a traversor to the inserted element. `hint` must be a non const traversor.

#### Example
```cpp
struct Info {
	Info (int a, int b) : v{a, b} {}
	int v[2];
	bool operator< (const Info &i) const { return v[0] < i.v[0]; }
};

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, Info> a;

	auto y = a.emplace(2, 0);
	std::cout << "element: " << (*y).v[0] << ',' << y->v[1] << "\n";
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	a.emplace(2, 1);
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	a.emplace_hint(a.begin(), 1, 0);
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
}
```
##### Output
```
element: 2,0
a: 2,0
a: 2,0 2,1
a: 1,0 2,0 2,1
```

---

### Erase

<a name="erase-0" href="#erase-0">#</a> *`size_type`* **erase** (<code>const <i>key_type</i> &<b>key</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Removes the elements that compare equivalent to `key`, if existent.
Returns the number of elements removed.

<sub>template <<code>typename T</code>></sub><br>
<a name="erase-1" href="#erase-1">#</a> `void` **erase** (<code>const T &<b>tr</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Removes the element referenced by `tr`, which must be a non const traversor.

<sub>template <<code>typename T1, typename T2</code>></sub><br>
<a name="erase-2" href="#erase-2">#</a> `void` **erase** (<code>const T1 &<b>first</b>, const T2 &<b>last</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Removes the elements in the range [`first`, `last`), which must be valid within the container. Both `first` and `last` must be non const traversors.

<a name="erase-3" href="#erase-3">#</a> *`size_type`* **erase** (<code>const <a href="http://en.cppreference.com/w/cpp/utility/initializer_list">std::initializer_list</a><<i>key_type</i>> &<b>il</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Removes the elements that compare equivalent to the keys in the initializer list `il`.
Returns the amount of elements removed.

#### Example
```cpp
int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 2, 3, 4, 5, 4};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	size_t y = a.erase(4);
	std::cout << "# erased: " << y << '\n';
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	a.erase(a.root().next(), a.end());
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	a.erase({1, 3});
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
}
```
##### Output
```
a: 1 2 3 4 4 5
# erased: 2
a: 1 2 3 5
a: 1 2 3
a: 2
```

---

### Transfer

<sub>template<<code>typename T</code>></sub><br>
<a name="transfer-" href="#transfer-">#</a> *`traversor`* **transfer** (<code><i>binary_tree</i> &<b>other</b>, const T &<b>tr</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Transfers an element from `other` into the container.
Returns a traversor to the transferred element.
`tr` must be a non const traversor in `other`.

**<u>Note</u>:** All four variants of *`binary_tree`* (*`set`*, *`map`*, *`multiset`*, *`multimap`*) are accepted, as well as any template signature, as long as *`value_type`* is the same.

#### Example
```cpp
struct Info {
	Info (int a, int b) : v{a, b} {}
	int v[2];
	bool operator< (const Info &i) const { return v[0] < i.v[0]; }
};

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, Info> a{Info(1,0), Info(2,0), Info(3,0)}, b{Info(2,1)};
	gmd::binary_tree_multiset<gmd::tree_rb, Info> c;
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	b.transfer(a, a.root());
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	c.transfer(a, a.begin());
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
	std::cout << "c: "; for(Info &x: c) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
}
```
###### Output
```
a: 1,0 2,0 3,0
b: 2,1
a: 1,0 3,0
b: 2,1 2,0
a: 3,0
c: 1,0
```

---

### Merge

<a name="merge-" href="#merge-">#</a> `void` **merge** (<code><i>binary_tree</i> &<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Merges the values of both containers into `*this`. This is achieved by attempting to transfer the elements of `other` one by one using `transfer`.

**<u>Note</u>:** All four variants of *`binary_tree`* (*`set`*, *`map`*, *`multiset`*, *`multimap`*) are accepted, as well as any template signature, as long as *`value_type`* is the same. If the container is empty and the tree types of `*this` and `other` are conversion compatible, then the structure of `other` is replicated; otherwise, the elements are copied one by one. For more information, refer to [tree type conversion](../tree.md#type-conversion).

#### Example
```cpp
struct Info {
	Info (int a, int b) : v{a, b} {}
	int v[2];
	bool operator< (const Info &i) const { return v[0] < i.v[0]; }
};

int main(const int, const char **)
{
	gmd::binary_tree_set<gmd::tree_avl, Info> a{Info(1,0), Info(2,0), Info(3,0)};
	gmd::binary_tree_multiset<gmd::tree_avl, Info> b{Info(2,1)};
	gmd::binary_tree_multiset<gmd::tree_rb, Info> c{Info(2,2)};
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
	std::cout << "c: "; for(Info &x: c) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	b.merge(a);
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	c.merge(b);
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
	std::cout << "c: "; for(Info &x: c) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
}
```
##### Output
```
a: 1,0 2,0 3,0
b: 2,1
c: 2,2
a:
b: 1,0 2,1 2,0 3,0
b:
c: 1,0 2,2 2,1 2,0 3,0
```

---

### Swap

<a name="swap-" href="#swap-">#</a> `void` **swap** (<code><i>binary_tree</i> &<b>other</b></code>) [<>](../../../src/binary_tree/base.hpp#L)

Exchanges the contents of the container with those of `other`.

**<u>Note</u>:** All four variants of *`binary_tree`* (*`set`*, *`map`*, *`multiset`*, *`multimap`*) are accepted, as well as any template signature, as long as *`value_type`* is the same. When copying the elements, if the tree types of `*this` and `other` are conversion compatible, then the structure of `other` is replicated, and vice-versa; otherwise, the elements are copied one by one. For more information, refer to [tree type conversion](../tree.md#type-conversion).

#### Example
```cpp
using intpair = std::pair<int, int>;

struct Comp {
	bool operator() (const intpair &a, const intpair &b) const {
		return a.first < b.first; }
};

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, intpair, false, Comp> a{{1, 0}, {3, 0}, {3, 1}, {4, 0}, {5, 0}};
	gmd::binary_tree_map<gmd::tree_rb, int, int, true, std::greater<int>> b{{2, 0}, {3, 0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';

	a.swap(b);
	std::cout << "a: "; for(intpair &x: a) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';
}
```
##### Output
```
a: 1,0 3,0 3,1 4,0 5,0
b: 3,0 2,0
a: 2,0 3,0
b: 5,0 4,0 3,0 1,0
```

---

## Lookup

### Count

<sub>template <<code>typename Key</code>></sub><br>
<a name="count-0" href="#count-0">#</a> *`size_type`* **count** (<code>const Key &<b>key</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="count-1" href="#count-1">#</a> *`size_type`* **count** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns the number of elements with a key that compares equivalent to `key`.

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 1};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "count 1: " << a.count(1) << "\n";
	std::cout << "count 2: " << a.count(2) << "\n";
}
```
##### Output
```
a: 1 1 3 4
count 1: 2
count 2: 0
```

---

### Contains

<sub>template <<code>typename Key</code>></sub><br>
<a name="contains-0" href="#contains-0">#</a> `bool` **contains** (<code>const Key &<b>key</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="contains-1" href="#contains-1">#</a> `bool` **contains** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)

Checks if there exists at least one element with a key that compares equivalent to `key`.
Returns `true` if such element exists; `false` otherwise.

It is equivalent to <code><a href="#find-0">find(key)</a> != <a href="#end-0">end()</a></code>.

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 3};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "contains 3: " << (a.contains(3) ? "true" : "false") << "\n";
	std::cout << "contains 2: " << (a.contains(2) ? "true" : "false") << "\n";
}
```
##### Output
```
a: 1 3 3 4
contains 3: true
contains 2: false
```

---

### Find

<sub>template <<code>typename Key</code>></sub><br>
<a name="find-0" href="#find-0">#</a> *`traversor`* **find** (<code>const Key &<b>key</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="find-1" href="#find-1">#</a> *`const_traversor`* **find** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)


<sub>template <<code>typename Key</code>></sub><br>
<a name="find_short-0" href="#find_short-0">#</a> *`traversor`* **find_short** (<code>const Key &<b>key</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="find_short-1" href="#find_short-1">#</a> *`const_traversor`* **find_short** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a traversor of the first element with a key equivalent to `key`. If no such element exists, a past-the-end traversor (e.g. [`end()`](#end-0)) is returned. The function [`find_short()`](#find_short-0) is more efficient than [`find()`](#find-0) when the element to be found is more likely to be close to the root, such as in a Splay-like tree.

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
struct Info {
	Info (int a, int b) : v{a, b} {}
	int v[2];
	bool operator< (const Info &i) const { return v[0] < i.v[0]; }
};

struct Comp {
	using is_transparent = void;
	bool operator() (const Info &i1, const Info &i2) const { return i1.v[0] < i2.v[0]; }
	bool operator() (const double &d, const Info &i) const { return d < i.v[0]; }
	bool operator() (const Info &i, const double &d) const { return i.v[0] < d; }
};

int main(const int, const char **)
{
	using btmset = gmd::binary_tree_multiset<gmd::tree_avl, Info, false, Comp>;
	btmset a{Info(1,0), Info(3,0), Info(4,0), Info(4,1)};
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	std::cout << "find 2.0: ";
	btmset::reverse_traversor y = a.find(2.0);
	if(y != a.rend()) std::cout << "true - " << (*y).v[0] << ',' << y->v[0] << "\n";
	else              std::cout << "false\n";

	std::cout << "find 4.0: ";
	btmset::const_traversor z = a.find_short(4.0);
	if(z != a.cend()) std::cout << "true - " << z->v[0] << ',' << z->v[1] << "\n";
	else              std::cout << "false\n";
}
```
##### Output
```
a: 1,0 3,0 4,0 4,1
find 2.0: false
find 4.0: true - 4,0
```

---

### Lower bound

<sub>template <<code>typename Key</code>></sub><br>
<a name="lower_bound-0" href="#lower_bound-0">#</a> *`traversor`* **lower_bound** (<code>const Key &<b>key</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="lower_bound-1" href="#lower_bound-1">#</a> *`const_traversor`* **lower_bound** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a traversor to the first element that is ***not lesser*** than `key`. If no such element exists, a past-the-end traversor (e.g. [`end()`](#end-0)) is returned.

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 3};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "lower_bound 2: ";
	auto y = a.lower_bound(2);
	if(y != a.end()) std::cout << *y;
	std::cout << "\n";

	a.insert(2);
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "lower_bound 2: ";
	y = a.lower_bound(2);
	if(y != a.end()) std::cout << *y;
	std::cout << "\n";
}
```
##### Output
```
a: 1 3 3 4
lower_bound 2: 3
a: 1 2 3 3 4
lower_bound 2: 2
```

---

### Upper bound

<sub>template <<code>typename Key</code>></sub><br>
<a name="upper_bound-0" href="#upper_bound-0">#</a> *`traversor`* **upper_bound** (<code>const Key &<b>key</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="upper_bound-1" href="#upper_bound-1">#</a> *`const_traversor`* **upper_bound** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a traversor to the first element that is ***greater*** than `key`. If no such element exists, a past-the-end traversor (e.g. [`end()`](#end-0)) is returned.

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 3};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "upper_bound 2: ";
	auto y = a.upper_bound(2);
	if(y != a.end()) std::cout << *y;
	std::cout << "\n";
}
```
##### Output
```
a: 1 3 3 4
upper_bound 2: 3
```

---

### Equal range

<sub>template <<code>typename Key</code>></sub><br>
<a name="equal_range-0" href="#equal_range-0">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>traversor</i>, <i>traversor</i>></code> **equal_range** (<code>const Key &<b>key</b></code>) [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="equal_range-1" href="#equal_range-1">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>const_traversor</i>, <i>const_traversor</i>></code> **equal_range** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)

Returns a range containing all the elements with a key equivalent to `key`.
Alternatively, the first traversor may be obtained with [`lower_bound(key)`](#lower_bound-0), and the second with [`upper_bound(key)`](#upper_bound-0).

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 3};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "equal_range 2: ";
	auto y = a.equal_range(2);
	if(y.first == y.second) std::cout << "no elements found\n";
	else                    std::cout << "element found\n";

	std::cout << "equal_range 3: ";
	y = a.equal_range(3);
	for(auto z = y.first; z != y.second; ++z)
		std::cout << *z << ' ';
	std::cout << "\n";
}
```
##### Output
```
a: 1 3 3 4
equal_range 2: no elements found
equal_range 3: 3 3
```

---

## Print

<sub>template <<code>bool Verbose = false, typename Printer</code>></sub><br>
<a name="print-0" href="#print-0">#</a> `void` **print** (<code>Printer &<b>printer</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>bool Verbose = false, typename Printer</code>></sub><br>
<a name="print-1" href="#print-1">#</a> `void` **print** ([<code>const Printer &<b>printer</b></code>]) `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>bool Verbose = false, typename Printer, typename T</code>></sub><br>
<a name="print-2" href="#print-2">#</a> `void` **print** (<code>const T &<b>tr</b>, Printer &<b>printer</b></code>) `const` [<>](../../../src/binary_tree/base.hpp#L)<br>
<sub>template <<code>bool Verbose = false, typename Printer, typename T</code>></sub><br>
<a name="print-3" href="#print-3">#</a> `void` **print** (<code>const T &<b>tr</b></code> [<code>, const Printer &<b>printer</b></code>]) `const` [<>](../../../src/binary_tree/base.hpp#L)

Prints the tree or subtree to the ***stdout***. If `Verbose` is set to `true`, aditional internal tree information is also displayed.

**<u>Note</u>:** `Printer` should print an element to the ***stdout*** without the *new line* character.

#### Example
```cpp
struct Print {
	void operator() (const int &i) const {
		std::cout << i ;
	}
};

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 6, 4, 1};
	gmd::binary_tree_multiset<gmd::tree_rb, int> b{2, 3, 5, 7, 5};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(int &x: b) std::cout << x << ' '; std::cout << '\n';

	std::cout << "\n"; a.print<true>(Print());
	std::cout << "\n"; b.print<true, Print>();
	std::cout << "\n"; b.print(b.root().right(), [](const int &i){ std::cout << i; });
}
```
##### Output
```
a: 1 1 3 4 4 6
b: 2 3 5 5 7

      ┌──╴• 6
  ┌──╴• 4
  │   └──╴• 4
─╴• 3
  │   ┌──╴• 1
  └──╴+ 1

      ┌──╴R 7
  ┌──╴B 5
  │   └──╴R 5
─╴B 3
  └──╴B 2

  ┌──╴7
┄╴5
  └──╴5
```
