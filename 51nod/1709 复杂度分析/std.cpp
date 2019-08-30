#include <cstdio>
#include <cctype>
#define N 100005
#define M 20
int read(){
	int x = 0, f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^'0');
	return f ? x : -x;
}
int n, fa[N], sz[N], f[N][2], s[N][2], S[N][2];
int edge, to[N << 1], pr[N << 1], hd[N];
void addedge(int u, int v){
	to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
}
void dfs(int u){
	sz[u] = 1;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa[u]) fa[v] = u, dfs(v), sz[u] += sz[v];
}
int main(){
	n = read();
	for (register int i = 1; i < n; ++i){
		int u (read()), v (read());
		addedge(u, v), addedge(v, u);
	}
	dfs(1);
	for (register int i = 1; i <= n; ++i) 
	int flag = 1;
	while (flag){
		flag = 0;
		for (register int i = 1; i <= n; ++i) 
	}
}