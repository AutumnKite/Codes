#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 2000005
int n, m, h[N], fa[N], cnt;
int edge, to[N], tw[N], pr[N], hd[N], vis[N];
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
}
struct node{
	int u, v, w;
	bool operator < (const node &res) const {
		return h[v] > h[res.v] || h[v] == h[res.v] && w < res.w;
	}
}E[N];
void dfs(int u){
	++cnt, vis[u] = 1;
	for (register int i = hd[u], v; i; i = pr[i]){
		if (!vis[v = to[i]]) dfs(v);
		E[++m] = (node){u, v, tw[i]};
	}
}
int find(int x){
	return x == fa[x] ? x : (fa[x] = find(fa[x]));
}
int merge(int x, int y){
	int fx = find(x), fy = find(y);
	if (fx == fy) return 0;
	return fa[fy] = fx, 1;
}
long long Kruskal(){
	std :: sort(E + 1, E + 1 + m);
	for (register int i = 1; i <= n; ++i) fa[i] = i;
	long long ans = 0;
	int sum = 0;
	for (register int i = 1; i <= m; ++i){
		if (merge(E[i].u, E[i].v)) ans += E[i].w, ++sum;
		if (sum == cnt - 1) break;
	}
	return ans;
}
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) h[i] = read();
	for (register int i = 1; i <= m; ++i){
		int u = read(), v = read(), w = read();
		if (h[u] >= h[v]) addedge(u, v, w);
		if (h[v] >= h[u]) addedge(v, u, w);
	}
	m = 0, dfs(1);
	printf("%d %lld", cnt, Kruskal());
}