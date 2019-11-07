#include <cstdio>
#include <cctype>
#include <cstdlib>
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
const int N = 100005;
int L, R, n, m, l[N], r[N], n1, n2, b[N];
std :: vector<int> E[N];
bool in(int x, int l, int r){ return l <= x && x <= r; }
void GG(){ puts("IMPOSSIBLE"), exit(0); }
void dfs(int u, int d){
	if (!in(d == 1 ? n1 : n2, l[u], r[u])) GG();
	b[u] = d, d = 3 - d;
	for (int v : E[u])
		if (!b[v]) dfs(v, d);
		else if (b[v] != d) GG();
}
int main(){
	L = read(), R = read();
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) l[i] = read(), r[i] = read();
	for (register int i = 1, u, v; i <= m; ++i)
		u = read(), v = read(), E[u].push_back(v), E[v].push_back(u);
	n1 = *std :: max_element(l + 1, l + 1 + n);
	n2 = *std :: min_element(r + 1, r + 1 + n);
	if (n1 + n2 < L) n1 += L - n1 - n2;
	else if (n1 + n2 > R) n2 -= n1 + n2 - R;
	if (n2 < 0) GG();
	for (register int i = 1; i <= n; ++i)
		if (!in(n1, l[i], r[i]) && !in(n2, l[i], r[i])) GG();
	for (register int i = 1; i <= n; ++i)
		if (!b[i]){
			bool flag1 = in(n1, l[i], r[i]), flag2 = in(n2, l[i], r[i]);
			if (flag1 && !flag2) dfs(i, 1);
			else if (!flag1 && flag2) dfs(i, 2);
		}
	for (register int i = 1; i <= n; ++i)
		if (!b[i]) dfs(i, 1);
	puts("POSSIBLE"), printf("%d %d\n", n1, n2);
	for (register int i = 1; i <= n; ++i) putchar(b[i] ^ '0');
	putchar('\n');
}