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
	gmd::point_kd_tree_map<2, intpair, int, Comp> a{{{3,1},1}, {{1,2},2}, {{2,3},3}};
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "access value of key (2,3): " << a.at(intpair{2,3}) << '\n';
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "setting value of key (3,1): " << (a.at(intpair{3,1}) = 3) << '\n';
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	try {
		std::cout << "access value of key (4,2): " << a.at(intpair{4,2}) << '\n';
	} catch (std::exception &e) {
		std::cout << e.what() << '\n';
	}

	return 0;
}
