#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<< (std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	// (1) Copy assignment
	gmd::binary_tree_map<gmd::tree_avl, int, int> a{{3,0}, {5,0}, {2,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	gmd::binary_tree_map<gmd::tree_avl, int, int> b; b = a;
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	// (2) Move assignment
	gmd::binary_tree_multimap<gmd::tree_avl, int, int> c{{1,0}, {6,0}, {1, 1}};
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';
	gmd::binary_tree_map<gmd::tree_rb, int, int> d; d = std::move(c);
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(intpair &x: d) std::cout << x << ' '; std::cout << '\n';

	// (3) Initializer list assignment
	a = {{7,0}, {4,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
