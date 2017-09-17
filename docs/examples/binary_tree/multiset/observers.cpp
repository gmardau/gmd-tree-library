#include <iostream>

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

	return 0;
}
