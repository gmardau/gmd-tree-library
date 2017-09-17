#include <iostream>

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 3};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "contains 3: " << (a.contains(3) ? "true" : "false") << "\n";
	std::cout << "contains 2: " << (a.contains(2) ? "true" : "false") << "\n";

	return 0;
}
