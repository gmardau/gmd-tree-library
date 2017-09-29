#include <iostream>

struct Info {
	Info (int a, int b) : v{a, b} {}
	int v[2];
	bool operator< (const Info &i) const { return v[0] < i.v[0]; }
};

struct Comp {
	using is_transparent = void;
	bool operator() (const Info &i1, const Info &i2) const { return i1.v[0] < i2.v[0]; }
	bool operator() (const double &d, const Info &i) const { return d < i.v[0]; }
	bool operator() (const Info &i, const double &d) const { return i.v[0] < d; }
};

int main(const int, const char **)
{
	using btmset = gmd::binary_tree_multiset<gmd::tree_avl, Info, false, Comp>;
	btmset a{Info(1,0), Info(3,0), Info(4,0), Info(4,1)};
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	std::cout << "find 2.0: ";
	btmset::reverse_traversor y = a.find(2.0);
	if(y != a.rend()) std::cout << "true - " << (*y).v[0] << ',' << y->v[0] << "\n";
	else              std::cout << "false\n";

	std::cout << "find 4.0: ";
	btmset::const_traversor z = a.find_short(4.0);
	if(z != a.rend()) std::cout << "true - " << z->v[0] << ',' << z->v[1] << "\n";
	else              std::cout << "false\n";

	return 0;
}
