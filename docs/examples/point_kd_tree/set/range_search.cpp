#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<< (std::ostream& os, const intpair& i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

struct Comp {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first < i2.first : i1.second < i2.second; }
};

int main(const int, const char **)
{
	using kdtset = gmd::point_kd_tree_set<2, intpair, Comp>;
	kdtset a{{1,1}, {2,7}, {4,6}, {5,2}, {6,7}, {7,3}, {9,4}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	kdtset::range y = a.range_search(intpair{3,2}, intpair{7,6});
	std::cout << "range search (3,2)-(7,6): ";
	for(kdtset::range::iterator z = y.begin(); z != y.end(); ++z)
		std::cout << *z << ' ';
	std::cout << '\n';

	return 0;
}
