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
const int N = 100005, P = 1000000007;
int T, n, m, pw[N], idx, dfn[N], low[N], sz[N], k, rt[N], ans[N];
char s[N];
std :: vector<int> E[N], son[N];
void tarjan(int u){
	dfn[u] = low[u] = ++idx, sz[u] = s[u] == '1';
	for (int v : E[u])
		if (!dfn[v]) tarjan(v), low[u] = std :: min(low[u], low[v]), son[u].push_back(v), sz[u] += sz[v];
		else low[u] = std :: min(low[u], dfn[v]);
}
void get_ans(int u, int Rt){
	for (int v : son[u]) get_ans(v, Rt);
	int tsz = sz[Rt] - (s[u] == '1'), d = 0;
	for (int v : son[u])
		if (low[v] >= dfn[u]){
			if (sz[v] & 1) return;
			tsz -= sz[v], ++d;
		}
	if (tsz & 1) return;
	// printf("%d %d\n", u, d);
	ans[u] = pw[(m - E[u].size()) - (n - 1) + (k + d - (u == Rt))];
}
void solve(){
	n = read(), m = read(), ans[0] = 0;
	for (register int i = 1; i <= n; ++i) dfn[i] = ans[i] = 0, E[i].clear(), son[i].clear();
	for (register int i = 1, u, v; i <= m; ++i)
		u = read(), v = read(), E[u].push_back(v), E[v].push_back(u);
	pw[0] = 1;
	for (register int i = 1; i <= m; ++i) pw[i] = 2ll * pw[i - 1] % P;
	scanf("%s", s + 1), k = idx = 0;
	int flag = 0, id = 0;
	for (register int i = 1; i <= n; ++i)
		if (!dfn[i]){
			tarjan(i), ++k, rt[k] = i;
			if (sz[i] & 1) if (!id) id = k; else flag = 1;
		}
	if (!flag){
		if (id) get_ans(rt[id], rt[id]);
		else{
			ans[0] = pw[m - n + k];
			for (register int i = 1; i <= k; ++i) get_ans(rt[i], rt[i]);
		}
	}
	for (register int i = 0; i <= n; ++i) printf("%d ", ans[i]); putchar('\n');
}
int main(){
	T = read();
	while (T--) solve();
}