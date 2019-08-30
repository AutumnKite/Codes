#include <cstdio>
#define N 355
int n, m, t, x, a[N][N], b[N][N][10];
long long ans;
char s[N];
int calc(int x1, int y1, int x2, int y2, int k){
	if (x1 > x2 || y1 > y2 || k < 1 || k > 9) return 0;
	--x1, --y1;
	return b[x2][y2][k] - b[x1][y2][k] - b[x2][y1][k] + b[x1][y1][k];
}
int main(){
	scanf("%d%d%d", &n, &m, &t);
	for (register int i = 1; i <= n; ++i){
		scanf("%s", s + 1);
		for (register int j = 1; j <= m; ++j){
			x = s[j] - '0';
			a[i][j] = a[i][j - 1] + x;
			for (register int k = 1; k <= 9; ++k)
				b[i][j][k] = b[i - 1][j][k] + b[i][j - 1][k] - b[i - 1][j - 1][k];
			++b[i][j][x];
		}
	}
	for (register int l = 1; l <= m - 2; ++l)
		for (register int r = l + 2; r <= m; ++r){
			int sum = 0;
			for (register int i = 1, j = 1; i <= n; ++i){
				sum += a[i][r] - a[i][l - 1];
				while (sum > t + 9) sum -= a[j][r] - a[j][l - 1], ++j;
				ans += calc(j + 1, l + 1, i - 1, r - 1, sum - t);
				ans += calc(j + 2, l + 1, i - 1, r - 1, sum - (a[j][r] - a[j][l - 1]) - t);
				ans += calc(j + 3, l + 1, i - 1, r - 1, sum - (a[j][r] - a[j][l - 1]) - (a[j + 1][r] - a[j + 1][l - 1]) - t);
			}
		}
	printf("%lld\n", ans);
}
