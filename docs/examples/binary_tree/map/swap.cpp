#include <iostream>

using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << i.first << ',' << i.second; return os;
}

struct Comp {
	bool operator() (const intpair &a, const intpair &b) const {
		return a.first > b.first; }
};

int main(const int, const char **)
{
	gmd::binary_tree_map<gmd::tree_avl, int, int, false, std::less<int>> a{{1,0}, {3,0}, {4,0}, {5,0}};
	gmd::binary_tree_multiset<gmd::tree_rb, intpair, true, Comp> b{{2,0}, {2,1}, {3,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	a.swap(b);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
