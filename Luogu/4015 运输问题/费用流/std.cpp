#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 505
#define M 100005
#define INF 0x3f3f3f3f
int n, m, a[N], b[N], c[N][N], S = 0, T;
int edge, to[M], cap[M], cost[M], pr[M], hd[N];
void addedge(int u, int v, int w, int c){
	to[edge] = v, pr[edge] = hd[u], cap[edge] = w, cost[edge] = c, hd[u] = edge++;
	to[edge] = u, pr[edge] = hd[v], cap[edge] = 0, cost[edge] = -c, hd[v] = edge++;
}
int h, t, Q[M << 3], vis[N], dis[N], mn[N], pre[N];
void spfa(){
	memset(dis, 0x3f, sizeof dis), memset(vis, 0, sizeof vis);
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
	scanf("%d%d", &n, &m), T = n + m + 1;
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1; i <= m; ++i) scanf("%d", b + i);
	memset(hd, -1, sizeof hd);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			scanf("%d", &c[i][j]), addedge(i, j + n, INF, c[i][j]);
	for (register int i = 1; i <= n; ++i) addedge(S, i, a[i], 0);
	for (register int i = 1; i <= m; ++i) addedge(i + n, T, b[i], 0);
	printf("%d\n", MCMF());
	memset(hd, -1, sizeof hd);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			addedge(i, j + n, INF, -c[i][j]);
	for (register int i = 1; i <= n; ++i) addedge(S, i, a[i], 0);
	for (register int i = 1; i <= m; ++i) addedge(i + n, T, b[i], 0);
	printf("%d", -MCMF());
	getchar(), getchar();
}