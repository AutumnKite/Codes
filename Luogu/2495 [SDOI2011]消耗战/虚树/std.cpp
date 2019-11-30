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
void print(long long x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 250005;
int n, q;
int idx, dfn[N], dep[N], fa[N][19], fw[N][19];
std :: vector< std :: pair<int, int> > E[N];
void dfs(int u){
	dfn[u] = ++idx, dep[u] = dep[fa[u][0]] + 1;
	for (register int i = 1; i <= 18; ++i)
		fa[u][i] = fa[fa[u][i - 1]][i - 1], fw[u][i] = std :: min(fw[u][i - 1], fw[fa[u][i - 1]][i - 1]);
	for (auto [v, w] : E[u])
		if (v != fa[u][0]) fa[v][0] = u, fw[v][0] = w, dfs(v);
}
int LCA(int u, int v){
	if (dep[u] < dep[v]) std :: swap(u, v);
	for (register int i = 18; ~i; --i)
		if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if (u == v) return u;
	for (register int i = 18; ~i; --i)
		if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
int pmin(int u, int v){
	int mn = 1e9;
	for (register int i = 18; ~i; --i)
		if (dep[fa[u][i]] >= dep[v]) mn = std :: min(mn, fw[u][i]), u = fa[u][i];
	return mn;
}
int k, p[N], vis[N], top, sta[N];
void insert(int u){
	if (!top) return sta[++top] = u, void(0);
	int x = sta[top], lca = LCA(x, u), y;
	if (lca == x) return sta[++top] = u, void(0);
	while (top > 1 && dfn[y = sta[top - 1]] > dfn[lca])
		E[y].push_back({x, pmin(x, y)}), x = sta[--top];
	E[lca].push_back({x, pmin(x, lca)}), --top;
	if (!top || sta[top] != lca) sta[++top] = lca;
	sta[++top] = u;
}
long long DP(int u, long long mn = 1e18){
	long long sum = 0;
	for (auto [v, w] : E[u]) sum += DP(v, std :: min(mn, 1ll * w));
	E[u].clear();
	if (vis[u]) return mn;
	return std :: min(sum, mn);
}
int main(){
	n = read();
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), E[u].push_back({v, w}), E[v].push_back({u, w});
	dfs(1);
	for (register int i = 1; i <= n; ++i) E[i].clear();
	q = read();
	while (q--){
		k = read() + 1, p[0] = 1;
		for (register int i = 1; i < k; ++i) p[i] = read(), vis[p[i]] = 1;
		std :: sort(p, p + k, [=](int u, int v){
			return dfn[u] < dfn[v];
		});
		top = 0;
		for (register int i = 0; i < k; ++i) insert(p[i]);
		while (top > 1) E[sta[top - 1]].push_back({sta[top], pmin(sta[top], sta[top - 1])}), --top;
		print(DP(sta[1]));
		for (register int i = 0; i < k; ++i) vis[p[i]] = 0;
	}
}