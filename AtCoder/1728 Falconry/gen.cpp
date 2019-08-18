#include <cstdio>
#include <cstdlib>
#include <windows.h>
int rnd(int a, int b){
	return rand() % (b - a + 1) + a;
}
int x[25], y[25];
bool has(int X, int Y, int p){
	for (register int i = 1; i <= p; ++i)
		if (x[i] == X && y[i] == Y) return 1;
	return 0;
}
#define N 18
#define L -9999
#define R 9999
int main(){
	srand(GetTickCount());
	int n = rnd(1, N);
	printf("%d\n", n), n += 3;
	for (register int i = 1; i <= n; ++i){
		x[i] = rnd(L, R), y[i] = rnd(L, R);
		while (has(x[i], y[i], i - 1)) x[i] = rnd(L, R), y[i] = rnd(L, R);
		printf("%d %d\n", x[i], y[i]);
	}
}
