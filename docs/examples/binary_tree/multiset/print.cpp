#include <iostream>

struct Print {
	void operator() (const int &i) const {
		std::cout << i ;
	}
};

int main(const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_avl, int> a{1, 3, 4, 6, 4, 1};
	gmd::binary_tree_multiset<gmd::tree_rb, int> b{2, 3, 5, 7, 5};
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "b: "; for(int &x: b) std::cout << x << ' '; std::cout << '\n';

	std::cout << "\n"; a.print<true>(Print());
	std::cout << "\n"; b.print<true, Print>();
	std::cout << "\n"; b.print(b.root().right(), [](const int &i){ std::cout << i; });

	return 0;
}
