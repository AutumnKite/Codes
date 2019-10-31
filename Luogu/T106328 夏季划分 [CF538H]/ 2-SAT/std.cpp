#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 100005;
int L, R, n, m, l[N], r[N], k, b[N << 2];
namespace graph{
	const int N = 2000005, M = 6000005;
	int edge, to[M], pr[M], hd[N];
	void addedge(int u, int v){
		to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
		to[++edge] = u ^ 1, pr[edge] = hd[v ^ 1], hd[v ^ 1] = edge;
	}
	int idx, dfn[N], low[N], tp, sta[N], vis[N], cnt, col[N];
	void tarjan(int u){
		dfn[u] = low[u] = ++idx, vis[sta[++tp] = u] = 1;
		for (register int i = hd[u], v; i; i = pr[i])
			if (!dfn[v = to[i]]) tarjan(v), low[u] = std :: min(low[u], low[v]);
			else if (vis[v]) low[u] = std :: min(low[u], dfn[v]);
		if (dfn[u] == low[u]){
			sta[tp + 1] = -1, ++cnt;
			while (sta[tp + 1] != u) col[sta[tp]] = cnt, vis[sta[tp--]] = 0;
		}
	}
	bool work(int n){
		for (register int i = 0; i < n; ++i)
			if (!dfn[i]) tarjan(i);
		for (register int i = 0; i < (n >> 1); ++i)
			if (col[i << 1] == col[i << 1 | 1]) return 0;
		return 1;
	}
}
using graph :: addedge;
using graph :: work;
using graph :: col;
int main(){
	L = read(), R = read(), n = read(), m = read();
	b[k++] = 0, b[k++] = L, b[k++] = R;
	for (register int i = 0; i < n; ++i){
		l[i] = read(), r[i] = read();
		if (l[i] < R) b[k++] = l[i];
		if (r[i] < R) b[k++] = r[i];
		if (l[i] < L) b[k++] = L - l[i];
		if (r[i] < L) b[k++] = L - r[i];
	}
	std :: sort(b, b + k);
	k = std :: unique(b, b + k) - b;
	int p1 = n << 1, p2 = (n << 1) + (k << 1);
	for (register int i = 0; i < k - 1; ++i){
		addedge(p1 + (i << 1 | 1), p1 + ((i + 1) << 1 | 1));
		addedge(p2 + (i << 1 | 1), p2 + ((i + 1) << 1 | 1));
	}
	addedge(p1 + ((k - 1) << 1), p1 + ((k - 1) << 1 | 1));
	addedge(p2 + ((k - 1) << 1), p2 + ((k - 1) << 1 | 1));
	for (register int i = 0, j = k - 1; i < k; ++i){
		while (j >= 0 && b[i] + b[j] >= L) --j;
		if (j < 0) break;
		addedge(p1 + (i << 1 | 1), p2 + (j << 1));
		addedge(p2 + (i << 1 | 1), p1 + (j << 1));
	}
	for (register int i = 0, j = k - 1; i < k - 1; ++i){
		while (j >= 0 && b[i + 1] + b[j] > R) --j;
		if (j < 0) break;
		addedge(p1 + (i << 1), p2 + (j << 1 | 1));
		addedge(p2 + (i << 1), p1 + (j << 1 | 1));
	}
	for (register int i = 0, j; i < n; ++i){
		j = std :: upper_bound(b, b + k, r[i]) - b - 1;
		addedge(i << 1 | 1, p1 + (j << 1 | 1));
		addedge(i << 1, p2 + (j << 1 | 1));
		j = std :: lower_bound(b, b + k, l[i]) - b - 1;
		if (j < 0) continue;
		addedge(i << 1 | 1, p1 + (j << 1));
		addedge(i << 1, p2 + (j << 1));
	}
	for (register int i = 0; i < m; ++i){
		int x = read() - 1, y = read() - 1;
		addedge(x << 1, y << 1 | 1), addedge(x << 1 | 1, y << 1);
	}
	if (!work((n << 1) + (k << 2))) return puts("IMPOSSIBLE"), 0;
	puts("POSSIBLE");
	for (register int i = 0; i < k; ++i)
		if (col[p1 + (i << 1 | 1)] < col[p1 + (i << 1)]){ printf("%d ", b[i]); break; }
	for (register int i = 0; i < k; ++i)
		if (col[p2 + (i << 1 | 1)] < col[p2 + (i << 1)]){ printf("%d\n", b[i]); break; }
	for (register int i = 0; i < n; ++i)
		if (col[i << 1 | 1] < col[i << 1]) putchar('1');
		else putchar('2');
	putchar('\n');
}
