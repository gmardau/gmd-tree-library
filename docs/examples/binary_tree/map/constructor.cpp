#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<< (std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	// (1) Default constructor
	gmd::binary_tree_map<gmd::tree_avl, int, int> a;
	a.insert({{1,0}, {3,0}, {5,0}});
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	// (2) Range constructor
	gmd::binary_tree_map<gmd::tree_avl, int, int> b(++a.begin(), a.end());
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	// (3) Copy constructor
	gmd::binary_tree_map<gmd::tree_avl, int, int> c(a);
	c.insert({2,0});
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';

	// (4) Move constructor
	gmd::binary_tree_map<gmd::tree_avl, int, int> d(std::move(b));
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(intpair &x: d) std::cout << x << ' '; std::cout << '\n';

	// (5) Initializer list constructor
	gmd::binary_tree_map<gmd::tree_avl, int, int> e{{4,0}, {6,0}, {5,0}};
	std::cout << "e: "; for(intpair &x: e) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
