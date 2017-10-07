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
	// (1) Copy assignment
	gmd::point_kd_tree_multiset<2, intpair, Comp> a{{3,2}, {5,1}, {2,4}, {5,1}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	gmd::point_kd_tree_multiset<2, intpair, Comp> b; b = a;
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	// (2) Move assignment
	gmd::point_kd_tree_set<2, intpair, Comp> c{{1,2}, {6,3}};
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';
	gmd::point_kd_tree_multiset<2, intpair, Comp> d; d = std::move(c);
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(intpair &x: d) std::cout << x << ' '; std::cout << '\n';

	// (3) Initializer list assignment
	a = {{7,1}, {7,2}, {7,1}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
