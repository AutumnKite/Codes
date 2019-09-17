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
#define N 2000005
int n, m;
int edge, to[N], pr[N], hd[N];
void addedge(int u, int v){
	to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
}
int idx, dfn[N], low[N], top, sta[N], vis[N], cnt, col[N];
void tarjan(int u){
	dfn[u] = low[u] = ++idx, sta[++top] = u, vis[u] = 1;
	for (register int i = hd[u], v; i; i = pr[i])
		if (!dfn[v = to[i]]) tarjan(v), low[u] = std :: min(low[u], low[v]);
		else if (vis[v]) low[u] = std :: min(low[u], dfn[v]);
	if (dfn[u] == low[u]){
		++cnt, sta[top + 1] = -1;
		while (sta[top + 1] != u) col[sta[top]] = cnt, vis[sta[top--]] = 0;
	}
}
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= m; ++i){
		int x = read() - 1, a = read(), y = read() - 1, b = read();
		addedge(x << 1 | (a ^ 1), y << 1 | b), addedge(y << 1 | (b ^ 1), x << 1 | a);
	}
	for (register int i = 0; i < (n << 1); ++i)
		if (!dfn[i]) tarjan(i);
	for (register int i = 0; i < n; ++i)
		if (col[i << 1] == col[i << 1 | 1]) return puts("IMPOSSIBLE"), 0;
	puts("POSSIBLE");
	for (register int i = 0; i < n; ++i)
		printf("%d ", col[i << 1 | 1] < col[i << 1]);
}