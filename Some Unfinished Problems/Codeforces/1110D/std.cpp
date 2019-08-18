#include <cstdio>
#include <cstring>
#include <algorithm>
int n, m, a[1000005], dp[1000005][7][7];
int main(){
	scanf("%d%d", &n, &m);
	if (n < 3) return printf("0"), 0;
	for (register int i = 1, x; i <= n; ++i) scanf("%d", &x), ++a[x];
	for (register int i = 1; i <= m; ++i)
		if (a[i] > 6) a[i] = (a[i] - 3) % 3 + 3;
	dp[1][0][0] = a[1] >= 3;
	for (register int i = 0; i <= 6; ++i) dp[2][i][0] = (a[2] >= 3) + (i >= 3);
	for (register int i = 3; i <= m; ++i)
		if (a[i] > 0)
			for (register int j = 0; j <= a[i - 1]; ++j)
				for (register int k = 0; k <= a[i - 2]; ++k){
					if (k > j) dp[i][j][k] = dp[i][j][j];
					for (register int x = 0; x <= 2; ++x)
						if (x * 3 <= a[i])
							for (register int y = 0; y <= 2; ++y)
								if (y <= j && y <= k && y <= a[i] - x * 3)
									dp[i][j][k] = std :: max(dp[i][j][k], dp[i - 1][k][a[i - 3]] + x + y);
				}
	printf("%d", dp[m][a[m - 1]][a[m - 2]]);
	getchar(), getchar();
}