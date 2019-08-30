#include <cstdio>
#define N 805
#define P 1000000007
int n, m, k, a[N][N], dp[N][N][18][2];
int main(){
	scanf("%d%d%d", &n, &m, &k), ++k;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			scanf("%d", &a[i][j]), dp[i][j][a[i][j] % k][0] = 1;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			for (register int h = 0; h < k; ++h){
				(dp[i][j][h][1] += dp[i - 1][j][(h + a[i][j]) % k][0]) %= P;
				(dp[i][j][h][1] += dp[i][j - 1][(h + a[i][j]) % k][0]) %= P;
				(dp[i][j][h][0] += dp[i - 1][j][(h - a[i][j] + k) % k][1]) %= P;
				(dp[i][j][h][0] += dp[i][j - 1][(h - a[i][j] + k) % k][1]) %= P;
			}
	int ans = 0;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			(ans += dp[i][j][0][1]) %= P;
	printf("%d", ans);
	getchar(), getchar();
}