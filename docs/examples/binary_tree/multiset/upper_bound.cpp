#include <iostream>

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 3};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "upper_bound 2: ";
	auto y = a.upper_bound(2);
	if(y != a.end()) std::cout << *y;
	std::cout << "\n";

	return 0;
}
