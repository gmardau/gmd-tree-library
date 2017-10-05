#include <iostream>

struct Comp {
	using is_transparent = void;
	bool operator() (const int &i1, const int &i2) const { return i1 < i2; }
	bool operator() (const double &d, const int &i) const { return d < i; }
	bool operator() (const int &i, const double &d) const { return i < d; }
};

int main(const int, const char **)
{
	using btset = gmd::binary_tree_set<gmd::tree_avl, int, false, Comp>;
	btset a{1, 3, 4};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "find 2.0: ";
	btset::reverse_traversor y = a.find(2.0);
	if(y != a.rend()) std::cout << "true - " << *y << "\n";
	else              std::cout << "false\n";

	std::cout << "find 4: ";
	btset::const_traversor z = a.find_short(4);
	if(z != a.cend()) std::cout << "true - " << *z << "\n";
	else              std::cout << "false\n";

	return 0;
}
