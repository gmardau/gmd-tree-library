#include <iostream>

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 5};
	gmd::binary_tree_multiset<gmd::tree_rb, int> b{1, 3, 3, 4, 5};
	gmd::binary_tree_multiset<gmd::tree_avl, int> c{2, 3, 4, 2};

	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(int &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "c: "; for(int &x: c) std::cout << x << ' '; std::cout << '\n';
	std::cout << "a == b: " << (a == b ? "true" : "false") << '\n';
	std::cout << "b != c: " << (b != c ? "true" : "false") << '\n';
	std::cout << "a < b: " << (a < b ? "true" : "false") << '\n';
	std::cout << "b > c: " << (b > c ? "true" : "false") << '\n';
	std::cout << "a <=> c: " << a.spaceship(c) << '\n';

	return 0;
}
