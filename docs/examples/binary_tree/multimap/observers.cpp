#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<<(std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	using btmmap_a = gmd::binary_tree_multimap<gmd::tree_avl, int, int>;
	using btmmap_b = gmd::binary_tree_multimap<gmd::tree_avl, int, int, false, std::greater<int>>;
	btmmap_a a;
	btmmap_b b;

	btmmap_a::key_compare x = a.key_comp();
	btmmap_b::value_compare y = b.value_comp();
	std::cout << "a (1 < 2): " << (x(1, 2) ? "true" : "false") << '\n';
	std::cout << "b (1 > 2): " << (y(intpair(1,0), intpair(2,0)) ? "true" : "false") << '\n';
	std::cout << "b (1 <= 2): " << (!y(intpair(1,0), intpair(2,1)) ? "true" : "false") << '\n';

	btmmap_a::allocator_type z = a.get_allocator();
	std::pair<int, int> *i = std::allocator_traits<btmmap_a::allocator_type>::allocate(z, 2);
	new(&i[0]) intpair(2, 1);
	new(&i[1]) intpair(1, 3);
	std::cout << "i[0]: " << i[0] << '\n';
	std::cout << "i[1]: " << i[1] << '\n';
	i[0].~intpair();
	i[1].~intpair();
	std::allocator_traits<btmmap_a::allocator_type>::deallocate(z, i, 2);

	return 0;
}
