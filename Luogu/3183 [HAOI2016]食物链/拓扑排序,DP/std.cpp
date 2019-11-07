#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0, f = 1;
	register char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n, m, dp[N], d[N], vis[N];
std :: vector<int> E[N];
int h, t, u, Q[N], ans;
void toposort(){
	h = t = 0;
	for (register int i = 1; i <= n; ++i) if (!d[i]) Q[++t] = i, dp[i] = 1;
	while (h < t) for (int v : E[u = Q[++h]]) if (dp[v] += dp[u], !(--d[v])) Q[++t] = v;
}
int main(){
	n = read(), m = read();
	for (register int i = 1, u, v; i <= m; ++i)
		u = read(), v = read(), E[u].push_back(v), ++d[v];
	for (register int i = 1; i <= n; ++i)
		if (d[i] && !E[i].size()) vis[i] = 1;
	toposort();
	for (register int i = 1; i <= n; ++i)
		ans += vis[i] * dp[i];
	printf("%d\n", ans);
}