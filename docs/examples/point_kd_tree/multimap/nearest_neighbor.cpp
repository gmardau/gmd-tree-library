#include <iostream>
#include <cmath>

using intpair = std::pair<int, int>;
using int2pair = std::pair<intpair, int>;
std::ostream &operator<< (std::ostream &os, const int2pair &i) {
	os << '(' << i.first.first << ',' << i.first.second << ')' << ',' << i.second; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

struct Measure {
	double operator() (unsigned short d, const intpair &i1, const intpair &i2) const {
		return d == 0 ? std::abs(i1.first - i2.first) : std::abs(i1.second - i2.second); }
	double operator() (const intpair &i1, const intpair &i2) const {
		return std::sqrt(std::pow(i1.first - i2.first, 2) + std::pow(i1.second - i2.second, 2)); }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_multimap<2, intpair, int, Comp>
		a{{{1,1},0}, {{2,7},0}, {{4,6},0}, {{5,2},0}, {{2,7},1}, {{6,7},0}, {{7,3},0}, {{9,4},0}};
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	auto y = a.nearest_neighbor<Measure>(intpair{3,3});
	std::cout << "nearest neighbor (3,3): " << *y.first << " distance: " << y.second << '\n';

	y = a.nearest_neighbor(intpair{7,6}, Measure());
	std::cout << "nearest neighbor (7,6): " << *y.first << " distance: " << y.second << '\n';

	return 0;
}
