#include <cstdio>
#include <cctype>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>
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
const int N = 200005, P = 998244353;
int n, q, p[N], ip[N], c[N], a[N], b[N];
int qpow(int a, int b = P - 2){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
int main(){
	n = read(), q = read();
	for (register int i = 1; i <= n; ++i)
		p[i] = 1ll * read() * qpow(100) % P, ip[i] = qpow(p[i]);
	c[1] = 1, c[n + 1] = 1;
	while (q--){
		int u = read(), ans = 0;
		c[u] ^= 1;
		for (register int r = 2, l = 1; r <= n + 1; ++r)
			if (c[r]){
				a[l] = 1, b[l] = 0;
				for (register int i = l; i < r; ++i){
					a[i + 1] = 1ll * (a[i] + p[i] - 1) * ip[i] % P;
					b[i + 1] = 1ll * (b[i] + P - 1) * ip[i] % P;
				}
				ans = (ans + 1ll * (P - b[r]) * qpow(a[r])) % P;
				l = r;
			}
		print(ans);
	}
}
