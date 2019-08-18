#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0, f = 1;
	register char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 200005
#define INF 0x3f3f3f3f3f3f3f3fll
int n;
int edge, to[N << 2], tw[N << 2], pr[N << 2], hd[N];
long long dis[N];
struct node{
	int x, y, id;
}a[N];
bool cmpx(node a, node b){ return a.x < b.x; }
bool cmpy(node a, node b){ return a.y < b.y; }
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
	to[++edge] = u, tw[edge] = w, pr[edge] = hd[v], hd[v] = edge;
}
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
long long Dijkstra(int s, int t){
	for (register int i = 1; i <= n; ++i) dis[i] = INF;
	dis[s] = 0, H.push(s);
	while (!H.empty()){
		int u = H.pop();
		for (register int i = hd[u], v; i; i = pr[i])
			if (dis[u] + tw[i] < dis[v = to[i]])
				dis[v] = dis[u] + tw[i], H.push(v);
	}
	return dis[t];
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i)
		a[i].x = read(), a[i].y = read(), a[i].id = i;
	std :: sort(a + 1, a + 1 + n, cmpx);
	for (register int i = 1; i < n; ++i)
		addedge(a[i].id, a[i + 1].id, a[i + 1].x - a[i].x);
	std :: sort(a + 1, a + 1 + n, cmpy);
	for (register int i = 1; i < n; ++i)
		addedge(a[i].id, a[i + 1].id, a[i + 1].y - a[i].y);
	printf("%lld\n", Dijkstra(1, n));
}