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
#define N 100005
#define M 400005
int t, n, m, in[N], out[N], s;
int edge = 1, to[M], pr[M], hd[N], vis[M];
int top, sta[M];
void addedge(int u, int v){
	to[++edge] = v, pr[edge] = hd[u], hd[u] = edge, ++out[u], ++in[v];
}
void dfs(int u){
	for (register int &i = hd[u]; i; i = pr[i]){
		int j = i;
		if (!vis[j >> 1]) vis[j >> 1] = 1, dfs(to[j]), sta[++top] = (j >> 1) * (j & 1 ? -1 : 1);
	}
}
int main(){
	t = read(), n = read(), m = read();
	for (register int i = 1, u, v; i <= m; ++i){
		u = read(), v = read(), addedge(u, v), s = u;
		if (t == 1) addedge(v, u); else ++edge;
	}
	for (register int i = 1; i <= n; ++i)
		if ((t == 1 && (in[i] & 1)) || (t == 2 && in[i] != out[i])) return printf("NO\n"), 0;
	dfs(s);
	if (top != m) return printf("NO\n"), 0;
	printf("YES\n");
	while (top) printf("%d ", sta[top]), --top;
}