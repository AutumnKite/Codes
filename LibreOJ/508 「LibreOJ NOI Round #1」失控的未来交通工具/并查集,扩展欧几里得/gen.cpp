#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
int rnd(int a, int b){
	return rand() % (b - a + 1) + a;
}
int main(){
	srand(time(0));
	int n = rnd(2, 500), m = rnd(2, 500), q = rnd(1, 1000);
	printf("%d %d %d\n", n, m, q);
	for (register int i = 1; i <= q; ++i){
		int op = rnd(1, 2), u = rnd(1, n), v = rnd(1, n);
		while (op == 2 && u == v) v = rnd(1, n);
		if (op == 1) printf("1 %d %d %d\n", u, v, rnd(1, m));
		else printf("2 %d %d %d %d %d\n", u, v, rnd(0, m - 1), rnd(0, m - 1), rnd(1, 10000));
	}
}