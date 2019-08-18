#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 55
int n, m, a[N], w[N], s[N], dp[N][N][2];
int main(){
	scanf("%d%d", &n, &m);
	for (register int i = 1; i <= n; ++i)
		scanf("%d%d", a + i, w + i), s[i] = s[i - 1] + w[i];
	memset(dp, 0x3f, sizeof dp);
	dp[m][m][0] = dp[m][m][1] = 0;
	for (register int len = 2; len <= n; ++len)
		for (register int i = 1, j; (j = i + len - 1) <= n; ++i)
			dp[i][j][0] = std :: min(dp[i + 1][j][1] + (a[j] - a[i]) * (s[n] - s[j] + s[i]), 
			    dp[i + 1][j][0] + (a[i + 1] - a[i]) * (s[n] - s[j] + s[i])), 
			dp[i][j][1] = std :: min(dp[i][j - 1][0] + (a[j] - a[i]) * (s[n] - s[j - 1] + s[i - 1]), 
			    dp[i][j - 1][1] + (a[j] - a[j - 1]) * (s[n] - s[j - 1] + s[i - 1]));
	printf("%d", std :: min(dp[1][n][1], dp[1][n][0]));
}