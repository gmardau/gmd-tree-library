#include <iostream>

using intpair = std::pair<int, int>;

struct Comp {
	bool operator() (const intpair &a, const intpair &b) const {
		return a.first < b.first; }
};

int main(const int, const char **)
{
	gmd::binary_tree_set<gmd::tree_avl, intpair, false, Comp> a{{1,0}, {3,0}, {4,0}, {5,0}};
	gmd::binary_tree_multimap<gmd::tree_rb, int, int, true, std::greater<int>> b{{2,0}, {2,1}, {3,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';

	a.swap(b);
	std::cout << "a: "; for(intpair &x: a) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';

	return 0;
}
