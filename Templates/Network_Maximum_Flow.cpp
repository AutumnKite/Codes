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
#define N 10005
#define M 200005
#define INF 1000000000
int n, m, S, T;
int edge, to[M], cap[M], pr[M], hd[N];
void addedge(int u, int v, int c){
	to[edge] = v, cap[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
}
namespace Maximum_Flow{
	int dep[N], h, t, Q[N];
	int dfs(int u, int flow){
		if (u == T || !flow) return flow;
		int ans = 0;
		for (register int i = hd[u], v, tmp; ~i; i = pr[i])
			if (dep[v = to[i]] == dep[u] + 1 && (tmp = dfs(v, std :: min(flow, cap[i])))){
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
	int dinic(){
		int ans = 0;
		while (bfs()) ans += dfs(S, INF);
		return ans;
	}
}
int main(){
	n = read(), m = read(), S = read(), T = read();
	memset(hd, -1, sizeof hd);
	for (register int i = 1; i <= m; ++i){
		int u = read(), v = read(), c = read();
		addedge(u, v, c), addedge(v, u, 0);
	}
	printf("%d", Maximum_Flow :: dinic());
}