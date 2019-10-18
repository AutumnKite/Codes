#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 5005
#define P 1000000007
int n, m, l1[N], r1[N], l2[N], r2[N];
int l[N], r[N], dp[N][N];
long long s1[N], s2[N];
void erase(int i, int j){
	s1[i] -= dp[i][j], s2[j] -= dp[i][j];
}
void solve(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i)
		l1[i] = l2[i] = 0, r1[i] = r2[i] = i;
	for (register int i = 1; i <= m; ++i){
		int l = read(), r = read(), x = read();
		if (x == 1) r1[r] = std :: min(r1[r], l);
		else if (x == 3) l2[r] = std :: max(l2[r], l);
		else r2[r] = std :: min(r2[r], l), l1[r] = std :: max(l1[r], l);
	}
	for (register int i = 0; i < n; ++i) s1[i] = s2[i] = l[i] = r[i] = 0;
	s1[0] = s2[0] = 3, dp[0][0] = 3, r[0] = 1;
	for (register int i = 1; i <= n; ++i){
		if (l1[i] >= r1[i] || l2[i] >= r2[i]) return puts("0"), void(0);
		for (register int j = 0; j < i; ++j)
			if (j < l1[i] || j >= r1[i])
				while (l[j] < r[j]) erase(j, --r[j]);
			else{
				while (l[j] < l2[i] && l[j] < r[j]) erase(j, l[j]++);
				while (r[j] > r2[i] && l[j] < r[j]) erase(j, --r[j]);
			}
		if (i == n) break;
		for (register int j = 0; j < i; ++j)
			dp[i][j] = (s1[j] + s2[j]) % P, s1[i] += dp[i][j], s2[j] += dp[i][j];
		l[i] = 0, r[i] = i;
	}
	long long ans = 0;
	for (register int i = 0; i < n; ++i) ans += s1[i];
	printf("%lld\n", ans % P);
}
int main(){
	int T = read();
	while (T--) solve();
}