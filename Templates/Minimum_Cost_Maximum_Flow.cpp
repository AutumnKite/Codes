#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 5005
#define M 100005
#define INF 0x3f3f3f3f
int n, m, S, T;
int edge, pr[M], to[M], cap[M], cost[M], hd[N];
void addedge(int u, int v, int w, int c){
	to[edge] = v, cap[edge] = w, cost[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
	to[edge] = u, cap[edge] = 0, cost[edge] = -c, pr[edge] = hd[v], hd[v] = edge++;
}
int h, t, Q[M << 3], dis[N], vis[N], pre[N], mn[N];
void spfa(){
	memset(vis, 0, sizeof vis), memset(dis, 0x3f, sizeof dis);
	h = 0, t = 1, Q[t] = S, dis[S] = 0, vis[S] = 1, pre[S] = 0, mn[S] = INF;
	while (h < t){
		int u = Q[++h]; vis[u] = 0;
		for (register int i = hd[u], v; ~i; i = pr[i])
			if (cap[i] && dis[u] + cost[i] < dis[v = to[i]]){
				dis[v] = dis[u] + cost[i], mn[v] = std :: min(mn[u], cap[i]), pre[v] = i;
				if (!vis[v]) Q[++t] = v, vis[v] = 1;
			}
	}
}
std :: pair<int, int> MinCostMaxFlow(){
	int Cost = 0, Flow = 0;
	while (spfa(), dis[T] != INF){
		Cost += dis[T] * mn[T], Flow += mn[T];
		for (register int p = T; p != S; p = to[pre[p] ^ 1])
			cap[pre[p]] -= mn[T], cap[pre[p] ^ 1] += mn[T];
	}
	return std :: make_pair(Flow, Cost);
}
int main(){
	scanf("%d%d%d%d", &n, &m, &S, &T);
	memset(hd, -1, sizeof hd);
	for (register int i = 1, u, v, w, c; i <= m; ++i)
		scanf("%d%d%d%d", &u, &v, &w, &c), addedge(u, v, w, c);
	std :: pair<int, int> ans = MinCostMaxFlow();
	printf("%d %d\n", ans.first, ans.second);
}