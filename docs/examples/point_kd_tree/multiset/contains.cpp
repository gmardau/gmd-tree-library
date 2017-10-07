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
	gmd::point_kd_tree_multiset<2, intpair, Comp> a{{1,2}, {3,1}, {4,0}, {3,1}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "contains (3,1): " << (a.contains(intpair{3,1}) ? "true" : "false") << "\n";
	std::cout << "contains (3,2): " << (a.contains(intpair{3,2}) ? "true" : "false") << "\n";

	return 0;
}
