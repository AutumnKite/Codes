#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 250005
#define INF 0x3f3f3f3f3f3f3f3fll
int n;
int edge, to[N << 1], pr[N << 1], tw[N << 1], hd[N];
void addedge(int u, int v, int w){
	to[++edge] = v, tw[edge] = w, pr[edge] = hd[u], hd[u] = edge;
}
long long dp[N][2];
void dfs(int X, int u, int fa = 0){
	std :: vector<long long> val;
	dp[u][0] = dp[u][1] = 0;
	for (register int i = hd[u], v; i; i = pr[i])
		if ((v = to[i]) != fa) dfs(X, v, u), val.push_back(dp[v][1] + tw[i] - dp[v][0]), dp[u][0] += dp[v][0];
	dp[u][1] = dp[u][0];
	std :: sort(val.begin(), val.end());
	int d = val.size();
	for (register int i = 0; i < d && (i < d - X || val[i] < 0); ++i) dp[u][1] += val[i];
	if (!X) return dp[u][0] = INF, void(0);
	++d;
	for (register int i = 0; i < d - 1 && (i < d - X || val[i] < 0); ++i) dp[u][0] += val[i];
}
int main(){
	n = read();
	for (register int i = 1, u, v, w; i < n; ++i)
		u = read(), v = read(), w = read(), addedge(u, v, w), addedge(v, u, w);
	for (register int i = 0; i < n; ++i) dfs(i, 1), printf("%lld ", dp[1][1]);
}
