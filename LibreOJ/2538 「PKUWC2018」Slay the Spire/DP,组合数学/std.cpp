#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
char buf[1 << 23], *ps = buf, *pt = buf, pbuf[1 << 23], *pp = pbuf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 1505, P = 998244353;
int n, m, k, a[N], b[N], fac[N << 1], inv[N << 1], f[N], g[N], ans;
int qpow(int a, int b = P - 2){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
void init(int n){
	fac[0] = 1;
	for (register int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % P;
	inv[n] = qpow(fac[n]);
	for (register int i = n; i; --i) inv[i - 1] = 1ll * inv[i] * i % P;
}
int C(int n, int m){
	if (m < 0 || m > n) return 0;
	return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}
void solve(){
	n = read(), m = read(), k = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= n; ++i) b[i] = read();
	std :: sort(a + 1, a + 1 + n), std :: reverse(a + 1, a + 1 + n);
	std :: sort(b + 1, b + 1 + n), std :: reverse(b + 1, b + 1 + n);
	for (register int i = 0; i <= n; ++i) f[i] = 0, g[i] = 0;
	init(n << 1), f[0] = 1, ans = 0;
	if (k == 1){
		for (register int i = 1; i <= n; ++i) ans = (ans + 1ll * b[i] * C(2 * n - i, m - 1)) % P;
		return print(ans), void(0);
	}
	for (register int i = 1; i <= n; ++i){
		if (k - 1 <= i){
			for (register int j = 1; j <= n; ++j)
				ans = (ans + (1ll * b[j] * C(2 * n - i - j, m - k) % P) * (1ll * f[k - 2] * a[i] % P)) % P;
		}
		for (register int j = i; j; --j)
			f[j] = (f[j] + 1ll * f[j - 1] * a[i]) % P;
	}
	for (register int i = 1; i <= n; ++i){
		for (register int j = std :: max(k - i, 0); j <= k - 2 && j <= n; ++j)
			ans = (ans + (1ll * f[j] * C(n - i, m - k) % P) * ((g[k - j - 1] + 1ll * C(i - 1, k - j - 1) * b[i]) % P)) % P;
		for (register int j = i; j; --j)
			g[j] = (g[j] + g[j - 1] + 1ll * C(i - 1, j - 1) * b[i]) % P;
	}
	print(ans);
}
int main(){
	int T = read();
	while (T--) solve();
}