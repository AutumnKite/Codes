#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 505
#define M 100005
#define INF 1000000000
int n, m, S, T;
int edge, to[M], pr[M], cap[M], hd[N];
int dep[N], h, t, Q[N];
void addedge(int u, int v, int c){
	to[edge] = v, cap[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
	to[edge] = u, cap[edge] = 0, pr[edge] = hd[v], hd[v] = edge++;
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
int dfs(int u, int flow){
	if (u == T || !flow) return flow;
	int ret = 0;
	for (register int i = hd[u], v, f; ~i; i = pr[i])
		if (dep[v = to[i]] == dep[u] + 1 && (f = dfs(v, std :: min(flow, cap[i])))){
			ret += f, flow -= f, cap[i] += f, cap[i ^ 1] -= f;
			if (!flow) break;
		}
	if (!ret) dep[u] = -1;
	return ret;
}
int dinic(){
	int ans = 0;
	while (bfs()) ans += dfs(S, INF);
	return ans;
}
int main(){
	scanf("%d%d", &n, &m), S = 0, T = n + m + 1;
	for (register int i = 1; i <= n; ++i){
		int s; scanf("%d", &s);
		for (register int j = 1, x; j <= s; ++j) 
			scanf("%d", &x), addedge(i, x + n, 1);
	}
	for (register int i = 1; i <= n; ++i) addedge(S, i, 1);
	for (register int i = 1; i <= m; ++i) addedge(i + n, T, 1);
	printf("%d", dinic());
}