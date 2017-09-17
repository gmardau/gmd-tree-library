#include <iostream>

int main(const int, const char **)
{
	// (1) Copy assignment
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{3, 5, 2, 5};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
	gmd::binary_tree_multiset<gmd::tree_avl, int> b; b = a;
	std::cout << "b: "; for(int &x: b) std::cout << x << ' '; std::cout << '\n';

	// (2) Move assignment
	gmd::binary_tree_set<gmd::tree_avl, int> c{1, 6};
	std::cout << "c: "; for(int &x: c) std::cout << x << ' '; std::cout << '\n';
	gmd::binary_tree_multiset<gmd::tree_rb, int> d; d = std::move(c);
	std::cout << "c: "; for(int &x: c) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(int &x: d) std::cout << x << ' '; std::cout << '\n';

	// (3) Initializer list assignment
	a = {7, 4, 7};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
