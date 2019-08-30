#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
#define M 500005
int n, m, k, p;
struct Graph{
	int edge, to[M], tw[M], pr[M], hd[N];
	void clear(){
		edge = 0, memset(hd, 0, sizeof hd);
	}
	void addedge(int u, int v, int w){
		to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
	}
}G, AG;
int dis[N];
bool cmp(int a, int b){
	return dis[a] > dis[b];
}
struct Heap{
	int h[M], sz;
	void clear(){ sz = 0; }
	bool empty(){ return !sz; }
	void push(int x){ h[++sz] = x, std :: push_heap(h + 1, h + 1 + sz, cmp); }
	int pop(){ return std :: pop_heap(h + 1, h + 1 + sz, cmp), h[sz--]; }
	int top(){ return h[1]; }
}H;
void Dijkstra(int s){
	memset(dis, 0x3f, sizeof dis);
	H.clear(), dis[s] = 0, H.push(s);
	while (!H.empty()){
		int u = H.pop();
		for (register int i = G.hd[u], v, w; i; i = G.pr[i])
			if (dis[u] + (w = G.tw[i]) < dis[v = G.to[i]])
				dis[v] = dis[u] + w, H.push(v);
	}
}
int dp[N][55];
bool in[N][55];
int dfs(int u, int j){
	if (in[u][j]) return in[u][j] = 0, -1;
	if (~dp[u][j]) return dp[u][j];
	in[u][j] = 1, dp[u][j] = u == 1 ? 1 : 0;
	for (register int i = AG.hd[u], v, w, d; i; i = AG.pr[i]){
		v = AG.to[i], w = AG.tw[i], d = dis[v] + w - dis[u];
		if (d <= j){
			d = dfs(v, j - d);
			if (d == -1) return in[u][j] = 0, -1;
			(dp[u][j] += d) %= p;
		}
	}
	return in[u][j] = 0, dp[u][j];
}
void work(){
	G.clear(), AG.clear();
	n = read(), m = read(), k = read(), p = read();
	for (register int i = 1, u, v, w; i <= m; ++i) 
		u = read(), v = read(), w = read(), G.addedge(u, v, w), AG.addedge(v, u, w);
	Dijkstra(1);
	memset(dp, -1, sizeof dp);
	printf("%d\n", dfs(n, k));
}
int main(){
	int T = read();
	while (T--) work();
}