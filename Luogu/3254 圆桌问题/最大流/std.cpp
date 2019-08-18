#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 505
#define M 100005
#define INF 0x3f3f3f3f
int n, m, S, T, sum, a[N], b[N];
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
			ret += f, flow -= f, cap[i] -= f, cap[i ^ 1] += f;
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
	memset(hd, -1, sizeof hd);
	scanf("%d%d", &n, &m), S = 0, T = n + m + 1;
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i), sum += a[i];
	for (register int i = 1; i <= m; ++i) scanf("%d", b + i);
	for (register int i = 1; i <= n; ++i) addedge(S, i, a[i]);
	for (register int i = n + 1; i <= n + m; ++i) addedge(i, T, b[i - n]);
	for (register int i = 1; i <= n; ++i)
		for (register int j = n + 1; j <= n + m; ++j)
			addedge(i, j, 1);
	if (dinic() < sum) return printf("0"), 0;
	printf("1\n");
	for (register int i = 1; i <= n; ++i){
		for (register int j = hd[i]; ~j; j = pr[j])
			if (!cap[j]) printf("%d ", to[j] - n);
		putchar('\n');
	}
}