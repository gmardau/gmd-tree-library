#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<<(std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	gmd::binary_tree_multimap<gmd::tree_avl, int, int> a;
	gmd::binary_tree_multimap<gmd::tree_rb, int, int> b;

	auto y = a.insert({2,0});
	std::cout << "element: " << *y << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	a.insert({{1,0}, {2,1}, {3,0}, {4,0}});
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	a.insert({2,1});
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	b.insert(a.root(), a.cend());
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	b.insert_hint(b.end(), {5,0});
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
