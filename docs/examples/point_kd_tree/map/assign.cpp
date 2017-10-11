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
	// (1) Copy assignment
	gmd::point_kd_tree_map<2, intpair, int, Comp> a{{{3,2},0}, {{5,1},0}, {{2,4},0}};
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';
	gmd::point_kd_tree_map<2, intpair, int, Comp> b; b = a;
	std::cout << "b: "; for(int2pair &x: b) std::cout << x << ' '; std::cout << '\n';

	// (2) Move assignment
	gmd::point_kd_tree_multimap<2, intpair, int, Comp> c{{{1,2},0}, {{6,3},0}, {{1,2},1}};
	std::cout << "c: "; for(int2pair &x: c) std::cout << x << ' '; std::cout << '\n';
	gmd::point_kd_tree_map<2, intpair, int, Comp> d; d = std::move(c);
	std::cout << "c: "; for(int2pair &x: c) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(int2pair &x: d) std::cout << x << ' '; std::cout << '\n';

	// (3) Initializer list assignment
	a = {{{7,1},0}, {{7,2},0}};
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
