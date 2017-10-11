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
	gmd::point_kd_tree_multimap<2, intpair, int, Comp> a{{{1,0},0}, {{2,1},0}, {{3,0},0}}, b{{{2,1},1}};
	gmd::point_kd_tree_multimap<2, intpair, int, Comp> c;
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(int2pair &x: b) std::cout << x << ' '; std::cout << '\n';

	b.transfer(a, a.root());
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(int2pair &x: b) std::cout << x << ' '; std::cout << '\n';

	c.transfer(a, a.begin());
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(int2pair &x: c) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
