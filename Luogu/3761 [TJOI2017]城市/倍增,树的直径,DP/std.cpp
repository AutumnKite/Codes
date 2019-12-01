#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 1000005;
int n, LOG;
struct node{
	long long w;
	int v;
	bool operator < (const node &rhs) const { return w < rhs.w; }
};
struct dnode{
	long long w;
	int u, v;
	bool operator < (const node &rhs) const { return w < rhs.w; }
};
dnode operator + (const node &a, const node &b){
	return (dnode){a.w + b.w, a.v, b.v};
}
std :: vector<node> E[N];
int dep[N], fa[N][20];
long long sum[N];
void init(int u){
	dep[u] = dep[fa[u][0]] + 1;
	for (register int i = LOG; ~i; --i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (node p : E[u])
		if (p.v != fa[u][0]) fa[p.v][0] = u, sum[p.v] = sum[u] + p.w, init(p.v);
}
int LCA(int u, int v){
	if (dep[u] < dep[v]) std :: swap(u, v);
	for (register int i = LOG; ~i; --i)
		if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if (u == v) return u;
	for (register int i = LOG; ~i; --i)
		if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
int getmd(int u, int v){
	int lca = LCA(u, v);
	long long su = sum[u] - sum[lca], sv = sum[v] - sum[lca], r = (su + sv) >> 1;
	if (su < sv) std :: swap(u, v), std :: swap(su, sv);
	int x = u;
	for (register int i = LOG; ~i; --i)
		if (sum[u] - sum[fa[x][i]] <= r) x = fa[x][i];
	if (x == lca) return 
}
node mx[N], cmx[N], ccmx[N];
dnode dmx[N];
void dfs1(int u){
	mx[u] = cmx[u] = ccmx[u] = {0, u}, dmx[u] = mx[u] + cmx[u];
	node tmp;
	for (node p : E[u])
		if (p.v != fa[u][0]){
			dfs1(p.v), tmp = mx[p.v], tmp.w += p.w;
			if (mx[u] < tmp) mx[u] = tmp;
			else if (cmx[u] < tmp) cmx[u] = tmp;
			else if (ccmx[u] < tmp) ccmx[u] = tmp;
			dmx[u] = std :: max(dmx[u], dmx[p.v]);
		}
	dmx[u] = std :: max(dmx[u], mx[u] + cmx[u]);
}
void dfs2(int u){
	mx[u] = 
}
int main(){
	n = read(), LOG = -1;
	int tn = n;
	while (tn) tn >>= 1, ++LOG;
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), E[u].push_back({w, v}), E[v].push_back({w, u});
	init(1);
}