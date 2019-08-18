#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 1005
#define INF 0x3f3f3f3f
int n, m, a[N], S = 0, T;
int edge, to[N], pr[N], cap[N], cost[N], hd[N];
int dis[N], h, t, Q[N << 5], vis[N], mn[N], pre[N];
void addedge(int u, int v, int w, int c){
	to[edge] = v, pr[edge] = hd[u], cap[edge] = w, cost[edge] = c, hd[u] = edge++;
	to[edge] = u, pr[edge] = hd[v], cap[edge] = 0, cost[edge] = -c, hd[v] = edge++;
}
void spfa(){
	memset(dis, 0x3f, sizeof dis), memset(vis, 0, sizeof vis);
	h = 0, t = 1, Q[t] = S, dis[S] = 0, vis[S] = 1, pre[S] = 0, mn[S] = INF;
	while (h < t){
		int u = Q[++h]; vis[u] = 0;
		for (register int i = hd[u], v; ~i; i = pr[i])
			if (cap[i] && dis[v = to[i]] > dis[u] + cost[i]){
				dis[v] = dis[u] + cost[i], mn[v] = std :: min(mn[u], cap[i]), pre[v] = i;
				if (!vis[v]) vis[v] = 1, Q[++t] = v;
			}
	}
}
int MinCostMaxFlow(){
	int Cost = 0;
	while (spfa(), dis[T] != INF){
		Cost += dis[T] * mn[T];
		for (register int i = T; i != S; i = to[pre[i] ^ 1])
			cap[pre[i]] -= mn[T], cap[pre[i] ^ 1] += mn[T];
	}
	return Cost;
}
int main(){
	scanf("%d", &n), T = n + 1;
	for (register int i = 1; i <= n; ++i)
		scanf("%d", a + i), m += a[i];
	m /= n, memset(hd, -1, sizeof hd);
	for (register int i = 1; i <= n; ++i){
		addedge(i, i == 1 ? n : i - 1, INF, 1);
		addedge(i, i == n ? 1 : i + 1, INF, 1);
		if (a[i] < m) addedge(S, i, m - a[i], 0);
		else addedge(i, T, a[i] - m, 0);
	}
	printf("%d", MinCostMaxFlow());
}