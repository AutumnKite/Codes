#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define N 11
int n, m, k, a[N][N], sum[N][N];
double x_, dp[N][N][N][N][N], ans;
int Sum(int x1, int y1, int x2, int y2){
	--x1, --y1;
	return sum[x2][y2] - sum[x1][y2] - sum[x2][y1] + sum[x1][y1];
}
double sqr(double x){ return x * x; }
double DP(int x1, int y1, int x2, int y2, int k){
	double &ans = dp[x1][y1][x2][y2][k];
	if (ans) return ans;
	if (k == 1) return sqr(Sum(x1, y1, x2, y2) - x_);
	ans = 1e100;
	for (register int i = x1; i < x2; ++i)
		for (register int j = 1; j < k; ++j)
			ans = std :: min(ans, DP(x1, y1, i, y2, j) + DP(i + 1, y1, x2, y2, k - j));
	for (register int i = y1; i < y2; ++i)
		for (register int j = 1; j < k; ++j)
			ans = std :: min(ans, DP(x1, y1, x2, i, j) + DP(x1, i + 1, x2, y2, k - j));
	return ans;
}
int main(){
	scanf("%d%d%d", &n, &m, &k);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			scanf("%d", &a[i][j]), 
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
	x_ = 1.0 * sum[n][m] / k;
	ans = DP(1, 1, n, m, k);
	printf("%.2lf", sqrt(ans / k));
}