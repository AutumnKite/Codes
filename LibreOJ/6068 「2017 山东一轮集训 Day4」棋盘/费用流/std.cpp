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
struct Graph{
	const static int N = 5005, M = 100005, INF = 0x3f3f3f3f;
	int S, T, edge, to[M], pr[M], cap[M], cost[M], hd[N];
	Graph(){ edge = 0, memset(hd, -1, sizeof hd); }
	void addedge(int u, int v, int w, int c){
		to[edge] = v, cap[edge] = w, cost[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
		to[edge] = u, cap[edge] = 0, cost[edge] = -c, pr[edge] = hd[v], hd[v] = edge++;
	}
	int h, t, Q[1000005], dis[N], vis[N], mn[N], pre[N];
	bool SPFA(){
		memset(dis, 0x3f, sizeof dis), memset(vis, 0, sizeof vis);
		h = 0, t = 1, Q[t] = S, dis[S] = 0, vis[S] = 1, pre[S] = 0, mn[S] = INF;
		while (h < t){
			int u = Q[++h]; vis[u] = 0;
			for (register int i = hd[u], v; ~i; i = pr[i])
				if (cap[i] && dis[u] + cost[i] < dis[v = to[i]]){
					dis[v] = dis[u] + cost[i], mn[v] = std :: min(mn[u], cap[i]), pre[v] = i;
					if (!vis[v]) Q[++t] = v, vis[v] = 1;
				}
		}
		return dis[T] != INF;
	}
	std :: vector<int> MinCostMaxFlow(int _S, int _T){
		std :: vector<int> res;
		res.push_back(0), S = _S, T = _T;
		while (SPFA()){
			res.push_back(res[res.size() - 1] + dis[T]);
			for (register int i = T; i != S; i = to[pre[i] ^ 1])
				cap[pre[i]] -= mn[T], cap[pre[i] ^ 1] += mn[T];
		}
		return res;
	}
}G;
int n, q, cnt, cntr, cntc, rbel[55][55], cbel[55][55], sz[5005];
char a[55][55];
std :: vector<int> ans;
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) scanf("%s", a[i] + 1);
	cntr = 1;
	for (register int i = 1; i <= n; ++i){
		if (sz[cntr]) ++cntr;
		for (register int j = 1; j <= n; ++j)
			if (a[i][j] == '.') rbel[i][j] = cntr, ++sz[cntr];
			else if (sz[cntr]) ++cntr;
	}
	cntc = cntr + 1;
	for (register int i = 1; i <= n; ++i){
		if (sz[cntc]) ++cntc;
		for (register int j = 1; j <= n; ++j)
			if (a[j][i] == '.') cbel[j][i] = cntc, ++sz[cntc];
			else if (sz[cntc]) ++cntc;
	}
	for (register int i = 1; i <= cntr; ++i)
		for (register int j = 0; j < sz[i]; ++j)
			G.addedge(0, i, 1, j);
	for (register int i = cntr + 1; i <= cntc; ++i)
		for (register int j = 0; j < sz[i]; ++j)
			G.addedge(i, cntc + 1, 1, j);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= n; ++j)
			if (a[i][j] == '.') G.addedge(rbel[i][j], cbel[i][j], 1, 0);
	ans = G.MinCostMaxFlow(0, cntc + 1);
	q = read();
	while (q--) printf("%d\n", ans[read()]);
}
