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
	// (1) Default constructor
	gmd::point_kd_tree_map<2, intpair, int, Comp> a;
	a.insert({{{1,4},0}, {{3,2},0}, {{5,6},0}});
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	// (2) Range constructor
	gmd::point_kd_tree_map<2, intpair, int, Comp> b(++a.begin(), a.end());
	std::cout << "b: "; for(int2pair &x: b) std::cout << x << ' '; std::cout << '\n';

	// (3) Copy constructor
	gmd::point_kd_tree_map<2, intpair, int, Comp> c(a);
	c.insert({{2,3},0});
	std::cout << "c: "; for(int2pair &x: c) std::cout << x << ' '; std::cout << '\n';

	// (4) Move constructor
	gmd::point_kd_tree_map<2, intpair, int, Comp> d(std::move(b));
	std::cout << "b: "; for(int2pair &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(int2pair &x: d) std::cout << x << ' '; std::cout << '\n';

	// (5) Initializer list constructor
	gmd::point_kd_tree_map<2, intpair, int, Comp> e{{{4,1},0}, {{6,2},0}, {{5,3},0}};
	std::cout << "e: "; for(int2pair &x: e) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
