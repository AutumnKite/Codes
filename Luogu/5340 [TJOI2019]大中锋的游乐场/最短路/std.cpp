#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <queue>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
const long long INF = 0x3f3f3f3f3f3f3f3fll;
int n, m, k, a[10005];
namespace Graph{
	const int N = 200005, M = 4000005;
	int n, edge, to[M], tw[M], pr[M], hd[N];
	bool vis[N];
	long long dis[N];
	struct node{
		long long d;
		int u;
		bool operator < (const node &rhs) const { return d > rhs.d; }
	};
	std :: priority_queue<node> Q;
	void init(int _n){
		n = _n, edge = 0;
		for (register int i = 1; i <= n; ++i) hd[i] = 0;
	}
	void addedge(int u, int v, int w){
		to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
	}
	void Dijkstra(int s){
		for (register int i = 1; i <= n; ++i) dis[i] = INF, vis[i] = 0;
		dis[s] = 0, Q.push((node){0, s});
		while (!Q.empty()){
			int u = Q.top().u; Q.pop();
			if (vis[u]) continue;
			vis[u] = 1;
			for (register int i = hd[u], v; i; i = pr[i])
				if (!vis[v = to[i]] && dis[v] > dis[u] + tw[i])
					dis[v] = dis[u] + tw[i], Q.push((node){dis[v], v});
		}
	}
	void print(){
		for (register int i = 1; i <= n; ++i)
			for (register int j = hd[i]; j; j = pr[j])
				printf("%d %d %d\n", i, to[j], tw[j]);
	}
}
int id(int i, int j){ return (i - 1) * (k << 1 | 1) + j + k + 1; }
void addedge(int u, int v, int w){
	if (a[v] == 1) for (register int i = -k; i < k; ++i) Graph :: addedge(id(u, i), id(v, i + 1), w);
	else for (register int i = k; i > -k; --i) Graph :: addedge(id(u, i), id(v, i - 1), w);
}
void solve(){
	n = read(), m = read(), k = read(), Graph :: init(n * (k << 1 | 1));
	for (register int i = 1; i <= n; ++i) a[i] = read() == 1 ? 1 : -1;
	for (register int i = 1, u, v, w; i <= m; ++i){
		u = read(), v = read(), w = read();
		addedge(u, v, w), addedge(v, u, w);
	}
	// Graph :: print();
	int u = read(), v = read();
	Graph :: Dijkstra(id(u, a[u]));
	long long ans = INF;
	for (register int i = -k; i <= k; ++i) ans = std :: min(ans, Graph :: dis[id(v, i)]);
	printf("%lld\n", ans < INF ? ans : -1ll);
}
int main(){
	int T = read();
	while (T--) solve();
}