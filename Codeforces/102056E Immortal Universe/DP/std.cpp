#include <cstdio>
#include <cstring>
#include <algorithm>
const int N = 5005, P = 998244353;
int n, m, f[2][N << 1], g[2][N << 1], dp[2][N << 1];
char a[N], b[N];
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
int plus(int a, int b){ return (a += b) >= P ? a - P : a; }
int minus(int a, int b){ return (a -= b) < 0 ? a + P : a; }
void DP(int n, char *a, int *f){
	int u = n & 1;
	for (register int i = 0; i <= (n << 1); ++i) dp[0][i] = dp[1][i] = 0;
	dp[u][n] = 1;
	for (register int i = n; i; --i){
		register int l = i, r = (n << 1) - i;
		if (a[i] == 'P')
			for (register int j = l; j <= r; ++j)
				if (dp[u][j]) inc(dp[u ^ 1][std :: min(n, j) - 1], dp[u][j]), dp[u][j] = 0;
		if (a[i] == 'V')
			for (register int j = l; j <= r; ++j)
				if (dp[u][j]) inc(dp[u ^ 1][j + 1], dp[u][j]), dp[u][j] = 0;
		if (a[i] == '?')
			for (register int j = l; j <= r; ++j)
				if (dp[u][j]){
					inc(dp[u ^ 1][std :: min(n, j) - 1], dp[u][j]);
					inc(dp[u ^ 1][j + 1], dp[u][j]), dp[u][j] = 0;
				}
		u ^= 1;
	}
	for (register int i = 0; i <= (n << 1); ++i) f[i] = dp[u][i];
}
int solve(int dn, int dm){
	int _n = n + dn, _m = m + dm, res = 0;
	for (register int i = -_n; i <= _n; ++i)
		if (f[dn][i + _n])
			for (register int j = std :: max(-_m, -1 - i); j <= _m; ++j)
				res = (res + 1ll * f[dn][i + _n] * g[dm][j + _m]) % P;
	return res;
}
int main(){
	scanf("%s%s", a + 1, b + 1), n = strlen(a + 1), m = strlen(b + 1);
	a[n + 1] = b[m + 1] = 'P';
	DP(n, a, f[0]), DP(n + 1, a, f[1]), DP(m, b, g[0]), DP(m + 1, b, g[1]);
	if ((n + m) & 1) printf("%d\n", solve(1, 1));
	else printf("%d\n", minus(plus(solve(1, 0), solve(0, 1)), solve(0, 0)));
}
