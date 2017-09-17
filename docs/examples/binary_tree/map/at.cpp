#include <iostream>

using intpair = std::pair<int, int>;
std::ostream& operator<<(std::ostream& os, const intpair& i) {
	os << i.first << ',' << i.second; return os;
}

int main(const int, const char **)
{
	gmd::binary_tree_map<gmd::tree_avl, int, int> a{{3,1}, {1,2}, {2,3}};
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "access value of key 2: " << a.at(2) << '\n';
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	std::cout << "setting value of key 3: " << (a.at(3) = 3) << '\n';
	std::cout << "a: "; for(intpair &x: a) std::cout << x << ' '; std::cout << '\n';

	try {
		std::cout << "access value of key 4: " << a.at(4) << '\n';
	} catch (std::exception &e) {
		std::cout << e.what() << '\n';
	}

	return 0;
}
