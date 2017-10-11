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
	gmd::point_kd_tree_map<2, intpair, int, Comp> a, b;

	auto y = a.insert({{2,1},0});
	std::cout << "inserted: " << (y.second ? "true" : "false") << "\n";
	std::cout << "element: " << *y.first << "\n";
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	size_t z = a.insert({{{1,4},0}, {{2,1},1}, {{3,0},0}, {{4,2},0}});
	std::cout << "# inserted: " << z << "\n";
	std::cout << "a: "; for(int2pair &x: a) std::cout << x << ' '; std::cout << '\n';

	b.insert(a.root(), a.cend());
	std::cout << "b: "; for(int2pair &x: b) std::cout << x << ' '; std::cout << '\n';

	return 0;
}
