#include <stdio.h>
#include <stdlib.h>

int main (const int, const char **)
{
	gmd::binary_tree_multiset<gmd::tree_scapegoat, int> a;

	for(int i = 0; i < 20; ++i)
		a.insert(rand()%50);
	a.print<true>([](const int &x) { printf("%d", x); });

	for(int i = 0; i < 50; ++i)
		a.erase(rand()%100);
	a.print([](const int &x) { printf("%d", x); });

	return 0;
}
