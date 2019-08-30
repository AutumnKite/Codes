#include <cstdio>
#include <cstdlib>
#include <windows.h>
int rnd(){
	return (rand() << 15) + rand();
}
int rnd(int a, int b){
	return rnd() % (b - a + 1) + a;
}
int main(){
	srand(GetTickCount());
	freopen("sort.in", "w", stdout);
	int n = 10000;
	printf("%d\n", n);
	for (register int i = 1; i <= n; ++i) printf("%d ", rnd(0, 1));
}