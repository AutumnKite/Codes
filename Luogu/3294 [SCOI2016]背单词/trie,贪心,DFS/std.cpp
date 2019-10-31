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
const int N = 100005, M = 510005;
int n, len;
char s[M];
std :: vector<int> E[N];
namespace trie{
	int cnt = 1, son[M][26], id[M];
	void insert(int _id, int len, char *s){
		int u = 1;
		for (register int i = 1; i <= len; u = son[u][s[i] - 'a'], ++i)
			if (!son[u][s[i] - 'a']) son[u][s[i] - 'a'] = ++cnt;
		id[u] = _id;
	}
	std :: vector<int> dfs(int u){
		std :: vector<int> res, tmp;
		for (register int i = 0; i < 26; ++i)
			if (son[u][i]){
				tmp = dfs(son[u][i]);
				for (int v : tmp) res.push_back(v);
			}
		if (id[u]) E[id[u]] = res, res.resize(1), res[0] = id[u];
		return res;
	}
}
int idx, dfn[N], sz[N];
long long ans;
void init(int u){
	sz[u] = 1;
	for (int v : E[u]) init(v), sz[u] += sz[v];
	std :: sort(E[u].begin(), E[u].end(), [=](int a, int b){
		return sz[a] < sz[b];
	});
}
void dfs(int u, int fa = 0){
	dfn[u] = idx++, ans += dfn[u] - dfn[fa];
	for (int v : E[u]) dfs(v, u);
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i){
		scanf("%s", s + 1), len = strlen(s + 1);
		std :: reverse(s + 1, s + 1 + len);
		trie :: insert(i, len, s);
	}
	E[0] = trie :: dfs(1);
	init(0), dfs(0);
	printf("%lld\n", ans);
}
