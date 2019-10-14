#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
long long read(){
	register long long x = 0;
	register char ch = getchar(), f = 1;
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
void print(long long x){
	if (x == 0) return putchar('0'), void(0);
	int cnt = 0, d[25];
	for (x < 0 ? x = -x, putchar('-') : 0; x; x /= 10) d[++cnt] = x % 10;
	while (cnt) putchar(d[cnt] ^ '0'), --cnt;
}
long long a, b, n, m, l, r, dp[65][2][2][2][2];
long long DP(int p, int ea, int eb, int el, int er){
	// printf("%d %d %d %d %d\n", p, ea, eb, el, er);
	if (p < 0) return 1;
	if (~dp[p][ea][eb][el][er]) return dp[p][ea][eb][el][er];
	long long ans = 0;
	if (n >> p & 1){
		if ((!eb || (b >> p & 1)) && (!el || !(l >> p & 1)))
			ans += DP(p - 1, ea & !(a >> p & 1), eb, el, er & !(r >> p & 1));
		if ((!ea || (a >> p & 1)) && (!er || (r >> p & 1)))
			ans += DP(p - 1, ea, eb & !(b >> p & 1), el & (l >> p & 1), er);
	}
	else{
		if (!el || !(l >> p & 1))
			ans += DP(p - 1, ea & !(a >> p & 1), eb & !(b >> p & 1), el, er & !(r >> p & 1));
		if ((!ea || (a >> p & 1)) && (!eb || (b >> p & 1)) && (!el || !(l >> p & 1)))
			ans += DP(p - 1, ea, eb, el, er & !(r >> p & 1));
	}
	return dp[p][ea][eb][el][er] = ans;
}
void solve(){
	a = read(), b = read(), n = read(), m = std :: min(n, read());
	l = (n - m + 1) >> 1, r = (n + m) >> 1;
	memset(dp, -1, sizeof dp);
	print(DP(59, 1, 1, 1, 1)), putchar('\n');
}
int main(){
	int T = read();
	while (T--) solve();
}
