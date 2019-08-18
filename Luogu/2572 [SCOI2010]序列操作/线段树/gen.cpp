#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
int rnd(int a, int b){
	return ((rand() << 15) + rand()) % (b - a + 1) + a;
}
int main(){
	freopen("test.in", "w", stdout);
	srand(GetTickCount());
	int n = rnd(1, 50), m = rnd(1, 100);
	printf("%d %d\n", n, m);
	for (register int i = 1; i <= n; ++i) printf("%d ", rnd(0, 1)); putchar('\n');
	for (register int i = 1; i <= m; ++i){
		int opt = rnd(0, 4), l = rnd(0, n - 1), r = rnd(0, n - 1);
		if (l > r) std :: swap(l, r);
		printf("%d %d %d\n", opt, l, r);
	}
}
