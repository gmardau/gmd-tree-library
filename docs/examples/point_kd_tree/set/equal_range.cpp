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
	gmd::point_kd_tree_set<2, intpair, Comp> a{{1,2}, {3,1}, {4,0}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "equal_range (2,0): ";
	auto y = a.equal_range(intpair{2,0});
	if(y.empty()) std::cout << "no element found\n";
	else          std::cout << "element found\n";

	std::cout << "equal_range (3,1): ";
	y = a.equal_range(intpair{3,1});
	for(auto z = y.begin(); z != y.end(); ++z)
		std::cout << *z << ' ';
	std::cout << "\n";

	return 0;
}
