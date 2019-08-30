#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 25
#define M 100005
#define INF 1000000000
int n, m, d;
char a[N][N], b[N][N];
int cnt, in[N][N], out[N][N], sum;
namespace MaxFlow{
	int edge, to[M], cap[M], pr[M], hd[M];
	int S, T, dep[M], h, t, Q[M];
	void addedge(int u, int v, int c){
		to[edge] = v, cap[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
		to[edge] = u, cap[edge] = 0, pr[edge] = hd[v], hd[v] = edge++;
	}
	int dfs(int u, int flow){
		if (u == T || !flow) return flow;
		int ret = 0;
		for (register int i = hd[u], v, f; ~i; i = pr[i])
			if (dep[v = to[i]] == dep[u] + 1 && (f = dfs(v, std :: min(flow, cap[i])))){
				ret += f, flow -= f, cap[i] -= f, cap[i ^ 1] += f;
				if (!flow) break;
			}
		if (!ret) dep[u] = -1;
		return ret;
	}
	int bfs(){
		memset(dep, -1, sizeof dep);
		h = 0, t = 1, Q[t] = S, dep[S] = 0;
		while (h < t){
			int u = Q[++h];
			for (register int i = hd[u], v; ~i; i = pr[i])
				if (cap[i] && dep[v = to[i]] == -1){
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
using namespace MaxFlow;
double dist(int x1, int y1, int x2, int y2){
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
int main(){
	scanf("%d%d%d", &n, &m, &d);
	for (register int i = 1; i <= n; ++i) scanf("%s", a[i] + 1);
	for (register int i = 1; i <= n; ++i) scanf("%s", b[i] + 1);
	memset(hd, -1, sizeof hd);
	S = 1, T = 2, cnt = 2;
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			if (a[i][j] > '0'){
				in[i][j] = ++cnt, out[i][j] = ++cnt;
				if (b[i][j] == 'L') ++sum, addedge(S, in[i][j], 1);
				addedge(in[i][j], out[i][j], a[i][j] - '0');
				if (i > n - d || i <= d || j > m - d || j <= d)
					addedge(out[i][j], T, INF);
			}
	for (register int i = 1; i <= n; ++i)
		for (register int j = 1; j <= m; ++j)
			if (a[i][j] > '0') 
				for (register int x = 1; x <= n; ++x)
					for (register int y = 1; y <= m; ++y)
						if ((x != i || y != j) && a[i][j] > '0' && dist(i, j, x, y) <= d)
							addedge(out[i][j], in[x][y], INF);
	// for (register int i = 1; i <= cnt; ++i)
	// 	for (register int j = hd[i]; ~j; j = pr[j])
	// 		printf("%d %d %d\n", i, to[j], cap[j]);
	printf("%d", sum - dinic());
}