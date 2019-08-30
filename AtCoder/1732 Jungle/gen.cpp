#include <cstdio>
#include <cstdlib>
#include <windows.h>
int rnd(int a, int b){
	return rand() % (b - a + 1) + a;
}
int main(){
	srand(GetTickCount());
	int n = rnd(2, 10), m = rnd(1, n >> 1), k = rnd(1, n >> 1);
	printf("%d %d %d\n", n, m, k);
	for (register int i = 1; i <= n; ++i) printf("%d\n", rnd(1, n));
	// getchar(), getchar();
}