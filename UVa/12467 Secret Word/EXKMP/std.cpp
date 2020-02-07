#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
char buf[1 << 23], *ps = buf, *pt = buf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
int read(){
	register int x = 0;
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
const int N = 2000005;
int n, z[N];
char s[N];
void z_algo(int *z, char *s, int n){
	z[1] = n;
	for (register int i = 2, l = 1, r = 1; i <= n; ++i){
		z[i] = i > r ? 0 : std::min(r - i + 1, z[i - l + 1]);
		while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) ++z[i];
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}
void solve(){
	n = 0;
	char ch = getchar();
	for (; isspace(ch); ch = getchar()) ;
	for (; !isspace(ch); ch = getchar()) s[++n] = ch;
	for (register int i = 1; i <= n; ++i) s[n + i + 1] = s[n - i + 1];
	s[n + 1] = '#';
	z_algo(z, s, n << 1 | 1);
	int ans = 0;
	for (register int i = 1; i <= n; ++i) ans = std::max(ans, z[n + i + 1]);
	for (register int i = ans; i; --i) putchar(s[i]);
	putchar('\n');
}
int main(){
	int T = read();
	while (T--) solve();
}