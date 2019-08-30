#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
int rnd(int a, int b){
	return rand() % (b - a + 1) + a;
}
int main(){
	srand(GetTickCount());
	int n = rnd(200, 800);
	printf("%d\n", n);
	for (register int i = 1; i < n; ++i)
		printf("%d %d\n", rnd(1, i), i + 1);
}