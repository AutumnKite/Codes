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
int read(char *s){
	int n = 0;
	char ch = getchar();
	for (; isspace(ch) && ch != EOF; ch = getchar()) ;
	for (; !isspace(ch) && ch != EOF; ch = getchar()) s[++n] = ch;
	return n;
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
const int N = 1000005, P = 19930726;
long long K;
int n, d[N], cnt[N], ans;
char s[N];
void manacher(int *d, char *s, int n){
	for (register int i = 1, m = 0, r = 0; i <= n; ++i){
		d[i] = i > r ? 0 : std::min(r - i + 1, d[m - (i - m)]);
		while (i - d[i] > 0 && i + d[i] <= n && s[i - d[i]] == s[i + d[i]]) ++d[i];
		if (i + d[i] - 1 > r) m = i, r = i + d[i] - 1;
	}
}
int qpow(int a, int b){
	int s = 1;
	for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) s = 1ll * s * a % P;
	return s;
}
int main(){
	n = read(), K = read(), n = read(s);
	manacher(d, s, n);
	for (register int i = 1; i <= n; ++i) ++cnt[d[i] - 1];
	for (register int i = n / 2 - 1; i >= 0; --i) cnt[i] += cnt[i + 1];
	ans = 1;
	for (register int i = n / 2; i >= 0 && K; --i){
		if (K < cnt[i]) ans = 1ll * ans * qpow(i << 1 | 1, K) % P, K = 0;
		else ans = 1ll * ans * qpow(i << 1 | 1, cnt[i]) % P, K -= cnt[i];
	}
	if (K) print(-1); else print(ans);
}