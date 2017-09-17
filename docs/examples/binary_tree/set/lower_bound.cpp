#include <iostream>

int main(const int, const char **)
{
	gmd::binary_tree_set<gmd::tree_avl, int> a{1, 3, 4};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "lower_bound 2: ";
	auto y = a.lower_bound(2);
	if(y != a.end()) std::cout << *y;
	std::cout << "\n";

	a.insert(2);
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "lower_bound 2: ";
	y = a.lower_bound(2);
	if(y != a.end()) std::cout << *y;
	std::cout << "\n";

	return 0;
}
