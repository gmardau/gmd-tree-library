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
	using kdtmset = gmd::point_kd_tree_multiset<2, intpair, Comp>;
	kdtmset a{{1,6}, {8,5}, {4,2}, {3,2}, {7,3}, {4,2}};

	std::cout << "a: ";
	for(kdtmset::traversor x = a.begin(); x != a.end(); ++x)
		std::cout << *x << " ";
	std::cout << "\n";

	kdtmset::traversor x = a.root();
	std::cout << "root: " << *x << "\n";
	if(x.greater()())
		std::cout << "greater: " << *x.greater() << "\n";

	return 0;
}
