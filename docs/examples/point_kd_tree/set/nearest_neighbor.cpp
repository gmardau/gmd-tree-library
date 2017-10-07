#include <iostream>
#include <cmath>

using intpair = std::pair<int, int>;
std::ostream &operator<< (std::ostream &os, const intpair &i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

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
	gmd::point_kd_tree_set<2, intpair, Comp> a{{1,1}, {2,7}, {4,6}, {5,2}, {6,7}, {7,3}, {9,4}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	auto y = a.nearest_neighbor<Measure>(intpair{3,3});
	std::cout << "nearest neighbor (3,3): " << *y.first << " distance: " << y.second << '\n';

	y = a.nearest_neighbor(intpair{7,6}, Measure());
	std::cout << "nearest neighbor (7,6): " << *y.first << " distance: " << y.second << '\n';

	return 0;
}
