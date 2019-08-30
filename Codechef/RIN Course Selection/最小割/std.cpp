#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define INF 0x3f3f3f3f
struct Graph{
	static const int N = 15005, M = 100005;
	int S, T, edge, to[M], cap[M], pr[M], hd[N], nhd[N];
	Graph(){
		edge = 0, memset(hd, -1, sizeof hd);
	}
	void addedge(int u, int v, int c){
		to[edge] = v, cap[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
		to[edge] = u, cap[edge] = 0, pr[edge] = hd[v], hd[v] = edge++;
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
	int MaxFlow(){
		int ans = 0;
		while (bfs()) memcpy(nhd, hd, sizeof nhd), ans += dfs(S, INF);
		return ans;
	}
}G;
int n, m, k, a[105], sum;
int main(){
	n = read(), m = read(), k = read();
	G.S = 0, G.T = n * (m + 1) + 1;
	for (register int i = 1; i <= n; ++i)
		G.addedge(G.S, (i - 1) * (m + 1) + 1, INF), G.addedge(i * (m + 1), G.T, INF);
	for (register int i = 1; i <= n; ++i){
		int s = 0;
		for (register int j = 1; j <= m; ++j) s += a[j] = read();
		for (register int j = 1; j <= m; ++j)
			if (~a[j]) G.addedge((i - 1) * (m + 1) + j, (i - 1) * (m + 1) + j + 1, s - a[j]);
			else G.addedge((i - 1) * (m + 1) + j, (i - 1) * (m + 1) + j + 1, INF);
		sum += s;
	}
	for (register int i = 1; i <= k; ++i){
		int u = read(), v = read();
		for (register int j = 1; j <= m; ++j)
			G.addedge((u - 1) * (m + 1) + j, (v - 1) * (m + 1) + j + 1, INF);
	}
	printf("%.2lf", 1.0 * (sum - G.MaxFlow()) / n);
}
