#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 2005
#define M 5000005
#define INF 0x3f3f3f3f3f3f3f3fll
int n, c, S, T;
int edge, to[M], cap[M], pr[M], hd[N];
void addedge(int u, int v, int c){
	to[edge] = v, cap[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
	to[edge] = u, cap[edge] = 0, pr[edge] = hd[v], hd[v] = edge++;
}
namespace Maximum_Flow{
	int dep[N], h, t, Q[N];
	long long dfs(int u, long long flow){
		if (u == T || !flow) return flow;
		long long ans = 0;
		for (register int i = hd[u], v, tmp; ~i; i = pr[i])
			if (dep[v = to[i]] == dep[u] + 1 && (tmp = dfs(v, std :: min(flow, 1ll * cap[i])))){
				ans += tmp, flow -= tmp, cap[i] -= tmp, cap[i ^ 1] += tmp;
				if (!flow) break;
			}
		if (!ans) dep[u] = -1;
		return ans;
	}
	int bfs(){
		memset(dep, -1, sizeof dep);
		h = 0, t = 1, Q[t] = S, dep[S] = 0;
		while (h < t){
			int u = Q[++h];
			for (register int i = hd[u], v; ~i; i = pr[i])
				if (dep[v = to[i]] == -1 && cap[i]){
					dep[v] = dep[u] + 1;
					if (v == T) return 1;
					Q[++t] = v;
				}
		}
		return 0;
	}
	long long dinic(){
		long long ans = 0;
		while (bfs()) ans += dfs(S, INF);
		return ans;
	}
}
int main(){
	n = read(), c = read(), S = 0, T = n + 1;
	memset(hd, -1, sizeof hd);
	for (register int i = 1; i <= n; ++i) addedge(S, i, read());
	for (register int i = 1; i <= n; ++i) addedge(i, T, read());
	for (register int i = 1; i <= n; ++i)
		for (register int j = i + 1; j <= n; ++j)
			addedge(i, j, c);
	printf("%lld", Maximum_Flow :: dinic());
	// getchar(), getchar();
}
