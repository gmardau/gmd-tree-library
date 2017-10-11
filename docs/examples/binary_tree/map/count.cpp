#include <iostream>

using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	gmd::binary_tree_map<gmd::tree_avl, int, int> a{{1,0}, {3,0}, {4,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "count 1: " << a.count(1) << "\n";
	std::cout << "count 2: " << a.count(2) << "\n";

	return 0;
}
