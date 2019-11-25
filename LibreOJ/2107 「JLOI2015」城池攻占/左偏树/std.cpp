#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
char buf[1 << 23], *ps = buf, *pt = buf, pbuf[1 << 23], *pp = pbuf;
#define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
#define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
long long read(){
	register long long x = 0;
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
const int N = 300005;
int n, m, fa[N], a[N], st[N], ed[N], dep[N], rt[N], ans[N];
long long h[N], v[N], c[N];
struct Leftist_Tree{
	int cnt, fa[N], ls[N], rs[N], dis[N];
	long long val[N], lz0[N], lz1[N];
	Leftist_Tree(){ cnt = 0, dis[0] = -1; }
	int new_node(long long v){
		int u = ++cnt;
		return fa[u] = u, ls[u] = rs[u] = 0, dis[u] = 0, val[u] = v, lz0[u] = 0, lz1[u] = 1, u;
	}
	void add(int u, long long v){ val[u] += v, lz0[u] += v; }
	void mul(int u, long long v){ val[u] *= v, lz1[u] *= v, lz0[u] *= v; }
	void down(int u){
		if (lz1[u] != 1) mul(ls[u], lz1[u]), mul(rs[u], lz1[u]), lz1[u] = 1;
		if (lz0[u]) add(ls[u], lz0[u]), add(rs[u], lz0[u]), lz0[u] = 0;
	}
	int find(int x){ return fa[x] == x ? x : (fa[x] = find(fa[x])); }
	int merge(int x, int y){
		if (!x || !y) return x | y;
		if (val[x] > val[y]) std :: swap(x, y);
		down(x), rs[x] = merge(rs[x], y);
		if (dis[ls[x]] < dis[rs[x]]) std :: swap(ls[x], rs[x]);
		return dis[x] = dis[rs[x]] + 1, fa[ls[x]] = fa[rs[x]] = fa[x] = x;
	}
	int pop(int x){
		fa[ls[x]] = ls[x], fa[rs[x]] = rs[x], down(x), fa[x] = merge(ls[x], rs[x]), val[x] = -1;
		return fa[x];
	}
}T;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) h[i] = read();
	for (register int i = 2; i <= n; ++i) fa[i] = read(), a[i] = read(), v[i] = read();
	for (register int i = 1; i <= m; ++i)
		c[i] = read(), st[i] = read(), rt[st[i]] = T.merge(rt[st[i]], T.new_node(c[i]));
	for (register int i = n; i; --i){
		while (rt[i] && T.val[rt[i]] < h[i])
			ed[rt[i]] = i, rt[i] = T.pop(rt[i]), ++ans[i];
		if (i == 1) break;
		if (a[i]) T.mul(rt[i], v[i]); else T.add(rt[i], v[i]);
		rt[fa[i]] = T.merge(rt[fa[i]], rt[i]);
	}
	for (register int i = 1; i <= n; ++i) dep[i] = dep[fa[i]] + 1;
	for (register int i = 1; i <= n; ++i) print(ans[i]);
	for (register int i = 1; i <= m; ++i) print(dep[st[i]] - dep[ed[i]]);
}