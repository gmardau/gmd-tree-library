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
	gmd::point_kd_tree_map<2, intpair, int, Comp> a{{{2,1},0}};
	a.insert({{{3,0},0}, {{5,4},0}, {{6,3},0}, {{7,5},0}});
	a.print([](const int2pair &i){ std::cout << i; });

	a.balance(a.root().greater().greater());
	std::cout << "\n"; a.print([](const int2pair &i){ std::cout << i; });

	a.balance();
	std::cout << "\n"; a.print([](const int2pair &i){ std::cout << i; });

	return 0;
}
