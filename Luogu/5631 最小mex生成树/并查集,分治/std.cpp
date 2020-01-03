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
int n, m, mx, ans;
std::vector< std::pair<int, int> > E[100005];
struct DSU{
	static const int N = 1000005;
	int fa[N], sz[N], tp, sta[N];
	void init(int n){
		for (register int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1;
	}
	int find(int x){ return fa[x] == x ? x : find(fa[x]); }
	void merge(int x, int y){
		x = find(x), y = find(y);
		if (x == y) return;
		if (sz[x] > sz[y]) std::swap(x, y);
		fa[x] = y, sz[y] += sz[x], sta[++tp] = x;
	}
	void undo(){
		int x = sta[tp--], y = fa[x];
		fa[x] = x, sz[y] -= sz[x];
	}
}D;
bool solve(int l, int r){
	if (D.tp == n - 1) return ans = l, 1;
	if (l == r) return 0;
	int md = (l + r) >> 1;
	int _tp = D.tp;
	for (register int i = md + 1; i <= r; ++i)
		for (auto v : E[i]) D.merge(v.first, v.second);
	if (solve(l, md)) return 1;
	while (D.tp > _tp) D.undo();
	for (register int i = l; i <= md; ++i)
		for (auto v : E[i]) D.merge(v.first, v.second);
	if (solve(md + 1, r)) return 1;
	while (D.tp > _tp) D.undo();
	return 0;
}
int main(){
	n = read(), m = read();
	for (register int i = 1, u, v, w; i <= m; ++i)
		u = read(), v = read(), w = read(), E[w].push_back({u, v}), mx = std::max(mx, w);
	D.init(n);
	solve(0, mx + 1);
	printf("%d\n", ans);
}