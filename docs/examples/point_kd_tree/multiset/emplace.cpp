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

	auto y = a.emplace(2, 0);
	std::cout << "element: " << *y << "\n";
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	y = a.emplace(2, 0);
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
