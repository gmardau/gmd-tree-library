#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<< (std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	gmd::binary_tree_map<gmd::tree_avl, int, int> a{{1,0}, {2,0}, {3,0}};
	gmd::binary_tree_multimap<gmd::tree_avl, int, int> b{{2,1}};
	gmd::binary_tree_multimap<gmd::tree_rb, int, int> c{{2,2}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';

	b.merge(a);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	c.merge(b);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
