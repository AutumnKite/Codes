#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 3005
int n, m, h, t, s[N];
long long a[N], dp[2][N];
long long X(int i, int j){
	return a[i] - a[j];
}
long long Y(int k, int i, int j){
	return dp[k ^ 1][i] + a[i] * a[i] - dp[k ^ 1][j] - a[j] * a[j];
}
long long val(int k, int i, int j){
	return dp[k ^ 1][j] + (a[i] - a[j]) * (a[i] - a[j]);
}
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i] = a[i - 1] + read();
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = 0;
	for (register int i = 1; i <= m; ++i){
		h = 1, t = 1, s[t] = i - 1;
		for (register int j = i; j <= n; ++j){
			while (h < t && Y(i & 1, s[h + 1], s[h]) <= 2 * a[j] * X(s[h + 1], s[h])) ++h;
			dp[i & 1][j] = val(i & 1, j, s[h]);
			while (h < t && Y(i & 1, s[t], s[t - 1]) * X(j, s[t]) >= Y(i & 1, j, s[t]) * X(s[t], s[t - 1])) --t;
			s[++t] = j;
		}
	}
	printf("%lld\n", m * dp[m & 1][n] - a[n] * a[n]);
}