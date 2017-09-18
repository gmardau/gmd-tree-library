#include <stdio.h>
#include <stdlib.h>

struct Point {
	int v[2] = {rand()%100, rand()%100};
	bool operator== (const Point &p) const {
		return v[0] == p.v[0] && v[1] == p.v[1];
	}
};

struct Comp {
	bool operator() (size_t d, const Point &p1, const Point &p2) {
		return p1.v[d] < p2.v[d];
	}
};

int main (const int, const char **)
{
	gmd::point_kd_tree_set<2, Point, Comp> a;
	a.insert(Point());


	return 0;
}
