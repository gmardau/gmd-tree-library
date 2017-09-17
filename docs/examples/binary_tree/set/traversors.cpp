#include <iostream>

int main(const int, const char **)
{
	using btset = gmd::binary_tree_set<gmd::tree_avl, int>;
	btset a{1, 8, 4, 3, 7};

	std::cout << "a: ";
	for(btset::traversor x = a.begin(); x != a.end(); ++x)
		std::cout << *x << " ";
	std::cout << "\n";

	btset::traversor x = a.root();
	std::cout << "root: " << *x << "\n";
	if(x.right()())
		std::cout << "right: " << *x.right() << "\n";

	std::cout << "reverse from root: ";
	for(btset::const_reverse_traversor y = x.reverse(); y != a.crend(); ++y)
		std::cout << *y << " ";
	std::cout << "\n";

	return 0;
}
