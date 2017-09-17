#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<<(std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	using btmap = gmd::binary_tree_map<gmd::tree_avl, int, int>;
	btmap a{{1,0}, {8,0}, {4,0}, {3,0}, {7,0}};

	std::cout << "a: ";
	for(btmap::traversor x = a.begin(); x != a.end(); ++x)
		std::cout << *x << " ";
	std::cout << "\n";

	btmap::traversor x = a.root();
	std::cout << "root: " << *x << "\n";
	if(x.right()())
		std::cout << "right: " << *x.right() << "\n";

	std::cout << "reverse from root: ";
	for(btmap::const_reverse_traversor y = x.reverse(); y != a.crend(); ++y)
		std::cout << *y << " ";
	std::cout << "\n";

	return 0;
}
