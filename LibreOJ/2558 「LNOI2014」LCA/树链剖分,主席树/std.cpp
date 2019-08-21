#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 50005
int n, q;
int edge, to[N << 1], pr[N << 1], hd[N];
void addedge(int u, int v){
	to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
}
int fa[N], sz[N], dep[N], son[N], top[N], idx, dfn[N], id[N];
void dfs(int u){
	dep[u] = dep[fa[u]] + 1, sz[u] = 1;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa[u])
			fa[v] = u, dfs(v), sz[u] += sz[v], 
			!son[u] || sz[v] > sz[son[u]] ? son[u] = v : 0;
}
void dfs(int u, int tp){
	top[u] = tp, dfn[u] = ++idx, id[idx] = u;
	if (son[u]) dfs(son[u], tp);
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa[u] && v != son[u]) dfs(v, v);
}
struct Chairman_Tree{
	int cnt, ls[N * 150], rs[N * 150], lz[N * 150];
	long long sum[N * 150];
	void modify(int &u, int _u, int l, int r, int L, int R){
		u = ++cnt, ls[u] = ls[_u], rs[u] = rs[_u], sum[u] = sum[_u], lz[u] = lz[_u];
		if (L == l && r == R) return ++lz[u], void(0);
		sum[u] += R - L + 1;
		int md = (l + r) >> 1;
		if (R <= md) modify(ls[u], ls[_u], l, md, L, R);
		else if (L > md) modify(rs[u], rs[_u], md + 1, r, L, R);
		else modify(ls[u], ls[_u], l, md, L, md), modify(rs[u], rs[_u], md + 1, r, md + 1, R);
	}
	long long query(int u, int l, int r, int L, int R){
		if (!u) return 0;
		if (L == l && r == R) return sum[u] + 1ll * lz[u] * (R - L + 1);
		long long tmp = 1ll * lz[u] * (R - L + 1);
		int md = (l + r) >> 1;
		if (R <= md) return tmp + query(ls[u], l, md, L, R);
		else if (L > md) return tmp + query(rs[u], md + 1, r, L, R);
		else return tmp + query(ls[u], l, md, L, md) + query(rs[u], md + 1, r, md + 1, R);
	}
}T;
int rt[N];
void update(int u){
	int _u = u;
	while (top[u] != 1){
		T.modify(rt[_u], rt[_u], 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	T.modify(rt[_u], rt[_u], 1, n, 1, dfn[u]);
}
long long query(int rt, int u){
	long long res = 0;
	while (top[u] != 1){
		res += T.query(rt, 1, n, dfn[top[u]], dfn[u]);
		u = fa[top[u]];
	}
	res += T.query(rt, 1, n, 1, dfn[u]);
	return res;
}
int main(){
	n = read(), q = read();
	for (register int i = 2, u; i <= n; ++i)
		u = read() + 1, addedge(u, i), addedge(i, u);
	dfs(1), dfs(1, 1);
	for (register int i = 1; i <= n; ++i) rt[i] = rt[i - 1], update(i);
	while (q--){
		int l = read() + 1, r = read() + 1, k = read() + 1;
		long long ans = query(rt[r], k) - query(rt[l - 1], k);
		printf("%lld\n", ans % 201314);
	}
}
