#include <iostream>

using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	using kdtmset_a = gmd::point_kd_tree_multiset<2, intpair, Comp>;
	using kdtmset_b = gmd::point_kd_tree_multiset<2, intpair, Comp>;
	kdtmset_a a;
	kdtmset_b b;

	kdtmset_a::key_compare x = a.key_comp();
	kdtmset_b::value_equal y = b.value_eq();
	std::cout << "a (d=0, (1,2) < (2,3)): " << (x(0, {1,2}, {2,3}) ? "true" : "false") << '\n';
	std::cout << "b ((1,2) == (1,3)): " << (y({1,2}, {1,3}) ? "true" : "false") << '\n';

	kdtmset_a::allocator_type z = a.get_allocator();
	intpair *i = std::allocator_traits<kdtmset_a::allocator_type>::allocate(z, 2);
	new(&i[0]) intpair(1,2);
	new(&i[1]) intpair(3,2);
	std::cout << "i[0]: " << i[0] << '\n';
	std::cout << "i[1]: " << i[1] << '\n';
	i[0].~intpair();
	i[1].~intpair();
	std::allocator_traits<kdtmset_a::allocator_type>::deallocate(z, i, 2);

	return 0;
}
