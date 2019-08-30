#include <cstdio>
int n, x, m;
int main(){
	scanf("%d", &n);
	for (register int i = 1; i < n; ++i)
		scanf("%d", &x), m += x == 1, scanf("%d", &x);
	printf(m == 1 || (n & 1) == 0 ? "A\n" : "B\n");
}
