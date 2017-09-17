#include <iostream>

int main(const int, const char **)
{
	using btmset = gmd::binary_tree_multiset<gmd::tree_avl, int>;
	btmset a{1, 8, 4, 3, 7, 4};

	std::cout << "a: ";
	for(btmset::traversor x = a.begin(); x != a.end(); ++x)
		std::cout << *x << " ";
	std::cout << "\n";

	btmset::traversor x = a.root();
	std::cout << "root: " << *x << "\n";
	if(x.right()())
		std::cout << "right: " << *x.right() << "\n";

	std::cout << "reverse from root: ";
	for(btmset::const_reverse_traversor y = x.reverse(); y != a.crend(); ++y)
		std::cout << *y << " ";
	std::cout << "\n";

	return 0;
}
