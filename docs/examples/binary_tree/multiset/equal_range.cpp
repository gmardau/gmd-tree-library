#include <iostream>

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 3};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

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
