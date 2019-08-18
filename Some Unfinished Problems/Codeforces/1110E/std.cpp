#include <cstdio>
#include <cstring>
#include <algorithm>
int n, a[100005], b[100005], c[100005];
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1; i <= n; ++i) b[i] = a[i] - a[i - 1];
	std :: sort(b + 1, b + 1 + n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1; i <= n; ++i) c[i] = a[i] - a[i - 1];
	std :: sort(c + 1, c + 1 + n);
	for (register int i = 1; i <= n; ++i) if (b[i] != c[i]) return printf("No"), 0;
	printf("Yes");
}