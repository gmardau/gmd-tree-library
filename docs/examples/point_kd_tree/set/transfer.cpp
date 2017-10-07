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
	gmd::point_kd_tree_set<2, intpair, Comp> a{{1,0}, {2,1}, {3,0}}, b{{2,1}};
	gmd::point_kd_tree_set<2, intpair, Comp> c;
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	auto y = b.transfer<true>(a, a.root());
	std::cout << "transferred: " << (y.second ? "true" : "false") << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	c.transfer(a, a.begin());
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
