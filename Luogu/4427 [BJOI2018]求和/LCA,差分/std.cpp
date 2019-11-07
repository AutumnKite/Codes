#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 300005, P = 998244353;
int n, m, md, pw[N], sum[N][51], fa[N][20], dep[N];
std :: vector<int> E[N];
void dfs(int u){
	dep[u] = dep[fa[u][0]] + 1, md = std :: max(md, dep[u]);
	for (register int i = 1; i <= 19; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (int v : E[u]) if (v != fa[u][0]) fa[v][0] = u, dfs(v);
}
int lca(int u, int v){
	if (dep[u] < dep[v]) std :: swap(u, v);
	for (register int i = 19; ~i; --i)
		if (dep[fa[u][i]] >= dep[v]) u = fa[u][i];
	if (u == v) return u;
	for (register int i = 19; ~i; --i)
		if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
int plus(int a, int b){ return (a += b) >= P ? a - P : a; }
int minus(int a, int b){ return (a -= b) < 0 ? a + P : a; }
int main(){
	n = read();
	for (register int i = 1, u, v; i < n; ++i)
		u = read(), v = read(), E[u].push_back(v), E[v].push_back(u);
	dep[0] = -1, dfs(1);
	for (register int i = 1; i <= md; ++i) pw[i] = 1;
	for (register int j = 1; j <= 50; ++j){
		for (register int i = 1; i <= md; ++i) pw[i] = 1ll * pw[i] * i % P;
		for (register int i = 1; i <= md; ++i) sum[i][j] = plus(sum[i - 1][j], pw[i]);
	}
	m = read();
	while (m--){
		int u = read(), v = read(), k = read(), l = lca(u, v);
		u = dep[u], v = dep[v], l = dep[l];
		print(plus(minus(sum[u][k], l ? sum[l - 1][k] : 0), minus(sum[v][k], sum[l][k])));
	}
}