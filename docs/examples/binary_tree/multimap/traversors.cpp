#include <iostream>

using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	using btmmap = gmd::binary_tree_multimap<gmd::tree_avl, int, int>;
	btmmap a{{1,0}, {8,0}, {4,0}, {3,0}, {7,0}, {4,1}};

	std::cout << "a: ";
	for(btmmap::traversor x = a.begin(); x != a.end(); ++x)
		std::cout << *x << " ";
	std::cout << "\n";

	btmmap::traversor x = a.root();
	std::cout << "root: " << *x << "\n";
	if(x.right()())
		std::cout << "right: " << *x.right() << "\n";

	std::cout << "reverse from root: ";
	for(btmmap::const_reverse_traversor y = x.reverse(); y != a.crend(); ++y)
		std::cout << *y << " ";
	std::cout << "\n";

	return 0;
}
