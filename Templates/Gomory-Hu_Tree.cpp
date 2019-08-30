#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 505
#define M 3005
#define INF 0x3f3f3f3f
int n, m, q;
struct Graph{
	int S, T, edge, to[M], cap[M], Cap[M], pr[M], hd[N], nhd[N];
	Graph(){
		edge = 0, memset(hd, -1, sizeof hd);
	}
	void addedge(int u, int v, int c){
		to[edge] = v, Cap[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
		to[edge] = u, Cap[edge] = c, pr[edge] = hd[v], hd[v] = edge++; // The graph is undirected.
	}
	int dep[N], h, t, Q[N];
	int dfs(int u, int flow){
		if (u == T || !flow) return flow;
		int ans = 0;
		for (register int i = nhd[u], v, tmp; ~i; nhd[u] = i = pr[i])
			if (dep[v = to[i]] == dep[u] + 1 && (tmp = dfs(v, std :: min(flow, cap[i])))){
				ans += tmp, flow -= tmp, cap[i] -= tmp, cap[i ^ 1] += tmp;
				if (!flow) break;
			}
		if (!ans) dep[u] = -1;
		return ans;
	}
	int bfs(){
		memset(dep, -1, sizeof dep);
		h = 0, t = 1, Q[t] = S, dep[S] = 0;
		while (h < t){
			int u = Q[++h];
			for (register int i = hd[u], v; ~i; i = pr[i])
				if (dep[v = to[i]] == -1 && cap[i]){
					Q[++t] = v, dep[v] = dep[u] + 1;
					if (v == T) return 1;
				}
		}
		return 0;
	}
	int MaxFlow(int _S, int _T){
		S = _S, T = _T, memcpy(cap, Cap, sizeof cap);
		int ans = 0;
		while (bfs()) memcpy(nhd, hd, sizeof nhd), ans += dfs(S, INF);
		return ans;
	}
}G;
struct Gomory_Hu_Tree{
	int edge, to[N << 1], tw[N << 1], pr[N << 1], hd[N];
	void addedge(int u, int v, int w){
		to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
	}
	void build(std :: vector<int> A){
		if (A.size() <= 1) return;
		int u = A[0], v = A[1], w = G.MaxFlow(u, v);
		addedge(u, v, w);
		std :: vector<int> A1, A2;
		for (register int i = 0; i < A.size(); ++i)
			if (~G.dep[A[i]]) A1.push_back(A[i]);
			else A2.push_back(A[i]);
		build(A1), build(A2);
	}
	int fa[N][10], mn[N][10], dep[N];
	void dfs(int u){
		dep[u] = dep[fa[u][0]] + 1;
		for (register int i = 1; i <= 9; ++i)
			fa[u][i] = fa[fa[u][i - 1]][i - 1], mn[u][i] = std :: min(mn[u][i - 1], mn[fa[u][i - 1]][i - 1]);
		for (register int i = hd[u], v; i; i = pr[i])
			if ((v = to[i]) != fa[u][0]) fa[v][0] = u, mn[v][0] = tw[i], dfs(v);
	}
	int query(int u, int v){
		if (dep[u] < dep[v]) std :: swap(u, v);
		int ans = INF;
		for (register int i = 9; ~i; --i)
			if (dep[fa[u][i]] >= dep[v])
				ans = std :: min(ans, mn[u][i]), u = fa[u][i];
		if (u == v) return ans;
		for (register int i = 9; ~i; --i)
			if (fa[u][i] != fa[v][i])
				ans = std :: min(ans, std :: min(mn[u][i], mn[v][i])), u = fa[u][i], v = fa[v][i];
		ans = std :: min(ans, std :: min(mn[u][0], mn[v][0]));
		return ans;
	}
}T;
int main(){
	n = read(), m = read();
	for (register int i = 1, u, v, w; i <= m; ++i)
		u = read(), v = read(), w = read(), G.addedge(u, v, w);
	std :: vector<int> A;
	for (register int i = 0; i <= n; ++i) A.push_back(i);
	T.build(A);
	T.dfs(0);
	q = read();
	while (q--){
		int u = read(), v = read();
		printf("%d\n", T.query(u, v));
	}
}
