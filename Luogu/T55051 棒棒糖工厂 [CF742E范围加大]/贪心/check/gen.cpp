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
	int n = rnd(1, 5);
	printf("%d %d\n", n, rnd(1, 5));
	for (register int i = 1; i <= n; ++i) printf("%d ", rnd(1, 5)); putchar('\n');
	for (register int i = 1; i <= n; ++i) printf("%d ", rnd(1, 5)); putchar('\n');
}