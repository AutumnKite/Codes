#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
int rnd(int a, int b){
	return rand() % (b - a + 1) + a;
}
int n, q;
int main(){
	srand(time(0));
	n = rnd(2, 1000), q = rnd(1, 1000);
	printf("%d %d\n", n, q);
	for (register int i = 1; i <= n; ++i) printf("%d ", rnd(1, 100));
	while (q--) printf("%d\n", rnd(2, n));
}