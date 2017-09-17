#include <iostream>

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 1};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "count 1: " << a.count(1) << "\n";
	std::cout << "count 2: " << a.count(2) << "\n";

	return 0;
}
