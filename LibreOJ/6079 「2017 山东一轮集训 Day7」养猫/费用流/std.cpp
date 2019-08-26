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
	const static int N = 2005, M = 10005, INF = 0x3f3f3f3f;
	int S, T, edge, to[M], pr[M], cap[M], cost[M], hd[N];
	Graph(){ edge = 0, memset(hd, -1, sizeof hd); }
	void addedge(int u, int v, int w, int c){
		to[edge] = v, cap[edge] = w, cost[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
		to[edge] = u, cap[edge] = 0, cost[edge] = -c, pr[edge] = hd[v], hd[v] = edge++;
	}
	int h, t, Q[1000005], vis[N], mn[N], pre[N];
	long long dis[N];
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
		return dis[T] != dis[N - 1];
	}
	long long MinCostMaxFlow(int _S, int _T){
		long long res = 0;
		S = _S, T = _T;
		while (SPFA()){
			res += mn[T] * dis[T];
			for (register int i = T; i != S; i = to[pre[i] ^ 1])
				cap[pre[i]] -= mn[T], cap[pre[i] ^ 1] += mn[T];
		}
		return res;
	}
}G;
int n, k, ms, me, a[1005], E[1005];
long long sum;
int main(){
	n = read(), k = read(), ms = read(), me = read();
	for (register int i = 1; i <= n; ++i) a[i] = read(), sum += a[i];
	for (register int i = 1; i <= n; ++i) a[i] -= read();
	for (register int i = 1; i <= n; ++i){
		G.addedge(i, i + 1, k - ms - me, 0);
		E[i] = G.edge;
		G.addedge(i, std :: min(i + k, n + 1), 1, a[i]);
	}
	for (register int i = 1; i <= k; ++i) G.addedge(0, i, Graph :: INF, 0);
	G.addedge(n + 2, 0, k - ms, 0);
	printf("%lld\n", sum - G.MinCostMaxFlow(n + 2, n + 1));
	for (register int i = 1; i <= n; ++i)
		if (G.cap[E[i]]) putchar('S'); else putchar('E');
}
