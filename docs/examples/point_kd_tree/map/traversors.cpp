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
	using kdtmap = gmd::point_kd_tree_map<2, intpair, int, Comp>;
	kdtmap a{{{1,6},0}, {{8,5},0}, {{4,2},0}, {{3,2},0}, {{7,3},0}};

	std::cout << "a: ";
	for(kdtmap::traversor x = a.begin(); x != a.end(); ++x)
		std::cout << *x << " ";
	std::cout << "\n";

	kdtmap::traversor x = a.root();
	std::cout << "root: " << *x << "\n";
	if(x.greater()())
		std::cout << "greater: " << *x.greater() << "\n";

	return 0;
}
