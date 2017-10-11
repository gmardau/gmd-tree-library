#include <iostream>

using intpair = std::pair<int, int>;
using int2pair = std::pair<intpair, int>;
using doublepair = std::pair<double, double>;
std::ostream &operator<< (std::ostream &os, const int2pair &i) {
	os << '(' << i.first.first << ',' << i.first.second << ')' << ',' << i.second; return os; }

struct Comp {
	using is_transparent = void;
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
	bool operator() (unsigned short d, const doublepair &d1, const intpair &i2) {
		return d == 0 ? d1.first < i2.first : d1.second < i2.second; }
	bool operator() (unsigned short d, const intpair &i1, const doublepair &d2) {
		return d == 0 ? i1.first < d2.first : i1.second < d2.second; }
};

int main(const int, const char **)
{
	using kdtmmap = gmd::point_kd_tree_multimap<2, intpair, int, Comp>;
	kdtmmap a{{{1,2},0}, {{3,1},0}, {{4,0},0}, {{4,0},1}};
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "find (1.0,3.0): ";
	kdtmmap::traversor y = a.find(doublepair{1.0,3.0});
	if(y != a.end()) std::cout << "true - " << *y << "\n";
	else             std::cout << "false\n";

	std::cout << "find (4.0,0.0): ";
	kdtmmap::const_traversor z = a.find(doublepair{4.0,0.0});
	if(z != a.cend()) std::cout << "true - " << *z << "\n";
	else              std::cout << "false\n";

	return 0;
}
