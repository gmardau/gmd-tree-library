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
	gmd::point_kd_tree_multiset<2, intpair, Comp> a{{2,1}};
	a.insert({{3,0}, {5,4}, {5,4}, {6,3}, {7,5}});
	a.print([](const intpair &i){ std::cout << i; });

	a.balance(a.root().greater().greater());
	std::cout << "\n"; a.print([](const intpair &i){ std::cout << i; });

	a.balance();
	std::cout << "\n"; a.print([](const intpair &i){ std::cout << i; });

	return 0;
}
