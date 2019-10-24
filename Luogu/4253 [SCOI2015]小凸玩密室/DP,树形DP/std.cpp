#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 200005
int n, a[N], dep[N];
long long w[N], s[N], dp[N][20][2], ans;
int pson(int i, int j){ return (i >> (j - 1)) ^ 1; }
long long dis(int i, int j){ return s[i] - s[i >> j]; }
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	dep[1] = 1;
	for (register int i = 2; i <= n; ++i)
		w[i] = read(), s[i] = s[i >> 1] + w[i], dep[i] = dep[i >> 1] + 1;
	for (register int i = n; i; --i){
		for (register int j = 1; j <= dep[i]; ++j){
			if ((i << 1) > n){
				dp[i][j][0] = dis(i, j) * a[i >> j], dp[i][j][1] = (dis(i, j) + w[pson(i, j)]) * a[pson(i, j)];
				continue;
			}
			if ((i << 1 | 1) > n){
				dp[i][j][0] = w[i << 1] * a[i << 1] + dp[i << 1][j + 1][0];
				dp[i][j][1] = w[i << 1] * a[i << 1] + dp[i << 1][j + 1][1];
				continue;
			}
			for (register int k = 0; k < 2; ++k){
				long long s1 = w[i << 1 | 1] * a[i << 1 | 1] + dp[i << 1 | 1][1][1] + dp[i << 1][j + 1][k];
				long long s2 = w[i << 1] * a[i << 1] + dp[i << 1][1][1] + dp[i << 1 | 1][j + 1][k];
				dp[i][j][k] = std :: min(s1, s2);
			}
		}
		// for (register int j = 1; j <= dep[i]; ++j) printf("%lld %lld\n", dp[i][j][0], dp[i][j][1]);
		// putchar('\n');
	}
	ans = 1ll << 60;
	for (register int i = 1; i <= n; ++i){
		long long sum = dp[i][1][0];
		for (register int j = i; j > 1; j >>= 1)
			if ((j ^ 1) <= n) sum += w[j ^ 1] * a[j ^ 1] + dp[j ^ 1][2][0];
			else sum += w[j >> 1] * a[j >> 2];
		// printf("%lld\n", sum);
		ans = std :: min(ans, sum);
	}
	printf("%lld\n", ans);
}