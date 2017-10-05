#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<< (std::ostream& os, const intpair& i) {
	os << '(' << i.first << ',' << i.second << ')'; return os; }

using intdoublepair = std::pair<intpair, int>;
struct Comp {
	bool operator() (unsigned short d, const intdoublepair &i1, const intdoublepair &i2) {
		return d == 0 ? i1.first.first < i2.first.first : i1.first.second < i2.first.second; }
};
struct Eq {
	bool operator() (const intdoublepair &i1, const intdoublepair &i2) {
		return i1.first.first == i2.first.first && i1.first.second == i2.first.second; }
};

struct Comp2 {
	bool operator() (unsigned short d, const intpair &i1, const intpair &i2) {
		return d == 0 ? i1.first > i2.first : i1.second > i2.second; }
};

int main(const int, const char **)
{
	gmd::point_kd_tree_set<2, intdoublepair, Comp, false, Eq> a{{{1,3},0}, {{3,2},0}, {{4,2},0}, {{5,1},0}};
	gmd::point_kd_tree_multimap<2, intpair, int, Comp2, true> b{{{2,6},0}, {{2,6},1}, {{3,1},0}};
	std::cout << "a: "; for(intdoublepair &x: a) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';
	std::cout << "b: "; for(intdoublepair &x: b) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';

	a.swap(b);
	std::cout << "a: "; for(intdoublepair &x: a) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';
	std::cout << "b: "; for(intdoublepair &x: b) std::cout << x.first << ',' << x.second << ' '; std::cout << '\n';

	return 0;
}
