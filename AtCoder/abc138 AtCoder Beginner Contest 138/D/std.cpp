#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 200005
int n, q, idx, ls[N], rs[N], a[N];
int edge, to[N << 1], pr[N << 1], hd[N];
void addedge(int u, int v){
	to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
}
void dfs(int u, int fa = 0){
	ls[u] = ++idx;
	for (register int i = hd[u]; i; i = pr[i])
		if (to[i] != fa) dfs(to[i], u);
	rs[u] = idx;
}
int main(){
	n = read(), q = read();
	for (register int i = 1, u, v; i < n; ++i)
		u = read(), v = read(), addedge(u, v), addedge(v, u);
	dfs(1);
	for (register int i = 1; i <= q; ++i){
		int u = read(), v = read();
		a[ls[u]] += v, a[rs[u] + 1] -= v;
	}
	for (register int i = 1; i <= n; ++i) a[i] += a[i - 1];
	for (register int i = 1; i <= n; ++i)
		printf("%d", a[ls[i]]), putchar(" \n"[i == n]);
}