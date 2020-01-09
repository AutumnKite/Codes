#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
char buf[1 << 23], *ps = buf, *pt = buf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 600005, P = 998244353;
int n, p[N], suf[N], fac[N << 1], inv[N << 1];
void inc(int &a, int b){ (a += b) >= P ? a -= P : 0; }
void dec(int &a, int b){ a < b ? a += P - b : a -= b; }
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
void init(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
	inv[n] = qpow(fac[n], P - 2);
	for (register int i = n; i; --i) inv[i - 1] = 1ll * inv[i] * i % P;
}
int C(int n, int m){
	if (m < 0 || m > n) return 0;
	return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}
void solve(){
	n = read();
	for (register int i = 1; i <= n; ++i) p[i] = read();
	suf[n + 1] = n + 1;
	for (register int i = n; i; --i) suf[i] = std::min(suf[i + 1], p[i]);
	int mx = 0, ans = 0;
	for (register int i = 1; i <= n && p[i] < n; ++i){
		int lst = mx;
		mx = std::max(mx, p[i]);
		// for (register int j = mx + 1; j <= n; ++j)
		// 	inc(ans, C(n - i + n - j, n - i));
		// for (register int j = mx + 1; j <= n; ++j)
		// 	dec(ans, C(n - i + n - j, n - i + 1));
		inc(ans, C(n - i + n - mx, n - i + 1));
		dec(ans, C(n - i + n - mx, n - i + 2));
		if (lst > p[i] && p[i] > suf[i + 1]) break;
	}
	printf("%d\n", ans);
}
int main(){
	freopen("inverse.in", "r", stdin);
	freopen("inverse.out", "w", stdout);
	init(1200000);
	int T = read();
	while (T--) solve();
}