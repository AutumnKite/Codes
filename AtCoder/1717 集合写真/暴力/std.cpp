#include <cstdio>
#include <algorithm>
int n, a[55], m;
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	scanf("%d", &m);
	for (register int i = 1; i <= n; ++i)
		if (a[i] > m) return printf("%d\n", i), 0;
	printf("%d\n", n + 1);
}
