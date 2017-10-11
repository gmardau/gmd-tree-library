#include <iostream>

using intpair = std::pair<int, int>;
using int2pair = std::pair<intpair, int>;
std::ostream &operator<< (std::ostream &os, const int2pair &i) {
	os << '(' << i.first.first << ',' << i.first.second << ')' << ',' << i.second; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	using kdtmmap_a = gmd::point_kd_tree_multimap<2, intpair, int, Comp>;
	using kdtmmap_b = gmd::point_kd_tree_multimap<2, intpair, int, Comp>;
	kdtmmap_a a;
	kdtmmap_b b;

	kdtmmap_a::key_compare x = a.key_comp();
	kdtmmap_b::value_equal y = b.value_eq();
	std::cout << "a (d=0, (1,2) < (2,3)): " << (x(0, {1,2}, {2,3}) ? "true" : "false") << '\n';
	std::cout << "b ((1,2) == (1,3)): " << (y({{1,2},0}, {{1,3},1}) ? "true" : "false") << '\n';

	kdtmmap_a::allocator_type z = a.get_allocator();
	int2pair *i = std::allocator_traits<kdtmmap_a::allocator_type>::allocate(z, 2);
	new(&i[0]) int2pair({1,2},0);
	new(&i[1]) int2pair({3,2},1);
	std::cout << "i[0]: " << i[0] << '\n';
	std::cout << "i[1]: " << i[1] << '\n';
	i[0].~int2pair();
	i[1].~int2pair();
	std::allocator_traits<kdtmmap_a::allocator_type>::deallocate(z, i, 2);

	return 0;
}
