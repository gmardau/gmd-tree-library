#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<< (std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	gmd::binary_tree_map<gmd::tree_avl, int, int> a;
	gmd::binary_tree_map<gmd::tree_rb, int, int> b;

	auto y = a.insert({2,0});
	std::cout << "inserted: " << (y.second ? "true" : "false") << "\n";
	std::cout << "element: " << *y.first << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	size_t z = a.insert({{1,0}, {2,1}, {3,0}, {4,0}});
	std::cout << "# inserted: " << z << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	y = a.insert<true>({2,1});
	std::cout << "inserted: " << (y.second ? "true" : "false") << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	b.insert(a.root(), a.cend());
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	b.insert_hint(b.end(), {5,0});
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
