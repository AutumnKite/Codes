#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, m, dp[2005];
struct node{
	int x, y;
	bool operator < (const node &b) const {
		return x + y < b.x + b.y;
	}
}a[2005];
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = (node){read(), read()};
	m = read(), std :: sort(a + 1, a + 1 + n);
	for (register int i = 1; i <= n; ++i) dp[i] = -0x3f3f3f3f, dp[0] += a[i].x;
	for (register int i = 1; i <= n; ++i)
		for (register int j = i; j; --j)
			if (dp[j - 1] + a[i].y >= m) dp[j] = std :: max(dp[j], dp[j - 1] - a[i].x);
	for (register int i = n; ~i; --i) if (dp[i] >= 0) return printf("%d", i), 0;
}