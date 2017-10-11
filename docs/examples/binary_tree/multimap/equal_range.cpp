#include <iostream>

using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	gmd::binary_tree_multimap<gmd::tree_avl, int, int> a{{1,0}, {3,0}, {4,0}, {3,1}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "equal_range 2: ";
	auto y = a.equal_range(2);
	if(y.first == y.second) std::cout << "no elements found\n";
	else                    std::cout << "element found\n";

	std::cout << "equal_range 3: ";
	y = a.equal_range(3);
	for(auto z = y.first; z != y.second; ++z)
		std::cout << *z << ' ';
	std::cout << "\n";

	return 0;
}
