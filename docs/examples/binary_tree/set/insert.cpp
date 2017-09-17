#include <iostream>

struct Info {
	Info (int a, int b) : v{a, b} {}
	int v[2];
	bool operator< (const Info &i) const { return v[0] < i.v[0]; }
};

int main(const int, const char **)
{
	gmd::binary_tree_set<gmd::tree_avl, Info> a;
	gmd::binary_tree_set<gmd::tree_rb, Info> b;

	auto y = a.insert(Info(2,0));
	std::cout << "inserted: " << (y.second ? "true" : "false") << "\n";
	std::cout << "element: " << (*y.first).v[0] << ',' << y.first->v[1] << "\n";
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	size_t z = a.insert({Info(1,0), Info(2,1), Info(3,0), Info(4,0)});
	std::cout << "# inserted: " << z << "\n";
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	y = a.insert<true>(Info(2,1));
	std::cout << "inserted: " << (y.second ? "true" : "false") << "\n";
	std::cout << "a: "; for(Info &x: a) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	b.insert(a.root(), a.cend());
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	b.insert_hint(b.end(), Info(5,0));
	std::cout << "b: "; for(Info &x: b) std::cout << x.v[0] << ',' << x.v[1] << ' '; std::cout << '\n';

	return 0;
}
