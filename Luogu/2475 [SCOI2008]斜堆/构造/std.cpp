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
const int N = 55;
int n, rt, son[N][2], fa[N], ans[N];
int main(){
	n = read(), rt = 0, fa[rt] = -1;
	for (register int i = 0; i <= n; ++i) son[i][0] = son[i][1] = -1;
	for (register int i = 1; i <= n; ++i){
		int x = read();
		if (x >= 100) son[x - 100][1] = i, fa[i] = x - 100;
		else son[x][0] = i, fa[i] = x;
	}
	for (register int i = n; ~i; --i){
		int u = rt;
		while (~son[u][1]) u = son[u][0];
		if (~son[u][0] && son[son[u][0]][0] == -1) u = std::max(u, son[u][0]);
		ans[i] = u;
		if (u == rt){ rt = son[u][0]; continue; }
		if (~son[u][0]) fa[son[u][0]] = fa[u];
		son[fa[u]][0] = son[u][0], u = fa[u];
		while (~u) std::swap(son[u][0], son[u][1]), u = fa[u];
	}
	for (register int i = 0; i <= n; ++i) printf("%d ", ans[i]);
}