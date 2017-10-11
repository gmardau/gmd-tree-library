# gmd::point_kd_tree_set

```cpp
template <
	unsigned short int K,
	typename Key,
	typename Comparator,
	bool Balanced = false,
	typename Equal = std::equal_to<Key>
	typename Allocator = std::allocator<Key>
> struct point_kd_tree_set;
```

`gmd::point_kd_tree_set` is a container that stores a set of (unique) elements of type `Key` in a k-d tree structure, whose number of dimensions is defined by the template parameter `K`.

The space partitioning is done by using a key comparison function/object of type `Comparator`, whose mechanism follows the *strict weak ordering* formalization. A valid comparison type must include a function with a signature similar to what follows:

&emsp;&emsp;`bool` **operator()** (<code>unsigned short int <b>d</b>, const Key &<b>k1</b>, const Key &<b>k2</b></code>)<br>
&emsp;&emsp;&emsp;&emsp;The function returns `true` if `k1` is ***lesser*** than `k2` in the `d`'th dimension (starting at `0`); `false` otherwise.

Because this container supports multiple dimensions, the cost of comparing the equivalence of two keys through the `Comparator` function/object alone would be too costly. As such, an additional function/object of type `Equal`, which gets defaulted to [`std::equal_to`](http://en.cppreference.com/w/cpp/utility/functional/equal_to), is requested. The template parameter `Allocator` defines the type of allocator that will be used to allocate the elements in the container, and it is defaulted to [`std::allocator`](http://en.cppreference.com/w/cpp/memory/allocator).

Being a **Point** k-d tree implies that the inserted elements also act as space dividers. This means that if the order by which the elements are inserted is not carefully planned, the tree can easily become unbalanced. The template parameter `Balanced` specifies if the tree should self-balance without user intervention. The self-balancing mechanism uses the same algorithm as Weight-balanced binary trees.

---

| Member type | Definition |
|:-|:-|
| *`key_type`* | `Key` |
| *`value_type`* | `Key` |
| *`size_type`* | [`std::size_t`](http://en.cppreference.com/w/cpp/types/size_t) |
| *`difference_type`* | [`std::ptrdiff_t`](http://en.cppreference.com/w/cpp/types/ptrdiff_t) |
| *`key_compare`* | `Comparator` |
| *`value_compare`* | `Comparator` |
| *`key_equal`* | `Equal` |
| *`value_equal`* | `Equal` |
| *`allocator_type`* | `Allocator` |
| *`reference`* | <code><i>value_type</i> &</code> |
| *`const_reference`* | <code>const <i>value_type</i> &</code> |
| *`pointer`* | <code><i>value_type</i> *</code> |
| *`const_pointer`* | <code>const <i>value_type</i> *</code> |
| *`iterator`*<br>*`traversor`* | [Point k-d tree traversor](traversal.md#traversor) |
| *`const_iterator`*<br>*`const_traversor`* | Constant [Point k-d tree traversor](traversal.md#traversor) |
| *`range`* | [Point k-d tree range](range.md#range) |
| *`const_range`* | Constant [Point k-d tree range](range.md#range) |

---

### Constructor

<a name="constructor-0" href="#constructor-0">#</a> **point_kd_tree_set** ([<code>const <i>key_compare</i> &<b>c</b>, const <i>key_equal</i> &<b>e</b>, const <i>allocator_type</i> &<b>a</b></code>]) [<>](../../../src/point_kd_tree/base.hpp#L)

*Default constructor*&emsp;Constructs an empty container.

<sub>template <<code>typename T1, typename T2</code>></sub><br>
<a name="constructor-1" href="#constructor-1">#</a> **point_kd_tree_set** (<code>const T1 &<b>first</b>, const T2 &<b>last</b></code> [<code>, const <i>key_compare</i> &<b>c</b>, const <i>key_equal</i> &<b>e</b>, const <i>allocator_type</i> &<b>a</b></code>]) [<>](../../../src/point_kd_tree/base.hpp#L)

*Range constructor*&emsp;Constructs the container with the contents of the range [`first`, `last`). It is equivalent to call the *default constructor* followed by [`insert(first, last)`](#insert-2).

<a name="constructor-2" href="#constructor-2">#</a> **point_kd_tree_set** (<code>const <i>point_kd_tree_set</i> &<b>other</b></code> [<code>, const <i>key_compare</i> &<b>c</b>, const <i>key_equal</i> &<b>e</b>, const <i>allocator_type</i> &<b>a</b></code>]) [<>](../../../src/point_kd_tree/base.hpp#L)

*Copy constructor*&emsp;Constructs the container with the copy of the contents of `other`. If a comparator or an equal or an allocator are not provided, they are obtained by copy from the ones in `other`. In the case of the allocator, the following is used: <code><a href="http://en.cppreference.com/w/cpp/memory/allocator_traits">std::allocator_traits</a><<i>allocator_type</i>>::select_on_container_copy_construction()</code>.

<a name="constructor-3" href="#constructor-3">#</a> **point_kd_tree_set** (<code><i>point_kd_tree_set</i> &&<b>other</b></code> [<code>, const <i>key_compare</i> &<b>c</b>, const <i>key_equal</i> &<b>e</b>, const <i>allocator_type</i> &<b>a</b></code>]) [<>](../../../src/point_kd_tree/base.hpp#L)

*Move constructor*&emsp;Constructs the container with the contents of `other`, using move semantics. If a comparator or an equal or an allocator are not provided, they are obtained by move-construction from the ones in `other`.

<a name="constructor-4" href="#constructor-4">#</a> **point_kd_tree_set** (<code>const <a href="http://en.cppreference.com/w/cpp/utility/initializer_list">std::initializer_list</a><<i>value_type</i>> &<b>il</b></code> [<code>, const <i>key_compare</i> &<b>c</b>, const <i>key_equal</i> &<b>e</b>, const <i>allocator_type</i> &<b>a</b></code>]) [<>](../../../src/point_kd_tree/base.hpp#L)

*Initializer list constructor*&emsp;Constructs the container with the contents of the initializer list `il`. It is equivalent to call the *default constructor* followed by [`insert(il)`](#insert-3).

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	// (1) Default constructor
	gmd::point_kd_tree_set<2, intpair, Comp> a;
	a.insert({{1,4}, {3,2}, {5,6}});
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	// (2) Range constructor
	gmd::point_kd_tree_set<2, intpair, Comp> b(++a.begin(), a.end());
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	// (3) Copy constructor
	gmd::point_kd_tree_set<2, intpair, Comp> c(a);
	c.insert({2,3});
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';

	// (4) Move constructor
	gmd::point_kd_tree_set<2, intpair, Comp> d(std::move(b));
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(intpair &x: d) std::cout << x << ' '; std::cout << '\n';

	// (5) Initializer list constructor
	gmd::point_kd_tree_set<2, intpair, Comp> e{{4,1}, {6,2}, {5,3}};
	std::cout << "e: "; for(intpair &x: e) std::cout << x << ' '; std::cout << '\n';
}
```
##### Output
```
a: (1,4) (3,2) (5,6)
b: (3,2) (5,6)
c: (2,3) (1,4) (3,2) (5,6)
b:
d: (3,2) (5,6)
e: (4,1) (5,3) (6,2)
```

---

### Destructor

<a name="destructor-" href="#destructor-">#</a> **~point_kd_tree_set** () [<>](../../../src/point_kd_tree/base.hpp#L)

Destructs and deallocates the container and all its elements.

---

### Assign operator

<a name="assign-0" href="#assign-0">#</a> <code><i>point_kd_tree_set</i> &</code>**operator=** (<code>const <i>point_kd_tree</i> &<b>other</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

*Copy assignment*&emsp;Replaces the contents of the containers with a copy of the contents of `other`. The allocator is replaced only if <code><a href="http://en.cppreference.com/w/cpp/memory/allocator_traits">std::allocator_traits</a><<i>allocator_type</i>>::propagate_on_container_copy_assignment::value</code> is set to `true`.

<a name="assign-1" href="#assign-1">#</a> <code><i>point_kd_tree_set</i> &</code>**operator=** (<code><i>point_kd_tree</i> &&<b>other</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

*Move assignment*&emsp;Replaces the contents with those of `other` using move semantics. The allocator is replaced only if <code><a href="http://en.cppreference.com/w/cpp/memory/allocator_traits">std::allocator_traits</a><<i>allocator_type</i>>::propagate_on_container_move_assignment::value</code> is set to `true`. If not, and neither <code><a href="http://en.cppreference.com/w/cpp/memory/allocator_traits">std::allocator_traits</a><<i>allocator_type</i>>::is_always_equal::value</code> is set `true` nor the allocators compare equal, then the elements are copied instead.

<a name="assign-2" href="#assign-2">#</a> <code><i>point_kd_tree_set</i> &</code>**operator=** (<code><a href="http://en.cppreference.com/w/cpp/utility/initializer_list">std::initializer_list</a><<i>value_type</i>> &<b>il</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

*Initializer list assignment*&emsp;Replaces the contents with those of the initializer list `il`.

**<u>Note</u>:** All four variants of *`point_kd_tree`* (*`set`*, *`map`*, *`multiset`*, *`multimap`*) are accepted, as well as any template signature, as long as *`value_type`* is the same. When copying the elements, if the containers are conversion compatible, then the structure of `other` is replicated; otherwise, the elements are copied one by one. For more information, refer to [type conversion](../tree.md#type-conversion-1).

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	// (1) Copy assignment
	gmd::point_kd_tree_set<2, intpair, Comp> a{{3,2}, {5,1}, {2,4}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	gmd::point_kd_tree_set<2, intpair, Comp> b; b = a;
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	// (2) Move assignment
	gmd::point_kd_tree_multiset<2, intpair, Comp> c{{1,2}, {6,3}, {1,2}};
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';
	gmd::point_kd_tree_set<2, intpair, Comp> d; d = std::move(c);
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(intpair &x: d) std::cout << x << ' '; std::cout << '\n';

	// (3) Initializer list assignment
	a = {{7,1}, {7,2}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
}
```
##### Output
```
a: (2,4) (3,2) (5,1)
b: (2,4) (3,2) (5,1)
c: (1,2) (1,2) (6,3)
c:
d: (1,2) (6,3)
a: (7,1) (7,2)
```

---

### Comparison operators

<a name="equal-0" href="#equal-0">#</a> `bool` **operator==** (<code><i>point_kd_tree</i> &<b>other</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="equal-1" href="#equal-1">#</a> `bool` **operator==** (<code>const <i>point_kd_tree</i> &<b>other</b></code>) `const` [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="not_equal-0" href="#not_equal-0">#</a> `bool` **operator!=** (<code><i>point_kd_tree</i> &<b>other</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="not_equal-1" href="#not_equal-1">#</a> `bool` **operator!=** (<code>const <i>point_kd_tree</i> &<b>other</b></code>) `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Checks if `*this` and `other` contain the same elements.

**<u>Note</u>:** All four variants of *`point_kd_tree`* (*`set`*, *`map`*, *`multiset`*, *`multimap`*) are accepted, as well as any template signature, as long as either *`key_type`* is the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a{{1,1}, {3,1}, {4,2}};
	gmd::point_kd_tree_set<2, intpair, Comp> b{{1,2}, {3,1}, {4,2}};

	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "a == b: " << (a == b ? "true" : "false") << '\n';
	std::cout << "b != a: " << (b != a ? "true" : "false") << '\n';
}
```
##### Output
```
a: (1,1) (3,1) (4,2)
b: (1,2) (3,1) (4,2)
a == b: false
b != a: true
```

---

## Observers

<a name="key_comp" href="#key_comp">#</a> *`key_compare`* **key_comp** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a copy of the function object used to compare the keys.

<a name="value_comp" href="#value_comp">#</a> *`value_compare`* **value_comp** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a copy of the function object that compares the values.

<a name="get_comparator" href="#get_comparator">#</a> <code><i>key_compare</i> &</code> **get_comparator** () [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="get_comparator" href="#get_comparator">#</a> <code>const <i>key_compare</i> &</code> **get_comparator** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns the comparator associated with the container.

<a name="key_eq" href="#key_eq">#</a> *`key_equal`* **key_eq** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a copy of the function object used to check if the keys are equivalent.

<a name="value_eq" href="#value_eq">#</a> *`value_equal`* **value_eq** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a copy of the function object that checks if the values are equivalent.

<a name="get_equal" href="#get_equal">#</a> <code><i>key_equal</i> &</code> **get_equal** () [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="get_equal" href="#get_equal">#</a> <code>const <i>key_equal</i> &</code> **get_equal** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns the equal function object associated with the container.

<a name="get_allocator" href="#value_comp">#</a> *`allocator_type`* **get_allocator** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a copy of the allocator associated with the container.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	using kdtset_a = gmd::point_kd_tree_set<2, intpair, Comp>;
	using kdtset_b = gmd::point_kd_tree_set<1, intpair, Comp>;
	kdtset_a a;
	kdtset_b b;

	kdtset_a::key_compare x = a.key_comp();
	kdtset_b::value_equal y = b.value_eq();
	std::cout << "a (d=0, (1,2) < (2,3)): " << (x(0, {1,2}, {2,3}) ? "true" : "false") << '\n';
	std::cout << "b ((1,2) == (1,3)): " << (y({1,2}, {1,3}) ? "true" : "false") << '\n';

	kdtset_a::allocator_type z = a.get_allocator();
	intpair *i = std::allocator_traits<kdtset_a::allocator_type>::allocate(z, 2);
	new(&i[0]) intpair(1,2);
	new(&i[1]) intpair(3,2);
	std::cout << "i[0]: " << i[0] << '\n';
	std::cout << "i[1]: " << i[1] << '\n';
	i[0].~intpair();
	i[1].~intpair();
	std::allocator_traits<kdtset_a::allocator_type>::deallocate(z, i, 2);
}
```
##### Output
```
a (d=0, (1,2) < (2,3)): true
b ((1,2) == (1,3)): false
i[0]: (1,2)
i[1]: (3,2)
```

---

## Traversors

<a name="root-0" href="#root-0">#</a> *`traversor`* **root** () [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="root-1" href="#root-1">#</a> *`const_traversor`* **root** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="croot" href="#croot">#</a> *`const_traversor`* **croot** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a traversor to the root element of the container.
If the container is empty, the returned traversor will be empty (***invalid***) and cannot be dereferenced.

<a name="begin-0" href="#begin-0">#</a> *`traversor`* **begin** () [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="begin-1" href="#begin-1">#</a> *`const_traversor`* **begin** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="cbegin" href="#cbegin">#</a> *`const_traversor`* **cbegin** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a traversor to the first element of the container.
If the container is empty, the returned traversor will be equivalent to [`end()`](#end-0).

<a name="end-0" href="#end-0">#</a> *`traversor`* **end** () [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="end-1" href="#end-1">#</a> *`const_traversor`* **end** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<a name="cend" href="#cend">#</a> *`const_traversor`* **cend** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a traversor to the element following the last element of the container (***past-the-end***). As such, it cannot be dereferenced.

#### Example

```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	using kdtset = gmd::point_kd_tree_set<2, intpair, Comp>;
	kdtset a{{1,6}, {8,5}, {4,2}, {3,2}, {7,3}};

	std::cout << "a: ";
	for(kdtset::traversor x = a.begin(); x != a.end(); ++x)
		std::cout << *x << " ";
	std::cout << "\n";

	kdtset::traversor x = a.root();
	std::cout << "root: " << *x << "\n";
	if(x.greater()())
		std::cout << "greater: " << *x.greater() << "\n";
}
```
##### Output
```
a: (3,2) (1,6) (4,2) (7,3) (8,5)
root: (4,2)
greater: (8,5)
```

---

## Capacity

<a name="empty" href="#empty">#</a> `bool` **empty** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns `true` if the container is empty; `false` otherwise.

<a name="size" href="#size">#</a> *`size_type`* **size** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns the number of elements in the container.

<a name="max_size" href="#max_size">#</a> *`size_type`* **max_size** () `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns the maximum number of elements the container is able to hold due to system or library implementation limitations. However, the size of the container may be limited to a smaller value at runtime.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a;

	std::cout << "empty: " << (a.empty() ? "true" : "false") << "\n";
	std::cout << "size: " << a.size() << "\n";
	a.insert({{3,2}, {1,3}, {2,4}});
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "empty: " << (a.empty() ? "true" : "false") << "\n";
	std::cout << "size: " << a.size() << "\n";

	std::cout << "max_size: " << a.max_size() << "\n";
}
```
##### Output
```
empty: true
size: 0
a: (1,3) (2,4) (3,2)
empty: false
size: 3
max_size: 576460752303423487
```

---

## Modifiers

### Clear

<a name="clear" href="#clear">#</a> `void` **clear** () [<>](../../../src/point_kd_tree/base.hpp#L)

Removes all elements from the container.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a{{4,1}, {2,3}, {3,5}, {1,4}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	a.clear();
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "size: " << a.size() << "\n";
}
```
##### Output
```
a: (2,3) (1,4) (3,5) (4,1)
a:
size: 0
```

---

### Insert

<sub>template <<code>bool Replace = false</code>></sub><br>
<a name="insert-0" href="#insert-0">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>traversor</i>, bool></code> **insert** (<code>const <i>value_type</i> &<b>info</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>bool Replace = false</code>></sub><br>
<a name="insert-1" href="#insert-1">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>traversor</i>, bool></code> **insert** (<code><i>value_type</i> &&<b>info</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Inserts `info` in the container.
Returns a pair consisting of a traversor to the inserted element (or to the element that prevented the insertion) and a boolean value set to `true` if the insertion took place.

<sub>template <<code>bool Replace = false, typename T1, typename T2</code>></sub><br>
<a name="insert-2" href="#insert-2">#</a> *`size_type`* **insert** (<code>const T1 &<b>first</b>, const T2 &<b>last</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Inserts elements from range [`first`, `last`).
Returns the number of elements inserted.
Even though `first` and `last` can be of different types, `last` must be reachable from `first` and `T1` needs to satisfy [EqualityComparable](http://en.cppreference.com/w/cpp/concept/EqualityComparable) towards `T2`.

<sub>template <<code>bool Replace = false</code>></sub><br>
<a name="insert-3" href="#insert-3">#</a> *`size_type`* **insert** (<code><a href="http://en.cppreference.com/w/cpp/utility/initializer_list">std::initializer_list</a><<i>value_type</i>> &<b>il</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Inserts elements from the initializer list `il`. Returns the number of elements inserted.

**<u>Note</u>:** If `Replace` is set to `true` and an element that compares equivalent already exists in the container, its *`value_type`* value is replaced. Also, the return values (`bool` and *`size_type`*) are set to `true` and `+1` only if the elements were inserted ***without*** need for replacement.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a, b;

	auto y = a.insert({2,1});
	std::cout << "inserted: " << (y.second ? "true" : "false") << "\n";
	std::cout << "element: " << *y.first << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	size_t z = a.insert({{1,4}, {2,1}, {3,0}, {4,2}});
	std::cout << "# inserted: " << z << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	b.insert(a.root(), a.cend());
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';
}
```
##### Output
```
inserted: true
element: (2,1)
a: (2,1)
# inserted: 3
a: (1,4) (2,1) (3,0) (4,2)
b: (2,1) (3,0) (4,2)
```

---

### Emplace

<sub>template <<code>bool Replace = false, typename... Args</code>></sub><br>
<a name="emplace-" href="#emplace-">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>traversor</i>, bool></code> **emplace** (<code>Args&&... <b>info</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Inserts a new element in the container constructed *in-place* with `info`.
Returns a pair consisting of a traversor to the inserted element (or to the element that prevented the insertion) and a boolean value set to `true` if the insertion took place.

**Note:** If `Replace` is set to `true` and an element the compares equivalent already exists in the container, its *`value_type`* value is replaced. Also, the return value (`bool`) is set to `true` only if the element was inserted ***without*** need for replacement.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a;

	auto y = a.emplace(2, 0);
	std::cout << "emplaced: " << (y.second ? "true" : "false") << "\n";
	std::cout << "element: " << *y.first << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	y = a.emplace<true>(2, 1);
	std::cout << "emplaced: " << (y.second ? "true" : "false") << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
}
```
##### Output
```
emplaced: true
element: (2,0)
a: (2,0)
emplaced: true
a: (2,0) (2,1)
```

---

### Erase

<a name="erase-0" href="#erase-0">#</a> `bool` **erase** (<code>const <i>key_type</i> &<b>key</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Removes the element that compares equivalent to `key`, if existent.
Returns `true` if an element is found and removed; `false` otherwise.

<sub>template <<code>typename T</code>></sub><br>
<a name="erase-1" href="#erase-1">#</a> `void` **erase** (<code>const T &<b>tr</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Removes the element referenced by `tr`, which must be a non const traversor.

<a name="erase-2" href="#erase-2">#</a> *`size_type`* **erase** (<code>const <a href="http://en.cppreference.com/w/cpp/utility/initializer_list">std::initializer_list</a><<i>key_type</i>> &<b>il</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Removes the elements that compare equivalent to the keys in the initializer list `il`.
Returns the amount of elements removed.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a{{1,2}, {2,4}, {3,1}, {4,5}, {5,3}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	a.erase({4,5});
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	size_t y = a.erase({{1,3}, {2,4}, {5,3}});
	std::cout << "# erased: " << y << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
}
```
##### Output
```
a: (1,2) (2,4) (3,1) (5,3) (4,5)
a: (1,2) (2,4) (3,1) (5,3)
# erased: 2
a: (1,2) (3,1)
```

---

### Transfer

<sub>template<<code>bool Replace = false, typename T</code>></sub><br>
<a name="transfer-" href="#transfer-">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>traversor</i>, bool></code> **transfer** (<code><i>point_kd_tree</i> &<b>other</b>, const T &<b>tr</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Transfers an element from `other` into the container, if it does not exist.
Returns a pair consisting of a traversor to the transferred element (or to the element that prevented the transferral) and a boolean value set to `true` if the transferral took place.
`tr` must be a non const traversor in `other`.

**<u>Note</u>:** If `Replace` is set to `true` and an element that compares equivalent already exists in the container, its *`value_type`* value is replaced. Also, the return value (`bool`) is set to `true` only if the element was transferred without need for replacement.
All four variants of *`point_kd_tree`* (*`set`*, *`map`*, *`multiset`*, *`multimap`*) are accepted, as well as any template signature, as long as *`value_type`* is the same.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a{{1,0}, {2,1}, {3,0}}, b{{2,1}};
	gmd::point_kd_tree_set<2, intpair, Comp> c;
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	auto y = b.transfer<true>(a, a.root());
	std::cout << "transferred: " << (y.second ? "true" : "false") << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	c.transfer(a, a.begin());
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';
}
```
###### Output
```
a: (1,0) (2,1) (3,0)
b: (2,1)
transferred: false
a: (1,0) (3,0)
b: (2,1)
a: (3,0)
c: (1,0)
```

---

### Merge

<sub>template<<code>bool Replace = false</code>></sub><br>
<a name="merge-" href="#merge-">#</a> *`size_type`* **merge** (<code><i>point_kd_tree</i> &<b>other</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Merges the values of both containers into `*this`. This is achieved by attempting to transfer the elements of `other` one by one using `transfer`.
Returns the number of elements merged from `other` into `*this`.

**<u>Note</u>:** If `Replace` is set to `true` and an element that compares equivalent already exists in the container, its *`value_type`* value is replaced.
All four variants of *`point_kd_tree`* (*`set`*, *`map`*, *`multiset`*, *`multimap`*) are accepted, as well as any template signature, as long as *`value_type`* is the same. If the container is empty and the containers are conversion compatible, then the structure of `other` is replicated; otherwise, the elements are copied one by one. For more information, refer to [type conversion](../tree.md#type-conversion-1).

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_multiset<2, intpair, Comp> a{{1,1}, {1,1}, {2,4}, {3,2}};
	gmd::point_kd_tree_set<2, intpair, Comp> b{{2,4}};
	gmd::point_kd_tree_set<2, intpair, Comp> c{{2,4}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';

	b.merge(a);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	c.merge<true>(a);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';
}
```
##### Output
```
a: (1,1) (1,1) (2,4) (3,2)
b: (2,4)
c: (2,4)
a: (1,1) (2,4)
b: (1,1) (2,4) (3,2)
a:
c: (1,1) (2,4)
```

---

### Swap

<a name="swap-" href="#swap-">#</a> `void` **swap** (<code><i>point_kd_tree</i> &<b>other</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Exchanges the contents of the container with those of `other`.

**<u>Note</u>:** All four variants of *`point_kd_tree`* (*`set`*, *`map`*, *`multiset`*, *`multimap`*) are accepted, as well as any template signature, as long as *`value_type`* is the same. When copying the elements, if the containers are conversion compatible, then the structure of `other` is replicated, and vice-versa; otherwise, the elements are copied one by one. For more information, refer to [type conversion](../tree.md#type-conversion-1).

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

using int2pair = std::pair<intpair, int>;
struct Comp {
	bool operator() (unsigned short d, const int2pair &i1, const int2pair &i2) {
		return d == 0 ? i1.first.first < i2.first.first : i1.first.second < i2.first.second; }
};
struct Eq {
	bool operator() (const int2pair &i1, const int2pair &i2) {
		return i1.first.first == i2.first.first && i1.first.second == i2.first.second; }
};

struct Comp2 {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first > i2.first : i1.second > i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, int2pair, Comp, false, Eq> a{{{1,3},0}, {{3,2},0}, {{4,2},0}, {{5,1},0}};
	gmd::point_kd_tree_multimap<2, intpair, int, Comp2, true> b{{{2,6},0}, {{2,6},1}, {{3,1},0}};
	std::cout << "a: "; for(int2pair &x: a) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';
	std::cout << "b: "; for(int2pair &x: b) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';

	a.swap(b);
	std::cout << "a: "; for(int2pair &x: a) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';
	std::cout << "b: "; for(int2pair &x: b) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';
}
```
##### Output
```
a: (3,2),0 (1,3),0 (4,2),0 (5,1),0
b: (3,1),0 (2,6),0 (2,6),1
a: (2,6),0 (3,1),0
b: (4,2),0 (5,1),0 (3,2),0 (1,3),0
```

---

### Balance

<a name="balance-1" href="#balance-1">#</a> `void` **balance** () [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>typename T</code>></sub><br>
<a name="balance-2" href="#balance-2">#</a> `void` **balance** (<code>const T &<b>tr</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)

Balances the tree or subtree.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a{{2,1}};
	a.insert({{3,0}, {5,4}, {6,3}, {7,5}});
	a.print([](const intpair &i){ std::cout << i; });

	a.balance(a.root().greater().greater());
	std::cout << "\n"; a.print([](const intpair &i){ std::cout << i; });

	a.balance();
	std::cout << "\n"; a.print([](const intpair &i){ std::cout << i; });
}
```
##### Output
```
              ┌──╴(7,5)
          ┌──╴(6,3)
      ┌──╴(5,4)
  ┌──╴(3,0)
─╴(2,1)

          ┌──╴(7,5)
      ┌──╴(6,3)
      │   └──╴(5,4)
  ┌──╴(3,0)
─╴(2,1)

  ┌──╴(7,5)
  │   └──╴(6,3)
─╴(5,4)
  └──╴(2,1)
      └──╴(3,0)
```

---

## Lookup

### Count

<sub>template <<code>typename Key</code>></sub><br>
<a name="count-0" href="#count-0">#</a> *`size_type`* **count** (<code>const Key &<b>key</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="count-1" href="#count-1">#</a> *`size_type`* **count** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns the number of elements with a key that compares equivalent to `key`. Because this container does not allow duplicates, the return value is either `0` or `1`.

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a{{1,2}, {3,1}, {4,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "count (1,1): " << a.count(intpair{1,1}) << "\n";
	std::cout << "count (1,2): " << a.count(intpair{1,2}) << "\n";
}
```
##### Output
```
a: (1,2) (3,1) (4,0)
count (1,1): 0
count (1,2): 1
```

---

### Contains

<sub>template <<code>typename Key</code>></sub><br>
<a name="contains-0" href="#contains-0">#</a> `bool` **contains** (<code>const Key &<b>key</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="contains-1" href="#contains-1">#</a> `bool` **contains** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Checks if there exists an element with a key that compares equivalent to `key`.
Returns `true` if such element exists; `false` otherwise.

It is equivalent to [`count(key)`](#count-0) or <code><a href="#find-0">find(key)</a> != <a href="#end-0">end()</a></code>.

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a{{1,2}, {3,1}, {4,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "contains (3,1): " << (a.contains(intpair{3,1}) ? "true" : "false") << "\n";
	std::cout << "contains (3,2): " << (a.contains(intpair{3,2}) ? "true" : "false") << "\n";
}
```
##### Output
```
a: (1,2) (3,1) (4,0)
contains (3,1): true
contains (3,2): false
```

---

### Find

<sub>template <<code>typename Key</code>></sub><br>
<a name="find-0" href="#find-0">#</a> *`traversor`* **find** (<code>const Key &<b>key</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="find-1" href="#find-1">#</a> *`const_traversor`* **find** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a traversor of an element with a key equivalent to `key`. If no such element exists, a past-the-end traversor (e.g. [`end()`](#end-0)) is returned.

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
using intpair = std::pair<int, int>;
using doublepair = std::pair<double, double>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	using is_transparent = void;
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
	bool operator() (unsigned short d, const doublepair &d1, const intpair &i2) {
		return d == 0 ? d1.first < i2.first : d1.second < i2.second; }
	bool operator() (unsigned short d, const intpair &i1, const doublepair &d2) {
		return d == 0 ? i1.first < d2.first : i1.second < d2.second; }
};

int main(const int, const char **)
{
	using kdtset = gmd::point_kd_tree_set<2, intpair, Comp>;
	kdtset a{{1,2}, {3,1}, {4,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "find (1.0,3.0): ";
	kdtset::traversor y = a.find(doublepair{1.0,3.0});
	if(y != a.end()) std::cout << "true - " << *y << "\n";
	else             std::cout << "false\n";

	std::cout << "find (4.0,0.0): ";
	kdtset::const_traversor z = a.find(doublepair{4.0,0.0});
	if(z != a.cend()) std::cout << "true - " << *z << "\n";
	else              std::cout << "false\n";
}
```
##### Output
```
a: (1,2) (3,1) (4,0)
find (1.0,3.0): false
find (4.0,0.0): true - (4,0)
```

---

### Equal range

<sub>template <<code>typename Key</code>></sub><br>
<a name="equal_range-0" href="#equal_range-0">#</a> *`range`* **equal_range** (<code>const Key &<b>key</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>typename Key</code>></sub><br>
<a name="equal_range-1" href="#equal_range-1">#</a> *`const_range`* **equal_range** (<code>const Key &<b>key</b></code>) `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a range containing all the elements with a key equivalent to `key`. Because this container does not allow duplicates, the range will have at most size 1.

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a{{1,2}, {3,1}, {4,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "equal_range (2,0): ";
	auto y = a.equal_range(intpair{2,0});
	if(y.empty()) std::cout << "no element found\n";
	else          std::cout << "element found\n";

	std::cout << "equal_range (3,1): ";
	y = a.equal_range(intpair{3,1});
	for(auto z = y.begin(); z != y.end(); ++z)
		std::cout << *z << ' ';
	std::cout << "\n";
}
```
##### Output
```
a: (1,2) (3,1) (4,0)
equal_range (2,0): no element found
equal_range (3,1): (3,1)
```

---

### Nearest neighbor

<sub>template <<code>typename Measure, typename Key</code>></sub><br>
<a name="nearest_neighbor-0" href="#nearest_neighbor-0">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>traversor</i>, double></code> **nearest_neighbor** (<code>const Key &<b>key</b>, Measure &<b>measure</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>typename Measure, typename Key</code>></sub><br>
<a name="nearest_neighbor-1" href="#nearest_neighbor-1">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>const_traversor</i>, double></code> **nearest_neighbor** (<code>const Key &<b>key</b>, Measure &<b>measure</b></code>) `const` [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>typename Measure, typename Key</code>></sub><br>
<a name="nearest_neighbor-2" href="#nearest_neighbor-2">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>traversor</i>, double></code> **nearest_neighbor** (<code>const Key &<b>key</b></code> [<code>, const Measure &<b>measure</b></code>]) [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>typename Measure, typename Key</code>></sub><br>
<a name="nearest_neighbor-3" href="#nearest_neighbor-3">#</a> <code><a href="http://en.cppreference.com/w/cpp/utility/pair">std::pair</a><<i>const_traversor</i>, double></code> **nearest_neighbor** (<code>const Key &<b>key</b></code> [<code>, const Measure &<b>measure</b></code>]) `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Finds the closest element in the container to a given `key`. Returns a pair consisting of a traversor to the element and the distance between its key and `key`. `Measure` is a function/object type that computes the distance between two keys. It must include functions with signatures similar to what follows:

&emsp;&emsp;`double` **operator()** (<code>const <i>key_type</i> &<b>k1</b>, const <i>key_type</i> &<b>k2</b></code>)<br>
&emsp;&emsp;&emsp;&emsp;The function returns the distance between `k1` and `k2`.

&emsp;&emsp;`double` **operator()** (<code>unsigned short int <b>d</b>, const <i>key_type</i> &<b>k1</b>, const <i>key_type</i> &<b>k2</b></code>)<br>
&emsp;&emsp;&emsp;&emsp;The function returns the distance between `k1` and `k2` in the `d`'th dimension (starting at `0`).

**<u>Note</u>:** The function is ***valid*** only if either `Key` and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

struct Measure {
	double operator() (unsigned short d, const intpair &i1, const intpair &i2) const {
		return d == 0 ? std::abs(i1.first - i2.first) : std::abs(i1.second - i2.second); }
	double operator() (const intpair &i1, const intpair &i2) const {
		return std::sqrt(std::pow(i1.first - i2.first, 2) + std::pow(i1.second - i2.second, 2)); }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a{{1,1}, {2,7}, {4,6}, {5,2}, {6,7}, {7,3}, {9,4}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	auto y = a.nearest_neighbor<Measure>(intpair{3,3});
	std::cout << "nearest neighbor (3,3): " << *y.first << " distance: " << y.second << '\n';

	y = a.nearest_neighbor(intpair{7,6}, Measure());
	std::cout << "nearest neighbor (7,6): " << *y.first << " distance: " << y.second << '\n';
}
```
##### Output
```
a: (1,1) (4,6) (2,7) (5,2) (7,3) (9,4) (6,7)
nearest neighbor (3,3): (5,2) distance: 2.23607
nearest neighbor (7,6): (6,7) distance: 1.41421
```

---

### Range search

<sub>template <<code>typename Key1, typename Key2</code>></sub><br>
<a name="range_search-0" href="#range_search-0">#</a> *`range`* **range_search** (<code>const Key1 &<b>min</b>, Key2 &<b>max</b></code>) [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>typename Key1, typename Key2</code>></sub><br>
<a name="range_search-1" href="#range_search-1">#</a> *`const_range`* **range_search** (<code>const Key1 &<b>min</b>, Key2 &<b>max</b></code>) `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Returns a range containing all the elements inside (and on) a given region, defined by `min` and `max`.

**<u>Note</u>:** The function is ***valid*** only if either `Key1`, `Key2`, and *`key_type`* are the same or <code><i>key_compare</i>::is_transparent</code> is valid.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	using kdtset = gmd::point_kd_tree_set<2, intpair, Comp>;
	kdtset a{{1,1}, {2,7}, {4,6}, {5,2}, {6,7}, {7,3}, {9,4}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	kdtset::range y = a.range_search(intpair{3,2}, intpair{7,6});
	std::cout << "range search (3,2)-(7,6): ";
	for(kdtset::range::iterator z = y.begin(); z != y.end(); ++z)
		std::cout << *z << ' ';
	std::cout << '\n';
}
```
##### Output
```
a: (1,1) (4,6) (2,7) (5,2) (7,3) (9,4) (6,7)
range search (3,2)-(7,6): (5,2) (4,6) (7,3)
```

---

## Print

<sub>template <<code>bool Verbose = false, typename Printer</code>></sub><br>
<a name="print-0" href="#print-0">#</a> `void` **print** (<code>Printer &<b>printer</b></code>) `const` [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>bool Verbose = false, typename Printer</code>></sub><br>
<a name="print-1" href="#print-1">#</a> `void` **print** ([<code>const Printer &<b>printer</b></code>]) `const` [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>bool Verbose = false, typename Printer, typename T</code>></sub><br>
<a name="print-2" href="#print-2">#</a> `void` **print** (<code>const T &<b>tr</b>, Printer &<b>printer</b></code>) `const` [<>](../../../src/point_kd_tree/base.hpp#L)<br>
<sub>template <<code>bool Verbose = false, typename Printer, typename T</code>></sub><br>
<a name="print-3" href="#print-3">#</a> `void` **print** (<code>const T &<b>tr</b></code> [<code>, const Printer &<b>printer</b></code>]) `const` [<>](../../../src/point_kd_tree/base.hpp#L)

Prints the tree or subtree to the ***stdout***. If `Verbose` is set to `true`, aditional internal tree information is also displayed.

**<u>Note</u>:** `Printer` should print an element to the ***stdout*** without the *new line* character.

#### Example
```cpp
using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

struct Print {
	void operator() (const intpair &i) const { std::cout << i ; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intpair, Comp> a{{2,1}, {3,0}, {5,4}, {6,3}, {7,2}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "\n"; a.print<true>(Print());
	std::cout << "\n"; a.print(a.root().greater(), [](const intpair &i){ std::cout << i; });
}
```
##### Output
```
a: (3,0) (2,1) (5,4) (7,2) (6,3)

  ┌──╴1 (6,3)
  │   └──╴0 (7,2)
─╴0 (5,4)
  └──╴1 (2,1)
      └──╴0 (3,0)

┄╴(6,3)
  └──╴(7,2)
```
