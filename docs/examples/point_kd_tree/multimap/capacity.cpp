#include <iostream>

using intpair = std::pair<int, int>;
using int2pair = std::pair<intpair, int>;
std::ostream &operator<< (std::ostream &os, const int2pair &i) {
	os << '(' << i.first.first << ',' << i.first.second << ')' << ',' << i.second; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_multimap<2, intpair, int, Comp> a;

	std::cout << "empty: " << (a.empty() ? "true" : "false") << "\n";
	std::cout << "size: " << a.size() << "\n";
	a.insert({{{3,2},0}, {{1,3},0}, {{2,4},0}, {{3,2},1}});
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "empty: " << (a.empty() ? "true" : "false") << "\n";
	std::cout << "size: " << a.size() << "\n";

	std::cout << "max_size: " << a.max_size() << "\n";

	return 0;
}
