#include <cstdio>
#define N 500005
int n, dep[N], fail[N], go[N][26];
char a[N];
int edge, hd[N], to[N], pr[N];
void addedge(int u, int v){
	to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
}
void dfs(int u, int fa = -1){
	int tmp;
	if (~fa){
		dep[u] = dep[fa] + 1, fail[u] = go[fa][a[u]];
		for (register int i = 0; i < 26; ++i) go[u][i] = go[fail[u]][i];
		if (fail[u] == fa) go[u][a[u]] = u;
		tmp = go[fa][a[u]], go[fa][a[u]] = u;
	}
	for (register int i = hd[u]; i; i = pr[i]) dfs(to[i], u);
	if (~fa) go[fa][a[u]] = tmp;
}
int main(){
	scanf("%d", &n);
	for (register int i = 1, fa; i <= n; ++i) scanf("%d", &fa), addedge(fa, i);
	scanf("%s", a + 1);
	for (register int i = 1; i <= n; ++i) a[i] -= 'a';
	dep[0] = 0, dfs(0);
	for (register int i = 1; i <= n; ++i) printf("%d\n", dep[i] - dep[fail[i]]);
}