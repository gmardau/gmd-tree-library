#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<< (std::ostream& os, const intpair& i) {
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

	return 0;
}
