#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<<(std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	gmd::binary_tree_map<gmd::tree_avl, int, int> a;

	auto y = a.emplace(2, 0);
	std::cout << "emplaced: " << (y.second ? "true" : "false") << "\n";
	std::cout << "element: " << *y.first << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	y = a.emplace<true>(2, 1);
	std::cout << "emplaced: " << (y.second ? "true" : "false") << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	a.emplace_hint(a.begin(), 1, 0);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	a.try_emplace(1, 1);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	a.try_emplace_hint(a.end(), 3, 0);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
