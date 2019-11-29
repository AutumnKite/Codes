#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>
int rnd(int a, int b){
	return rand() % (b - a + 1) + a;
}
int main(){
	srand(time(0));
	int n = rnd(1, 20), m = rnd(0, std :: min(20, n * (n - 1) >> 1));
	printf("%d %d\n", n, m);
	std :: set< std :: pair<int, int> > S;
	for (register int i = 1; i <= n; ++i) S.insert({i, i});
	for (register int i = 1; i <= m; ++i){
		int x = rnd(1, n), y = rnd(1, n);
		while (S.count({x, y})) x = rnd(1, n), y = rnd(1, n);
		printf("%d %d\n", x, y), S.insert({x, y}), S.insert({y, x});
	}
}
