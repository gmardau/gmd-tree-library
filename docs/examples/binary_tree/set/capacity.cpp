#include <iostream>

int main(const int, const char **)
{
	gmd::binary_tree_set<gmd::tree_avl, int> a;

	std::cout << "empty: " << (a.empty() ? "true" : "false") << "\n";
	std::cout << "size: " << a.size() << "\n";
	a.insert({3, 1, 2});
	std::cout << "a: "; for(int &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "empty: " << (a.empty() ? "true" : "false") << "\n";
	std::cout << "size: " << a.size() << "\n";

	std::cout << "max_size: " << a.max_size() << "\n";

	return 0;
}
