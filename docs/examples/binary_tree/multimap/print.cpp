#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<<(std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

struct Print {
	void operator() (const intpair &i) const {
		std::cout << i ;
	}
};

int main(const int, const char **)
{
	gmd::binary_tree_multimap<gmd::tree_avl, int, int> a{{1,0}, {3,0}, {4,0}, {6,0}, {4,1}, {1,1}};
	gmd::binary_tree_multimap<gmd::tree_rb, int, int> b{{2,0}, {3,0}, {5,0}, {7,0}, {5,1}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(intpair &x: b) std::cout << x << ' '; std::cout << '\n';

	std::cout << "\n"; a.print<true>(Print());
	std::cout << "\n"; b.print<true, Print>();
	std::cout << "\n"; b.print(b.root().right(), [](const intpair &i){ std::cout << i; });

	return 0;
}
