#include <iostream>

using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	gmd::binary_tree_map<gmd::tree_avl, int, int> a{{1,0}, {3,0}, {4,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "lower_bound 2: ";
	auto y = a.lower_bound(2);
	if(y != a.end()) std::cout << *y;
	std::cout << "\n";

	a.insert({2,0});
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "lower_bound 2: ";
	y = a.lower_bound(2);
	if(y != a.end()) std::cout << *y;
	std::cout << "\n";

	return 0;
}
