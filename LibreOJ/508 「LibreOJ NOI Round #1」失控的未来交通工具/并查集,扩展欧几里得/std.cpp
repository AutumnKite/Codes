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
const int N = 1000005;
int n, m, q, fa[N], fw[N], dep[N], g[N];
void inc(int &a, int b){ (a += b) >= m ? a -= m : 0; }
void dec(int &a, int b){ (a -= b) < 0 ? a += m : 0; }
int plus(int a, int b){ return (a += b) >= m ? a - m : a; }
int minus(int a, int b){ return (a -= b) < 0 ? a + m : a; }
int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }
int find(int &x){
	if (fa[x] == x) return 0;
	else return plus(fw[x], find(fa[x]));
}
void merge(int x, int y, int w){
	int d = plus(find(x), find(y));
	if (x == y) return g[x] = gcd(g[x], gcd(plus(w, w), plus(d, w))), void(0);
	if (dep[x] < dep[y]) std :: swap(x, y);
	fa[y] = x, fw[y] = w, dep[x] += dep[x] == dep[y], g[x] = gcd(gcd(g[x], g[y]), plus(w, w));
}
int main(){
	n = read(), m = read(), q = read();
	for (register int i = 1; i <= n; ++i) fa[i] = i, fw[i] = 0, dep[i] = 1, g[i] = m;
	while (q--){
		int op = read(), u = read(), v = read();
		if (op == 1){ merge(u, v, read() % m); continue; }
		int d = plus(find(u), find(v)), a = read(), b = read(), c = read();
		if (u != v){ print(0); continue; }
		dec(a, d);
	}
}