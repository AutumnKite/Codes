#include <cstdio>
#include <cctype>
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
const int N = 1005;
int n, m, q, f[N][N];
std :: vector< std :: pair<int, int> > E[N];
void dfs(int u, int r){
	if (f[u][r]) return;
	f[u][r] = 1;
	for (auto [v, w] : E[u]) dfs(v, (r + w) % m);
}
int main(){
	n = read(), m = read(), q = read();
	while (q--){
		int op = read(), u = read(), v = read();
		if (op == 1){
			int w = read() % m;
			E[u].push_back({v, w}), E[v].push_back({u, w});
		}
		else{
			int a = read(), b = read(), c = read();
			for (register int i = 1; i <= n; ++i)
				for (register int j = 0; j < m; ++j)
					f[i][j] = 0;
			dfs(u, 0);
			int s = 0;
			for (register int i = 0; i < c; ++i, a = (a + b) % m)
				if (f[v][a]){
					if (!s) print(i);
					++s;
				}
			print(s);
		}
	}
}