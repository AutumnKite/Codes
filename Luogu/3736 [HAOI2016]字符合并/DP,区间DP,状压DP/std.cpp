#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 305
#define INF 0x3f3f3f3f3f3f3f3fll
int n, k, a[N], c[256];
long long dp[N][N][256], w[256];
int main(){
	n = read(), k = read();
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= n; ++j)
			for (register int p = 0; p < (1 << k); ++p)
				dp[i][j][p] = -INF;
	for (register int i = 1; i <= n; ++i) a[i] = read(), dp[i][i][a[i]] = 0;
	for (register int i = 0; i < (1 << k); ++i) c[i] = read(), w[i] = read();
	for (register int len = 2; len <= n; ++len)
		for (register int i = 1; i <= n - len + 1; ++i){
			int j = i + len - 1, l = len - 1;
			l = (l - 1) % (k - 1) + 1;
			for (register int p = 0; p < (1 << l); ++p)
				for (register int t = j; t > i; t -= k - 1){
					dp[i][j][p << 1] = std :: max(dp[i][j][p << 1], dp[i][t - 1][p] + dp[t][j][0]);
					dp[i][j][p << 1 | 1] = std :: max(dp[i][j][p << 1 | 1], dp[i][t - 1][p] + dp[t][j][1]);
				}
			if (l == k - 1){
				long long tmp[2] = {-INF, -INF};
				for (register int p = 0; p < (1 << k); ++p)
					tmp[c[p]] = std :: max(tmp[c[p]], dp[i][j][p] + w[p]);
				dp[i][j][0] = tmp[0], dp[i][j][1] = tmp[1];
			}
		}
	int l = (n - 1) % (k - 1) + 1;
	long long ans = -INF;
	for (register int p = 0; p < (1 << l); ++p)
		ans = std :: max(ans, dp[1][n][p]);
	printf("%lld\n", ans);
}
