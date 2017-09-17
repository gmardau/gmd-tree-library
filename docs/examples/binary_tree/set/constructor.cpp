#include <iostream>

int main(const int, const char **)
{
	// (1) Default constructor
	gmd::binary_tree_set<gmd::tree_avl, int> a;
	a.insert({1, 3, 5});
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	// (2) Range constructor
	gmd::binary_tree_set<gmd::tree_avl, int> b(++a.begin(), a.end());
	std::cout << "b: "; for(int &x: b) std::cout << x << ' '; std::cout << '\n';

	// (3) Copy constructor
	gmd::binary_tree_set<gmd::tree_avl, int> c(a);
	c.insert(2);
	std::cout << "c: "; for(int &x: c) std::cout << x << ' '; std::cout << '\n';

	// (4) Move constructor
	gmd::binary_tree_set<gmd::tree_avl, int> d(std::move(b));
	std::cout << "b: "; for(int &x: b) std::cout << x << ' '; std::cout << '\n';
	std::cout << "d: "; for(int &x: d) std::cout << x << ' '; std::cout << '\n';

	// (5) Initializer list constructor
	gmd::binary_tree_set<gmd::tree_avl, int> e{4, 6, 5};
	std::cout << "e: "; for(int &x: e) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
