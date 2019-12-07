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
const int N = 20005;
int n, ans;
int edge, to[N << 1], tw[N << 1], pr[N << 1], hd[N];
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
}
int vis[N], sz[N], dis[N], cnt[3], Cnt[3], rt;
void getrt(int Sz, int u, int fa = 0){
	bool flag = 1;
	sz[u] = 1;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa && !vis[v])
			getrt(Sz, v, u), flag &= sz[v] <= (Sz >> 1), sz[u] += sz[v];
	if (flag && Sz - sz[u] <= (Sz >> 1)) rt = u;
}
void dfs(int u, int fa = 0){
	sz[u] = 1, ++cnt[dis[u] % 3];
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa && !vis[v])
			dis[v] = dis[u] + tw[i], dfs(v, u), sz[u] += sz[v];
}
void solve(int Sz, int u){
	getrt(Sz, u);
	vis[rt] = 1, Cnt[0] = 1, Cnt[1] = Cnt[2] = 0, ++ans;
	for (register int i = hd[rt], v; i; i = pr[i])
		if (!vis[v = to[i]]){
			cnt[0] = cnt[1] = cnt[2] = 0;
			dis[v] = tw[i], dfs(v, rt);
			ans += 2 * (cnt[0] * Cnt[0] + cnt[1] * Cnt[2] + cnt[2] * Cnt[1]);
			Cnt[0] += cnt[0], Cnt[1] += cnt[1], Cnt[2] += cnt[2];
		}
	for (register int i = hd[rt], v; i; i = pr[i])
		if (!vis[v = to[i]]) solve(sz[v], v);
}
int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }
int main(){
	n = read();
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), addedge(u, v, w), addedge(v, u, w);
	solve(n, 1);
	int sum = n * n, g = gcd(ans, sum);
	printf("%d/%d\n", ans / g, sum / g);
}