#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<<(std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

struct Comp {
	using is_transparent = void;
	bool operator() (const int &i1, const int &i2) const { return i1 < i2; }
	bool operator() (const double &d, const int &i) const { return d < i; }
	bool operator() (const int &i, const double &d) const { return i < d; }
};

int main(const int, const char **)
{
	using btmmap = gmd::binary_tree_multimap<gmd::tree_avl, int, int, false, Comp>;
	btmmap a{{1,0}, {3,0}, {4,0}, {4,1}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "find 2.0: ";
	btmmap::reverse_traversor y = a.find(2.0);
	if(y != a.rend()) std::cout << "true - " << *y << "\n";
	else              std::cout << "false\n";

	std::cout << "find 4: ";
	btmmap::const_traversor z = a.find_short(4);
	if(z != a.rend()) std::cout << "true - " << *z << "\n";
	else              std::cout << "false\n";

	return 0;
}
