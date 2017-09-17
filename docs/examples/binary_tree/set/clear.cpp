#include <iostream>

int main(const int, const char **)
{
	gmd::binary_tree_set<gmd::tree_avl, int> a{4, 2, 3, 1};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	a.clear();
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "size: " << a.size() << "\n";

	return 0;
}
