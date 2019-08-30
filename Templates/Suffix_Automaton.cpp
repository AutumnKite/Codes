#include <cstdio>
#include <algorithm>
#include <cstring>
#define N 1000005
int n;
char a[N];
long long ans;
struct SAM{
	int cnt, len[N << 1], par[N << 1], son[N << 1][26], last;
	void Init(){
		cnt = 1, len[0] = 0, par[0] = -1, last = 0;
	}
	void Insert(int c){
		int cur = cnt++, p = last, q, nq;
		sz[cur] = 1, len[cur] = len[last] + 1;
		for (; ~p && !son[p][c]; p = par[p]) son[p][c] = cur;
		if (p == -1) return par[last = cur] = 0, void(0);
		q = son[p][c];
		if (len[q] == len[p] + 1) return par[last = cur] = q, void(0);
		nq = cnt++, par[nq] = par[q], len[nq] = len[p] + 1;
		memcpy(son[nq], son[q], sizeof son[nq]);
		par[q] = par[cur] = nq, last = cur;
		for (; ~p && son[p][c] == q; p = par[p]) son[p][c] = nq;
	}
	int edge, to[N << 1], pr[N << 1], hd[N << 1], sz[N << 1];
	void addedge(int u, int v){
		to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
	}
	void Build(){
		for (register int i = 1; i < cnt; ++i) addedge(par[i], i);
	}
	void dfs(int u = 0){
		for (register int i = hd[u]; i; i = pr[i]) dfs(to[i]), sz[u] += sz[to[i]];
		if (sz[u] > 1) ans = std :: max(ans, 1ll * sz[u] * len[u]);
	}
}T;
int main(){
	scanf("%s", a), n = strlen(a), T.Init();
	for (register int i = 0; i < n; ++i) T.Insert(a[i] - 'a');
	T.Build(), T.dfs();
	printf("%lld", ans);
}
