#include <iostream>

using intpair = std::pair<int, int>;
using doublepair = std::pair<double, double>;
std::ostream& operator<< (std::ostream& os, const intpair& i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

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
	using kdtset = gmd::point_kd_tree_set<2, intpair, Comp>;
	kdtset a{{1,2}, {3,1}, {4,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "find (1.0,3.0): ";
	kdtset::traversor y = a.find(doublepair{1.0,3.0});
	if(y != a.end()) std::cout << "true - " << *y << "\n";
	else             std::cout << "false\n";

	std::cout << "find (4.0,0.0): ";
	kdtset::const_traversor z = a.find(doublepair{4.0,0.0});
	if(z != a.cend()) std::cout << "true - " << *z << "\n";
	else              std::cout << "false\n";

	return 0;
}
