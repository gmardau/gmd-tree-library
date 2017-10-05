#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<< (std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	gmd::binary_tree_map<gmd::tree_avl, int, int> a{{1,0}, {3,0}, {4,0}};
	gmd::binary_tree_map<gmd::tree_rb, int, int> b{{1,0}, {3,0}, {4,0}, {5,0}};
	gmd::binary_tree_map<gmd::tree_avl, int, int> c{{1,0}, {3,0}, {4,1}};

	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(intpair &x: c) std::cout << x << ' '; std::cout << '\n';
	std::cout << "a == b: " << (a == b ? "true" : "false") << '\n';
	std::cout << "b != c: " << (b != c ? "true" : "false") << '\n';
	std::cout << "a < b: " << (a < b ? "true" : "false") << '\n';
	std::cout << "b > c: " << (b > c ? "true" : "false") << '\n';
	std::cout << "a <=> c: " << a.spaceship(c) << '\n';

	return 0;
}
