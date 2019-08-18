#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
#define N 400005
int n, m, a[N], b[N];
struct Segment_Tree{
	int cnt, ls[N * 20], rs[N * 20], a[N * 20], pos[N * 20];
	void insert(int &u, int l, int r, int x, int y){
		if (!u) u = ++cnt;
		if (l == r) return a[u] += y, pos[u] = l, void(0);
		int md = (l + r) >> 1;
		if (x <= md) insert(ls[u], l, md, x, y);
		else insert(rs[u], md + 1, r, x, y);
		a[u] = std :: max(a[ls[u]], a[rs[u]]);
		if (a[u] == a[ls[u]]) pos[u] = pos[ls[u]]; else pos[u] = pos[rs[u]];
	}
	void merge(int &x, int y){
		if (!x || !y) return x += y, void(0);
		if (!ls[x] && !rs[x]) return a[x] += a[y], void(0);
		merge(ls[x], ls[y]), merge(rs[x], rs[y]);
		a[x] = std :: max(a[ls[x]], a[rs[x]]);
		if (a[x] == a[ls[x]]) pos[x] = pos[ls[x]]; else pos[x] = pos[rs[x]];
	}
}T;
std :: vector<int> E[N];
int rt[N];
void dfs(int u, int fa = 0){
	T.insert(rt[u], 1, m, a[u], b[u]);
	for (register int i = 0, v; i < E[u].size(); ++i)
		if ((v = E[u][i]) != fa) dfs(v, u), T.merge(rt[u], rt[v]);
}
int main(){
	n = read(), m = read();
	for (register int i = 1, u, v; i < n; ++i)
		u = read(), v = read(), E[u].push_back(v), E[v].push_back(u);
	for (register int i = 1; i <= n; ++i) a[i] = read(), b[i] = read();
	dfs(1);
	for (register int i = 1; i <= n; ++i) printf("%d %d\n", T.pos[rt[i]], T.a[rt[i]]);
}
