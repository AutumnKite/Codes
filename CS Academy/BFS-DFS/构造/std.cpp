#include <cstdio>
int n, a[5005], b[5005];
int m, x[100005], y[100005];
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1; i <= n; ++i) scanf("%d", b + i);
	if (n == 1) return printf("0"), 0;
	if (a[2] != b[2]) return printf("-1"), 0;
	++m, x[m] = 1, y[m] = b[2];
	for (register int i = 2; i < n; ++i) ++m, x[m] = b[i], y[m] = b[i + 1];
	for (register int i = 3; i <= n; ++i) ++m, x[m] = 1, y[m] = a[i];
	printf("%d\n", m);
	for (register int i = 1; i <= m; ++i) printf("%d %d\n", x[i], y[i]);
}
