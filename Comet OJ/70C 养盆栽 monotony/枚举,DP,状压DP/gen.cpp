#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
int rnd(int a, int b){
	return rand() % (b - a + 1) + a;
}
int n, m, a[505];
int main(){
	srand(time(0));
	m = rnd(1, 10), n = rnd(1, 10);
	for (register int i = 1; i <= n * m; ++i) a[i] = i;
	std :: random_shuffle(a + 1, a + 1 + n * m);
	printf("%d %d\n", n, m);
	for (register int i = 1; i <= n * m; ++i){
		printf("%d ", a[i]);
		if (i % m == 0) putchar('\n');
	}
}