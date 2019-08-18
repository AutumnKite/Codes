#include <cstdio>
#include <cctype>
#include <algorithm>
#include <set>
#include <map>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 50005
#define M 200005
int n, m;
std :: set<int> to[N];
std :: map<int, int> dp[2][2][N];
int h, t, Q[M], ans, vis[N];
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= m; ++i){
		int u = read(), v = read();
		to[u].insert(v), to[v].insert(u);
		dp[0][1][u][v] = dp[1][0][v][u] = dp[1][0][u][v] = dp[0][1][v][u] = 1;
		dp[1][1][u][v] = dp[1][1][v][u] = -1e9;
	}
	ans = 0, h = 1, t = 0;
	for (register int i = 1; i <= n; ++i) if (to[i].size() == 2) Q[++t] = i, vis[i] = 1;
	while (h <= t){
		int x = Q[h++];
		if (to[x].size() != 2) continue;
		int u = *to[x].begin(), v = *(++to[x].begin());
		if (!dp[0][1][u][v]) ++dp[0][1][u][v];
		if (!dp[1][0][u][v]) ++dp[1][0][u][v];
		if (!dp[1][1][u][v]) dp[1][1][u][v] += 2;
		for (register int i = 0; i < 2; ++i)
			for (register int j = 0; j < 2; ++j){
				if (dp[i][j][u][v] < 0) continue;
				int mx = 0;
				for (register int k = 0; k < 2; ++k)
					mx = std :: max(mx, dp[i][k][u][x] + dp[k][j][x][v] - i - j - k);
				dp[j][i][v][u] = dp[i][j][u][v] += mx;
				ans = std :: max(ans, dp[i][j][u][v]);
			}
		to[u].erase(x), to[v].erase(x), to[u].insert(v), to[v].insert(u);
		if (to[u].size() == 2 && !vis[u]) Q[++t] = u, vis[u] = 1;
		if (to[v].size() == 2 && !vis[v]) Q[++t] = v, vis[v] = 1;
	}
	printf("%d\n", ans);
}

