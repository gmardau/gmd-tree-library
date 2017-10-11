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
	gmd::point_kd_tree_multimap<2, intpair, int, Comp> a{{{1,2},0}, {{3,1},0}, {{4,2},0}};
	gmd::point_kd_tree_multimap<2, intpair, int, Comp> b{{{1,2},0}, {{1,2},1}, {{3,1},0}, {{4,2},0}};

	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(int2pair &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "a == b: " << (a == b ? "true" : "false") << '\n';
	std::cout << "b != a: " << (b != a ? "true" : "false") << '\n';

	return 0;
}
