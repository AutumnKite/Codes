#include <cstdio>
#include <algorithm>
#include <vector>
#define N 1000005
#define INF 0x3f3f3f3f3f3f3f3fll
int n, m, t;
struct Edge{
	int x, y, c, w;
}E[N];
std :: vector<int> C[N], num[N];
int edge, to[N], pr[N], tw[N], hd[N];
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
	to[++edge] = u, tw[edge] = w, pr[edge] = hd[v], hd[v] = edge;
}
long long dis[N];
bool vis[N];
bool cmp(int x, int y){
	return dis[x] > dis[y];
}
struct Heap{
	int sz, a[N];
	bool empty(){ return !sz; }
	void push(int x){ a[++sz] = x, std :: push_heap(a + 1, a + 1 + sz, cmp); }
	int top(){ return a[1]; }
	int pop(){ return std :: pop_heap(a + 1, a + 1 + sz, cmp), a[sz--]; }
}H;
void Dijkstra(int s){
	for (register int i = 1; i <= t; ++i) dis[i] = INF, vis[i] = 0;
	dis[s] = 0, H.push(s);
	while (!H.empty()){
		int u = H.pop();
		if (vis[u]) continue;
		for (register int i = hd[u], v; i; i = pr[i])
			if (!vis[v = to[i]] && dis[u] + tw[i] < dis[v])
				dis[v] = dis[u] + tw[i], H.push(v);
	}
}
int main(){
	scanf("%d%d", &n, &m), C[1].push_back(1);
	for (register int i = 1; i <= m; ++i)
		scanf("%d%d%d%d", &E[i].x, &E[i].y, &E[i].c, &E[i].w),
		C[E[i].x].push_back(E[i].c), C[E[i].y].push_back(E[i].c);
	for (register int i = 1; i <= n; ++i){
		std :: sort(C[i].begin(), C[i].end());
		C[i].erase(std :: unique(C[i].begin(), C[i].end()), C[i].end());
		for (register int j = 0; j < C[i].size(); ++j)
			num[i].push_back(++t), j ? addedge(t, t - 1, C[i][j] - C[i][j - 1]), 0 : 0;
	}
	for (register int i = 1, x, y; i <= m; ++i)
		x = num[E[i].x][std :: lower_bound(C[E[i].x].begin(), C[E[i].x].end(), E[i].c) - C[E[i].x].begin()],
		y = num[E[i].y][std :: lower_bound(C[E[i].y].begin(), C[E[i].y].end(), E[i].c) - C[E[i].y].begin()],
		addedge(x, y, E[i].w);
	Dijkstra(1);
	long long ans = INF;
	for (register int i = 0; i < C[n].size(); ++i)
		ans = std :: min(ans, dis[num[n][i]]);
	printf("%lld\n", ans);
}
