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
long long a, b, n, m;
long long abs(long long x){
	return x >= 0 ? x : -x;
}
void solve(){
	a = read(), b = read(), n = read(), m = read();
	long long ans = 0;
	for (register int i = 0; i <= a; ++i){
		int j = i ^ n;
		if (j <= b && abs(i - j) <= m) ++ans;
	}
	printf("%lld\n", ans);
}
int main(){
	int T = read();
	while (T--) solve();
}
