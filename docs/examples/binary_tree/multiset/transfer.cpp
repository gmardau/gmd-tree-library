#include <iostream>

struct Info {
	Info (int a, int b) : v{a, b} {}
	int v[2];
	bool operator< (const Info &i) const { return v[0] < i.v[0]; }
};

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, Info> a{Info(1,0), Info(2,0), Info(3,0)}, b{Info(2,1)};
	gmd::binary_tree_multiset<gmd::tree_rb, Info> c;
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	b.transfer(a, a.root());
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	c.transfer(a, a.begin());
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';
	std::cout << "c: "; for(Info &x: c) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	return 0;
}
