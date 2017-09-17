#include <iostream>

int main(const int, const char **)
{
	gmd::binary_tree_set<gmd::tree_avl, int> a{1, 2, 3, 4, 5};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	a.erase(4);
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	a.erase(a.root().next(), a.end());
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	a.erase({1, 3});
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
