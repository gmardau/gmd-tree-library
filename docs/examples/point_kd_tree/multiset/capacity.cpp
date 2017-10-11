#include <iostream>

using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_multiset<2, intpair, Comp> a;

	std::cout << "empty: " << (a.empty() ? "true" : "false") << "\n";
	std::cout << "size: " << a.size() << "\n";
	a.insert({{3,2}, {1,3}, {2,4}, {3,2}});
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "empty: " << (a.empty() ? "true" : "false") << "\n";
	std::cout << "size: " << a.size() << "\n";

	std::cout << "max_size: " << a.max_size() << "\n";

	return 0;
}
