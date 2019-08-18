#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n, m, a[N], ans;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= n; ++i) if (!a[i]) return printf("%d\n", n), 0;
	if (!m) return printf("0\n"), 0;
	long long s = 1;
	for (register int i = 1, j = 0; i <= n; ++i){
		s = s * a[i];
		while (j < i && s > m) s /= a[++j];
		ans = std :: max(ans, i - j);
	}
	printf("%d\n", ans);
}