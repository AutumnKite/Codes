#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n, a[N], k, b[N << 2];
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i < n; ++i)
		if (a[i] == a[i + 1] && a[i]) return printf("-1"), 0;
	if (a[1] == 3 || a[n] == 3) return printf("-1"), 0;
	for (register int j = 2; j < n; ++j)
		if (a[j] == 3) b[++k] = j, b[++k] = j + 1, b[++k] = j - 1, b[++k] = j;
	for (register int j = 1; j <= n; ++j)
		if (a[j] == 2)
			if (a[j - 1] != 3 && j > 1) b[++k] = j - 1, b[++k] = j;
			else if (a[j + 1] != 3 && j < n) b[++k] = j + 1, b[++k] = j;
			else return printf("-1"), 0;
	for (register int j = 1; j <= n; ++j)
		if (a[j] == 1) b[++k] = j;
	printf("%d\n", k);
	for (register int i = 1; i <= k; ++i) printf("%d ", b[i]);
}
