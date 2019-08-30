#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
int n;
struct point{
	int x, y;
}a[20], b;
double dp[3][300000][20], d[20][20];
double dis(point a, point b){
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main(){
	scanf("%d", &n);
	for (register int i = 0; i < n; ++i) scanf("%d%d", &a[i].x, &a[i].y);
	for (register int t = 0; t < 3; ++t){
		scanf("%d%d", &b.x, &b.y);
		for (register int i = 0; i < (1 << n); ++i)
			for (register int j = 0; j <= n; ++j)
				dp[t][i][j] = 1e100;
		for (register int i = 0; i < n; ++i)
			for (register int j = 0; j < n; ++j)
				d[i][j] = dis(a[i], a[j]);
		dp[t][0][n] = 0;
		for (register int i = 0; i < n; ++i) dp[t][1 << i][i] = dis(b, a[i]);
		for (register int i = 0; i < (1 << n); ++i)
			for (register int j = 0; j < n; ++j)
				if (i >> j & 1){
					dp[t][i][n] = std :: min(t ? dp[t - 1][i][n] : 1e100, dp[t][i][n]);
					for (register int k = 0; k < n; ++k)
						if (i >> k & 1 && k != j)
							dp[t][i][j] = std :: min(dp[t][i][j], dp[t][1 << j ^ i][k] + d[k][j]);
					dp[t][i][j] = std :: min(dp[t][i][j], t ? dp[t - 1][1 << j ^ i][n] + dis(b, a[j]) : 1e100);
					dp[t][i][n] = std :: min(dp[t][i][n], dp[t][i][j]);
				}
	}
	printf("%.12lf\n", dp[2][(1 << n) - 1][n]);
}

