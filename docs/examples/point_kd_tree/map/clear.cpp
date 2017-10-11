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
	gmd::point_kd_tree_map<2, intpair, int, Comp> a{{{4,1},0}, {{2,3},0}, {{3,5},0}, {{1,4},0}};
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	a.clear();
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';
	std::cout << "size: " << a.size() << "\n";

	return 0;
}
