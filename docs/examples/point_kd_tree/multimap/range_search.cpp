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
	using kdtmmap = gmd::point_kd_tree_multimap<2, intpair, int, Comp>;
	kdtmmap a{{{1,1},0}, {{2,7},0}, {{4,6},0}, {{5,2},0}, {{2,7},0}, {{6,7},0}, {{7,3},0}, {{9,4},0}};
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	kdtmmap::range y = a.range_search(intpair{3,2}, intpair{7,6});
	std::cout << "range search (3,2)-(7,6): ";
	for(kdtmmap::range::iterator z = y.begin(); z != y.end(); ++z)
		std::cout << *z << ' ';
	std::cout << '\n';

	return 0;
}
