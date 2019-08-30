#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n, m, a[N], rt;
int edge, to[N << 1], pr[N << 1], hd[N];
void addedge(int u, int v){
	to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
}
int dep[N], fa[N], sz[N], son[N];
void dfs(int u){
	sz[u] = 1;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa[u])
			fa[v] = u, dep[v] = dep[u] + 1, dfs(v), sz[u] += sz[v], 
			!son[u] || sz[v] > sz[son[u]] ? son[u] = v : 0;
}
int top[N], idx, st[N], id[N], ed[N];
void dfs(int u, int tp){
	top[u] = tp, id[st[u] = ++idx] = u;
	if (son[u]) dfs(son[u], tp);
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa[u] && v != son[u]) dfs(v, v);
	ed[u] = idx;
}
int val[N << 2], lz[N << 2];
void build(int u, int l, int r){
	if (l == r) return val[u] = a[id[l]], lz[u] = 0, void(0);
	int mid = (l + r) >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	val[u] = std :: min(val[u << 1], val[u << 1 | 1]);
}
void down(int u){
	if (lz[u]) val[u << 1] = val[u << 1 | 1] = lz[u << 1] = lz[u << 1 | 1] = lz[u];
}
void modify(int u, int l, int r, int L, int R, int v){
	if (L <= l && r <= R) return val[u] = lz[u] = v, void(0);
	int mid = (l + r) >> 1; down(u);
	if (L <= mid) modify(u << 1, l, mid, L, R, v);
	if (R > mid) modify(u << 1 | 1, mid + 1, r, L, R, v);
	val[u] = std :: min(val[u << 1], val[u << 1 | 1]);
}
int query(int u, int l, int r, int L, int R){
	if (L <= l && r <= R) return val[u];
	int mid = (l + r) >> 1, ans = 2147483647; down(u);
	if (L <= mid) ans = std :: min(ans, query(u << 1, l, mid, L, R));
	if (R > mid) ans = std :: min(ans, query(u << 1 | 1, mid + 1, r, L, R));
	return ans;
}
void Modify(int u, int v, int w){
	while (top[u] != top[v]){
		if (dep[top[u]] < dep[top[v]]) std :: swap(u, v);
		modify(1, 1, n, st[top[u]], st[u], w), u = fa[top[u]];
	}
	if (dep[u] < dep[v]) std :: swap(u, v);
	modify(1, 1, n, st[v], st[u], w);
}
int Query(int u){
	if (u == rt) return val[1];
	if (st[rt] < st[u] || st[rt] > ed[u]) return query(1, 1, n, st[u], ed[u]);
	int v = rt;
	while (st[fa[top[v]]] > st[u] && st[fa[top[v]]] <= ed[u]) v = fa[top[v]];
	if (fa[top[v]] == u) v = top[v]; else v = son[u];
	return std :: min(query(1, 1, n, 1, st[v] - 1), query(1, 1, n, ed[v] + 1, n));
}
int main(){
	n = read(), m = read();
	for (register int i = 1, u, v; i < n; ++i)
		u = read(), v = read(), addedge(u, v), addedge(v, u);
	for (register int i = 1; i <= n; ++i) a[i] = read();
	rt = read();
	dfs(rt), dfs(rt, rt), build(1, 1, n);
	while (m--){
		int opt = read(), x, y, w;
		if (opt == 1) rt = read();
		if (opt == 2) x = read(), y = read(), w = read(), Modify(x, y, w);
		if (opt == 3) printf("%d\n", Query(read()));
	}
	getchar(), getchar();
}
