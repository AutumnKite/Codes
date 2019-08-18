#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 205
#define M 100005
#define INF 0x3f3f3f3f
int n, a[N][N], S, T;
int edge, to[M], pr[M], cap[M], cost[M], hd[N];
void addedge(int u, int v, int w, int c){
	to[edge] = v, cap[edge] = w, cost[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
	to[edge] = u, cap[edge] = 0, cost[edge] = -c, pr[edge] = hd[v], hd[v] = edge++;
}
int h, t, Q[M << 3], dis[N], vis[N], mn[N], pre[N];
void spfa(){
	memset(vis, 0, sizeof vis), memset(dis, 0x3f, sizeof dis);
	h = 0, t = 1, Q[t] = S, dis[S] = 0, vis[S] = 1, pre[S] = 0, mn[S] = INF;
	while (h < t){
		int u = Q[++h]; vis[u] = 0;
		for (register int i = hd[u], v; ~i; i = pr[i])
			if (cap[i] && dis[u] + cost[i] < dis[v = to[i]]){
				dis[v] = dis[u] + cost[i];
				mn[v] = std :: min(mn[u], cap[i]), pre[v] = i;
				if (!vis[v]) Q[++t] = v, vis[v] = 1;
			}
	}
}
int MCMF(){
	int ans = 0;
	while (spfa(), dis[T] != INF){
		ans += dis[T] * mn[T];
		for (register int i = T; i != S; i = to[pre[i] ^ 1])
			cap[pre[i]] -= mn[T], cap[pre[i] ^ 1] += mn[T];
	}
	return ans;
}
int main(){
	scanf("%d", &n), S = 0, T = n + n + 1;
	memset(hd, -1, sizeof hd);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= n; ++j)
			scanf("%d", &a[i][j]), addedge(i, j + n, 1, a[i][j]);
	for (register int i = 1; i <= n; ++i) addedge(S, i, 1, 0);
	for (register int i = 1; i <= n; ++i) addedge(i + n, T, 1, 0);
	printf("%d\n", MCMF());
	memset(hd, -1, sizeof hd);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= n; ++j)
			addedge(i, j + n, 1, -a[i][j]);
	for (register int i = 1; i <= n; ++i) addedge(S, i, 1, 0);
	for (register int i = 1; i <= n; ++i) addedge(i + n, T, 1, 0);
	printf("%d", -MCMF());
}