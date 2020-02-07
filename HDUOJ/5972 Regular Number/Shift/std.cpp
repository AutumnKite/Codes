#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <bitset>
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
const int N = 1005;
int n, m;
char s[5000005];
std::bitset<N> st[10], f;
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i){
		int c = read();
		for (register int j = 1; j <= c; ++j) st[read()][i] = 1;
	}
	while (1){
		char ch;
		while (!isdigit(ch = getchar()) && ch != EOF) ;
		if (ch == EOF) break;
		s[++m] = ch;
		f <<= 1, f[1] = 1, f &= st[ch ^ '0'];
		if (f[n]){
			for (register int i = m - n + 1; i <= m; ++i) putchar(s[i]);
			putchar('\n');
		}
	}
}