#include <iostream>

struct Info {
	Info (int a, int b) : v{a, b} {}
	int v[2];
	bool operator< (const Info &i) const { return v[0] < i.v[0]; }
};

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, Info> a;

	auto y = a.emplace(2, 0);
	std::cout << "element: " << (*y).v[0] << ',' << y->v[1] << "\n";
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	a.emplace(2, 1);
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	a.emplace_hint(a.begin(), 1, 0);
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	return 0;
}
