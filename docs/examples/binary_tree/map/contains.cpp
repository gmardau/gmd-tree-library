#include <iostream>

using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	gmd::binary_tree_map<gmd::tree_avl, int, int> a{{1,0}, {3,0}, {4,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "contains 3: " << (a.contains(3) ? "true" : "false") << "\n";
	std::cout << "contains 2: " << (a.contains(2) ? "true" : "false") << "\n";

	return 0;
}
