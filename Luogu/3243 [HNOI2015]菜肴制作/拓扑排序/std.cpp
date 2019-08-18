#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
int read(){
	register int x = 0, f = 1;
	register char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int T, n, m, d[N], cnt, ans[N];
std :: vector<int> E[N];
std :: set<int> S;
void toposort(){
	S.clear(), cnt = 0;
	for (register int i = 1; i <= n; ++i)
		if (!d[i]) S.insert(i);
	while (!S.empty()){
		int u = ans[++cnt] = *(--S.end());
		S.erase(--S.end());
		for (register int i = 0, v; i < E[u].size(); ++i)
			if (!(--d[v = E[u][i]])) S.insert(v);
	}
}
int main(){
	T = read();
	while (T--){
		n = read(), m = read();
		for (register int i = 1; i <= n; ++i) d[i] = 0, E[i].clear();
		for (register int i = 1, u, v; i <= m; ++i)
			u = read(), v = read(), ++d[u], E[v].push_back(u);
		toposort();
		if (cnt < n) printf("Impossible!");
		else for (register int i = n; i; --i) printf("%d ", ans[i]);
		putchar('\n');
	}
}