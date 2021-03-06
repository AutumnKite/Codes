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
const int N = 1000005;
int n, d[N], fa[N];
char s[N];
void manacher(int *d, char *s, int n){
	for (register int i = 1, m = 0, r = 0; i <= n; ++i){
		d[i] = i > r ? 0 : std::min(r - i + 1, d[m - (i - m)]);
		while (i - d[i] > 0 && i + d[i] <= n && s[i - d[i]] == s[i + d[i]]) ++d[i];
		if (i + d[i] - 1 > r) m = i, r = i + d[i] - 1;
	}
}
int find(int x){ return fa[x] == x ? x : (fa[x] = find(fa[x])); }
int main(){
	read(), n = read(s);
	for (register int i = n; i; --i) s[i << 1] = s[i], s[i << 1 | 1] = '#';
	s[1] = '#', n = n * 2 + 1;
	manacher(d, s, n);
	for (register int i = 1; i <= n; ++i)
		if (s[i] == '#') fa[i] = i; else fa[i] = i + 1;
	fa[n + 1] = n + 1;
	int ans = 0;
	for (register int i = 1; i <= n; ++i)
		if (s[i] == '#'){
			for (register int j = find(i - (d[i] - 1) / 2); j < i; j = find(j + 1)){
				if (j + d[j] - 1 >= i){ ans = std::max(ans, (i - j) << 1); break; }
				else fa[j] = j + 1;
			}
		}
	print(ans);
}