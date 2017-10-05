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
	gmd::point_kd_tree_multiset<2, intpair, Comp> a{{1,1}, {1,1}, {2,4}, {3,2}};
	gmd::point_kd_tree_set<2, intpair, Comp> b{{2,4}};
	gmd::point_kd_tree_set<2, intpair, Comp> c{{2,4}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';

	b.merge(a);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	c.merge<true>(a);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
