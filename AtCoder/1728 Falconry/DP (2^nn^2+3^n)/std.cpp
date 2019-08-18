#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
int n;
struct point{
	int x, y;
}a[20], b[3];
double Dp[3][300000][20];
double dis(point a, point b){
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main(){
	scanf("%d", &n);
	for (register int i = 0; i < n; ++i) scanf("%d%d", &a[i].x, &a[i].y);
	for (register int i = 0; i < 3; ++i) scanf("%d%d", &b[i].x, &b[i].y);
	for (register int t = 0; t < 3; ++t){
		double (*dp)[20] = Dp[t];
		for (register int i = 0; i < (1 << n); ++i)
			for (register int j = 0; j <= n; ++j)
				dp[i][j] = 1e100;
		dp[0][n] = 0;
		for (register int i = 0; i < n; ++i) dp[1 << i][i] = dis(b[t], a[i]);
		for (register int i = 0; i < (1 << n); ++i)
			for (register int j = 0; j < n; ++j)
				if (i >> j & 1){
					for (register int k = 0; k < n; ++k)
						if (i >> k & 1 && k != j)
							dp[i][j] = std :: min(dp[i][j], dp[1 << j ^ i][k] + dis(a[k], a[j]));
					dp[i][n] = std :: min(dp[i][n], dp[i][j]);
				}
	}
	double ans = 1e100;
	for (register int i = 0; i < (1 << n); ++i)
		for (register int j = i; j >= 0; j = (j - 1) & i){
			int A = j, B = i ^ j, C = ((1 << n) - 1) ^ i;
			ans = std :: min(ans, Dp[0][A][n] + Dp[1][B][n] + Dp[2][C][n]);
			if (!j) break;
		}
	printf("%.12lf\n", ans);
}

