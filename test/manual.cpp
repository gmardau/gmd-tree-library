#include <stdio.h>
#include <stdlib.h>

struct Point {
	float v[2];
	Point (float x = rand()%10, float y = rand()%10) : v{x,y} {}
	bool operator== (const Point &p) const {
		return v[0] == p.v[0] && v[1] == p.v[1];
	}
};

struct Comp {
	bool operator() (size_t d, const Point &p1, const Point &p2) {
		return p1.v[d] < p2.v[d];
	}
};

struct Divider {
	Point operator() () { return Point(5, 5); }
	Point operator() (ushort depth, const Point &p, bool half) {
		float delta = 10.0 / pow(2, (depth-1)/2 + 2);
		if(!half) delta *= -1;
		if(depth % 2 == 0) return Point(p.v[0], p.v[1] + delta);
		else               return Point(p.v[0] + delta, p.v[1]);
	}
};

int main (const int, const char **)
{
	gmd::region_kd_tree_set<2, Point, Divider, Comp> a;
	for(int i = 0; i < 10; ++i)
		a.emplace();
	a.print<true>([](const Point &p){printf("%f %f", p.v[0], p.v[1]);});

	a.erase(a.begin());
	a.print<true>([](const Point &p){printf("%f %f", p.v[0], p.v[1]);});

	a.erase(a.begin());
	a.print<true>([](const Point &p){printf("%f %f", p.v[0], p.v[1]);});
	return 0;
}

