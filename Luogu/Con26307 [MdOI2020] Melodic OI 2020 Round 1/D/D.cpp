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
int n, q;
int edge, to[N << 1], tw[N << 1], pr[N << 1], hd[N];
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
}
int Fa[N][18];
int fa[N], sz[N], dep[N], dis[N], son[N], top[N], idx, dfn[N], id[N];
void dfs(int u){
	Fa[u][0] = fa[u];
	for (register int i = 1; i <= 17; ++i) Fa[u][i] = Fa[Fa[u][i - 1]][i - 1];
	dep[u] = dep[fa[u]] + 1, sz[u] = 1;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa[u])
			fa[v] = u, dis[v] = dis[u] + tw[i], dfs(v), sz[u] += sz[v], 
			!son[u] || sz[v] > sz[son[u]] ? son[u] = v : 0;
}
void dfs(int u, int tp){
	top[u] = tp, dfn[u] = ++idx, id[idx] = u;
	if (son[u]) dfs(son[u], tp);
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa[u] && v != son[u]) dfs(v, v);
}
int rt[N], lastCnt;
struct Chairman_Tree{
	int cnt, ls[N * 150], rs[N * 150], lz[N * 150];
	void modify(int &u, int _u, int l, int r, int L, int R){
		if (u <= lastCnt) u = ++cnt, ls[u] = ls[_u], rs[u] = rs[_u], lz[u] = lz[_u];
		if (L == l && r == R) return ++lz[u], void(0);
		int md = (l + r) >> 1;
		if (R <= md) modify(ls[u], ls[_u], l, md, L, R);
		else if (L > md) modify(rs[u], rs[_u], md + 1, r, L, R);
		else modify(ls[u], ls[_u], l, md, L, md), modify(rs[u], rs[_u], md + 1, r, md + 1, R);
	}
	int query(int u, int _u, int l, int r, int x){
		if (l == r) return lz[u] - lz[_u];
		int md = (l + r) >> 1;
		if (x <= md) return query(ls[u], ls[_u], l, md, x) + lz[u] - lz[_u];
		else return query(rs[u], rs[_u], md + 1, r, x) + lz[u] - lz[_u];
	}
}T;
void update(int u){
	int _u = u;
	while (u){
		T.modify(rt[_u], rt[_u], 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
}
int lca(int u, int v){
	while (top[u] != top[v]){
		if (dep[top[u]] < dep[top[v]]) std::swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}
int query(int rt, int _rt, int u, int w){
	if (T.query(rt, _rt, 1, n, dfn[u]) >= w) return u;
	for (register int i = 17; ~i; --i)
		if (Fa[u][i] && T.query(rt, _rt, 1, n, dfn[Fa[u][i]]) < w) u = Fa[u][i];
	return fa[u];
}
bool is_ancestor(int u, int v){
	return dfn[u] <= dfn[v] && dfn[v] < dfn[u] + sz[u];
}
int main(){
	n = read(), q = read();
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), addedge(u, v, w), addedge(v, u, w);
	dfs(1), dfs(1, 1);
	for (register int i = 1; i <= n; ++i)
		rt[i] = rt[i - 1], update(i), lastCnt = T.cnt;
	int ans = 0;
	while (q--){
		int u = read() ^ ans, l = read() ^ ans, r = read() ^ ans;
		int v = query(rt[r], rt[l - 1], l, r - l + 1);
		if (is_ancestor(v, u)) v = query(rt[r], rt[l - 1], u, 1);
		int LCA = lca(u, v);
		ans = (dis[u] - dis[LCA]) + (dis[v] - dis[LCA]);
		print(ans);
	}
}