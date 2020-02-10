#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
char buf[1 << 23], *ps = buf, *pt = buf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
char pbuf[1 << 23], *pp = pbuf;
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 200005;
const long double eps = 1e-9;
int n, a[N];
long long s[N], s2[N], m;
bool check(int x){
	for (register int i = x; i <= n; ++i){
		long double p = (long double)1.0 * (s[i] - s[i - x]) / x;
		if (s2[i] - s2[i - x] - p * (s[i] - s[i - x]) < m + eps) return 1;
	}
	return 0;
}
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	std::sort(a + 1, a + 1 + n);
	for (register int i = 1; i <= n; ++i)
		s[i] = s[i - 1] + a[i], s2[i] = s2[i - 1] + 1ll * a[i] * a[i];
	int l = 1, r = n, md, ans = 0;
	while (l <= r) if (check(md = (l + r) >> 1)) l = md + 1, ans = md; else r = md - 1;
	print(n - ans);
}