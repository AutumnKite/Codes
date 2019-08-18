#include <cstdio>
#include <algorithm>
#define N 105
#define P 9999973
int n, m;
long long dp[N][N][N];
int main(){
	scanf("%d%d", &n, &m);
	dp[0][0][0] = 1;
	for (register int i = 0; i < n; ++i)
		for (register int j = 0; j <= m; ++j)
			for (register int k = 0; k <= m; ++k){
				(dp[i + 1][j][k] += dp[i][j][k]) %= P; // No
				(dp[i + 1][j + 1][k] += dp[i][j][k] * (m - k - j)) %= P; // 0
				if (j) (dp[i + 1][j - 1][k + 1] += dp[i][j][k] * j) %= P; // 1
				(dp[i + 1][j + 2][k] += dp[i][j][k] * (m - j - k) * (m - j - k - 1) / 2) %= P; // 0 0
				(dp[i + 1][j][k + 1] += dp[i][j][k] * (m - j - k) * j) %= P; // 0 1
				if (j >= 2) (dp[i + 1][j - 2][k + 2] += dp[i][j][k] * j * (j - 1) / 2) %= P; // 1 1
			}
	long long ans = 0;
	for (register int i = 0; i <= m; ++i)
		for (register int j = 0; j <= m; ++j)
			(ans += dp[n][i][j]) %= P;
	printf("%lld", ans);
}