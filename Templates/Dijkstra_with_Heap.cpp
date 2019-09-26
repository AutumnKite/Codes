#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
#define M 200005
#define INF 0x3f3f3f3f
int n, m, S;
int edge, to[M], pr[M], tw[M], hd[N];
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
}
int dis[N];
bool vis[N];
struct Heap{
	int sz;
	std :: pair<int, int> a[M];
	bool empty(){ return !sz; }
	void push(std :: pair<int, int> x){ a[++sz] = x, std :: push_heap(a + 1, a + 1 + sz); }
	std :: pair<int, int> top(){ return a[1]; }
	std :: pair<int, int> pop(){ return std :: pop_heap(a + 1, a + 1 + sz), a[sz--]; }
}H;
void Dijkstra(int s){
	for (register int i = 1; i <= n; ++i) dis[i] = INF, vis[i] = 0;
	dis[s] = 0, H.push(std :: make_pair(0, s));
	while (!H.empty()){
		int u = H.top().second, d = -H.top().first;
		H.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (register int i = hd[u], v; i; i = pr[i])
			if (!vis[v = to[i]] && dis[u] + tw[i] < dis[v])
				dis[v] = dis[u] + tw[i], H.push(std :: make_pair(-dis[v], v));
	}
}
int main(){
	n = read(), m = read(), S = read();
	for (register int i = 1, u, v, w; i <= m; ++i)
		u = read(), v = read(), w = read(), addedge(u, v, w);
	Dijkstra(S);
	for (register int i = 1; i <= n; ++i) printf("%d ", dis[i]);
}