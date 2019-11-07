#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0, f = 1;
	register char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 10005;
int n, m, b[N];
std :: vector<int> E[N];
struct node{
	int u, v, id;
	node(){}
	node(int _u, int _v, int _id){
		u = _u, v = _v, id = _id;
		if (u > v) std :: swap(u, v);
	}
};
std :: vector<node> ed;
std :: vector< std :: pair<int, int> > ans;
void color(int u, int d){
	b[u] = d, d ^= 1;
	for (int v : E[u]) if (b[v] == -1) color(v, d);
}
namespace Graph{
	const int N = 10005, M = 300005, INF = 0x3f3f3f3f;
	int S, T, n, edge, to[M], pr[M], cap[M], hd[N], nhd[N];
	void init(int _n){
		n = _n, edge = 0;
		for (register int i = 0; i < n; ++i) hd[i] = -1;
	}
	void addedge(int u, int v, int c){
		to[edge] = v, cap[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
		to[edge] = u, cap[edge] = 0, pr[edge] = hd[v], hd[v] = edge++;
	}
	int h, t, Q[N], dep[N];
	bool bfs(){
		for (register int i = 0; i < n; ++i) dep[i] = -1;
		h = 0, t = 1, Q[t] = S, dep[S] = 0;
		while (h < t)
			for (register int u = Q[++h], i = hd[u], v; ~i; i = pr[i])
				if (cap[i] && dep[v = to[i]] == -1){
					dep[v] = dep[u] + 1;
					if (v == T) return 1;
					Q[++t] = v;
				}
		return 0;
	}
	int dfs(int u, int flow){
		if (u == T || !flow) return flow;
		int res = 0, tmp;
		for (register int i = nhd[u], v; ~i; nhd[u] = i = pr[i])
			if (dep[v = to[i]] == dep[u] + 1 && (tmp = dfs(v, std :: min(flow, cap[i])))){
				flow -= tmp, res += tmp, cap[i] -= tmp, cap[i ^ 1] += tmp;
				if (!flow) break;
			}
		if (!res) dep[u] = -1;
		return res;
	}
	int dinic(int _S, int _T){
		S = _S, T = _T;
		int res = 0;
		while (bfs()){
			for (register int i = 0; i < n; ++i) nhd[i] = hd[i];
			res += dfs(S, INF);
		}
		return res;
	}
	int idx, dfn[N], low[N], tp, sta[N], vis[N], cnt, col[N];
	void dfs(int u){
		dfn[u] = low[u] = ++idx, vis[sta[++tp] = u] = 1;
		for (register int i = hd[u], v; ~i; i = pr[i])
			if (cap[i])
				if (!dfn[v = to[i]]) dfs(v), low[u] = std :: min(low[u], low[v]);
				else if (vis[v]) low[u] = std :: min(low[u], dfn[v]);
		if (dfn[u] == low[u]){
			sta[tp + 1] = -1, ++cnt;
			while (sta[tp + 1] != u) col[sta[tp]] = cnt, vis[sta[tp--]] = 0;
		}
	}
	void tarjan(){
		for (register int i = 0; i < n; ++i) if (!dfn[i]) dfs(i);
	}
}
int main(){
	n = read(), m = read();
	for (register int i = 1, u, v; i <= m; ++i)
		u = read(), v = read(), E[u].push_back(v), E[v].push_back(u);
	for (register int i = 1; i <= n; ++i) b[i] = -1;
	for (register int i = 1; i <= n; ++i)
		if (b[i] == -1) color(i, 0);
	Graph :: init(n + 2);
	for (register int i = 1; i <= n; ++i)
		if (b[i] == 0) Graph :: addedge(0, i, 1);
		else Graph :: addedge(i, n + 1, 1);
	for (register int i = 1; i <= n; ++i)
		for (int j : E[i])
			if (b[i] == 0 && b[j] == 1)
				ed.push_back(node(i, j, Graph :: edge)), Graph :: addedge(i, j, 1);
	Graph :: dinic(0, n + 1);
	Graph :: tarjan();
	for (node e : ed)
		if (!Graph :: cap[e.id] && Graph :: col[e.u] != Graph :: col[e.v])
			ans.push_back(std :: make_pair(e.u, e.v));
	std :: sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for (auto v : ans) printf("%d %d\n", v.first, v.second);
}