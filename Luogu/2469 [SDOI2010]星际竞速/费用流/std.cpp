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
struct Graph{
	static const int N = 2005, M = 50005, INF = 0x3f3f3f3f;
	int S, T, edge, to[M], cap[M], cost[M], pr[M], hd[N];
	Graph(){
		edge = 0, memset(hd, -1, sizeof hd);
	}
	void addedge(int u, int v, int w, int c){
		to[edge] = v, cap[edge] = w, cost[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
		to[edge] = u, cap[edge] = 0, cost[edge] = -c, pr[edge] = hd[v], hd[v] = edge++;
	}
	int h, t, Q[1000005], dis[N], mn[N], vis[N], pre[N];
	void spfa(){
		memset(vis, 0, sizeof vis);
		memset(dis, 0x3f, sizeof dis);
		h = 0, t = 1, Q[t] = S, dis[S] = 0, vis[S] = 1, pre[S] = 0, mn[S] = INF;
		while (h < t){
			int u = Q[++h];
			vis[u] = 0;
			for (register int i = hd[u], v; ~i; i = pr[i])
				if (cap[i] && dis[u] + cost[i] < dis[v = to[i]]){
					dis[v] = dis[u] + cost[i], mn[v] = std :: min(mn[u], cap[i]), pre[v] = i;
					if (!vis[v]) Q[++t] = v, vis[v] = 1;
				}
		}
	}
	int MCMF(){
		int ans = 0;
		while (spfa(), dis[T] != INF){
			ans += dis[T];
			for (register int p = T; p != S; p = to[pre[p] ^ 1])
				cap[pre[p]] -= mn[T], cap[pre[p] ^ 1] += mn[T];
		}
		return ans;
	}
}G;
int n, m;
int main(){
	n = read(), m = read();
	G.S = 1, G.T = 2;
	for (register int i = 1; i <= n; ++i)
		G.addedge(G.S, i + 2, 1, 0), G.addedge(n + i + 2, G.T, 1, 0);
	for (register int i = 1, w; i <= n; ++i)
		w = read(), G.addedge(G.S, n + i + 2, 1, w);
	for (register int i = 1, u, v, w; i <= m; ++i){
		u = read(), v = read(), w = read();
		if (u > v) std :: swap(u, v);
		G.addedge(u + 2, n + v + 2, 1, w);
	}
	printf("%d", G.MCMF());
}
