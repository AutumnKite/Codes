#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 200005
int n, q, a[N];
long long s[N], S;
std :: vector<int> E[N];
int fa[N], dep[N], son[N], sz[N], top[N], Idx, idx[N], idt[N];
void dfs(int u){
	dep[u] = dep[fa[u]] + 1, sz[u] = 1, s[u] = a[u];
	for (auto v : E[u])
		if (v != fa[u]) fa[v] = u, dfs(v), s[u] += s[v], sz[u] += sz[v], !son[u] || sz[v] > sz[son[u]] ? son[u] = v : 0;
}
void dfs(int u, int tp){
	top[u] = tp, idx[u] = ++Idx, idt[Idx] = u;
	if (son[u]) dfs(son[u], tp);
	for (auto v : E[u]) if (v != fa[u] && v != son[u]) dfs(v, v);
}
struct Segment_Tree{
	long long sum[N << 2], sum2[N << 2], lz[N << 2];
	void up(int u){
		sum[u] = sum[u << 1] + sum[u << 1 | 1];
		sum2[u] = sum2[u << 1] + sum2[u << 1 | 1];
	}
	void update(int u, int len, long long w){
		sum2[u] += len * w * w + 2 * w * sum[u], sum[u] += len * w, lz[u] += w;
	}
	void down(int u, int l, int r){
		if (lz[u]){
			int md = (l + r) >> 1;
			update(u << 1, md - l + 1, lz[u]), update(u << 1 | 1, r - md, lz[u]), lz[u] = 0;
		}
	}
	void build(int u, int l, int r){
		if (l == r) return sum[u] = s[idt[l]], sum2[u] = sum[u] * sum[u], void(0);
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r), up(u);
	}
	void modify(int u, int l, int r, int L, int R, long long w){
		if (L <= l && r <= R) return update(u, r - l + 1, w), void(0);
		int md = (l + r) >> 1;
		down(u, l, r);
		if (L <= md) modify(u << 1, l, md, L, R, w);
		if (R > md) modify(u << 1 | 1, md + 1, r, L, R, w);
		up(u);
	}
	long long query(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return sum[u];
		int md = (l + r) >> 1;
		long long ans = 0;
		down(u, l, r);
		if (L <= md) ans += query(u << 1, l, md, L, R);
		if (R > md) ans += query(u << 1 | 1, md + 1, r, L, R);
		return ans;
	}
}T;
void Modify(int u, int w){
	w -= a[u], a[u] += w, S += w;
	while (u){
		T.modify(1, 1, n, idx[top[u]], idx[u], w);
		u = fa[top[u]];
	}
}
long long Query(int u){
	long long ans = T.sum2[1], k = dep[u] - 1, Sum = 0;
	while (u){
		Sum += T.query(1, 1, n, idx[top[u]], idx[u]);
		u = fa[top[u]];
	}
	Sum -= S;
	return ans + k * S * S - 2 * S * Sum;
}
int main(){
	n = read(), q = read();
	for (register int i = 1, u, v; i < n; ++i) u = read(), v = read(), E[u].push_back(v), E[v].push_back(u);
	for (register int i = 1; i <= n; ++i) a[i] = read(), S += a[i];
	dfs(1), dfs(1, 1);
	T.build(1, 1, n);
	for (register int i = 1; i <= q; ++i){
		int opt = read(), x = read();
		if (opt == 1) Modify(x, read());
		else printf("%lld\n", Query(x));
	}
}
