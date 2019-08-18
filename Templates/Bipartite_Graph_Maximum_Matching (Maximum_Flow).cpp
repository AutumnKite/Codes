#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 105
#define M 100005
#define INF 1000000000
int n, m, x, y;
namespace MaxFlow{
	int S, T, edge, to[M], cap[M], pr[M], hd[N];
	int dep[N], h, t, Q[N];
	void addedge(int u, int v, int c){
		to[edge] = v, cap[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
		to[edge] = u, cap[edge] = 0, pr[edge] = hd[v], hd[v] = edge++;
	}
	int dfs(int u, int flow){
		if (u == T || !flow) return flow;
		int ret = 0;
		for (register int i = hd[u], v, f; ~i; i = pr[i])
			if (dep[v = to[i]] == dep[u] + 1 && (f = dfs(v, std :: min(flow, cap[i])))){
				ret += f, flow -= f, cap[i] -= f, cap[i ^ 1] += f;
				if (!flow) break;
			}
		if (!ret) dep[u] = -1;
		return ret;
	}
	int bfs(){
		memset(dep, -1, sizeof dep);
		h = 0, t = 1, Q[t] = S, dep[S] = 0;
		while (h < t){
			int u = Q[++h];
			for (register int i = hd[u], v; ~i; i = pr[i])
				if (dep[v = to[i]] == -1 && cap[i]){
					dep[v] = dep[u] + 1;
					if (v == T) return 1;
					Q[++t] = v;
				}
		}
		return 0;
	}
	int dinic(){
		int ans = 0;
		while (bfs()) ans += dfs(S, INF);
		return ans;
	}
}
using namespace MaxFlow;
int main(){
	scanf("%d%d", &m, &n);
	memset(hd, -1, sizeof hd), S = 0, T = n + 1;
	while (scanf("%d%d", &x, &y), ~x) addedge(x, y, 1);
	for (register int i = 1; i <= m; ++i) addedge(S, i, 1);
	for (register int i = m + 1; i <= n; ++i) addedge(i, T, 1);
	printf("%d\n", dinic());
	for (register int i = m + 1; i <= n; ++i)
		for (register int j = hd[i]; ~j; j = pr[j])
			if (cap[j] && to[j] != T) printf("%d %d\n", to[j], i);
	getchar(), getchar();
}