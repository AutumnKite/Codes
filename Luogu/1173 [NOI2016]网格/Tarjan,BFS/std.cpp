#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0, f = 1;
	register char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 100005;
const int d[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
int r, c, n;
struct node{
	int x, y;
	bool operator < (const node &rhs) const {
		return x < rhs.x || (x == rhs.x && y < rhs.y);
	}
	bool operator == (const node &rhs) const {
		return x == rhs.x && y == rhs.y;
	}
}a[N];
int abs(int a){ return a > 0 ? a : -a; }
bool con4(node a, node b){ return abs(a.x - b.x) + abs(a.y - b.y) <= 1; }
bool con8(node a, node b){ return abs(a.x - b.x) + abs(a.y - b.y) <= 2; }
bool check_impos(){
	if (1ll * r * c - n < 2) return 1;
	if (1ll * r * c - n > 2) return 0;
	node p[2];
	int cnt = 0, k = 1;
	for (register int i = 1; i <= r; ++i)
		for (register int j = 1; j <= c; ++j)
			if (k > n || a[k].x != i || a[k].y != j) p[cnt++] = (node){i, j};
			else ++k;
	return con4(p[0], p[1]);
}
bool vis[N], Vis[N * 24];
int h, t, m;
node Q[N], S[N * 24];
int get_id(node *a, int n, node v){
	int p = std :: lower_bound(a + 1, a + 1 + n, v) - a;
	if (p <= n && a[p] == v) return p;
	return -1;
}
bool check_unc(int s){
	h = 0, t = 1, Q[t] = a[s], vis[s] = 1, m = 0;
	while (h < t){
		node u = Q[++h], v;
		for (register int i = 0; i < 8; ++i){
			v.x = u.x + d[i][0], v.y = u.y + d[i][1];
			if (v.x < 1 || v.x > r || v.y < 1 || v.y > c) continue;
			int p = get_id(a, n, v);
			if (p == -1){ S[++m] = v; continue; }
			if (!vis[p]) Q[++t] = v, vis[p] = 1;
		}
	}
	std :: sort(S + 1, S + 1 + m);
	m = std :: unique(S + 1, S + 1 + m) - S - 1;
	for (register int i = 1; i <= m; ++i) Vis[i] = 0;
	h = 0, t = 1, Q[t] = S[1], Vis[1] = 1;
	while (h < t){
		node u = Q[++h], v;
		for (register int i = 0; i < 4; ++i){
			v.x = u.x + d[i][0], v.y = u.y + d[i][1];
			if (v.x < 1 || v.x > r || v.y < 1 || v.y > c) continue;
			int p = get_id(S, m, v);
			if (~p && !Vis[p]) Q[++t] = v, Vis[p] = 1; else continue;
			if (t == m) return 0;
		}
	}
	return t < m;
}
bool check_0(){
	for (register int i = 1; i <= n; ++i) vis[i] = 0;
	for (register int i = 1; i <= n; ++i)
		if (!vis[i] && check_unc(i)) return 1;
	return 0;
}
int edge, to[N * 96], pr[N * 96], hd[N * 24];
int idx, dfn[N * 24], low[N * 24], cut_flag;
void addedge(int u, int v){
	to[++edge] = v, pr[edge] = hd[u], hd[u] = edge;
}
void tarjan(int u, int rt){
	int d = 0;
	dfn[u] = low[u] = ++idx;
	for (register int i = hd[u], v; i; i = pr[i])
		if (!dfn[v = to[i]]){
			tarjan(v, rt), low[u] = std :: min(low[u], low[v]), ++d;
			if (low[v] >= dfn[u] && u != rt && Vis[u]) cut_flag = 1;
		}
		else low[u] = std :: min(low[u], dfn[v]);
	if (u == rt && d >= 2 && Vis[u]) cut_flag = 1;
}
bool check_1(){
	if (r == 1 || c == 1) return 1;
	m = 0;
	int _p[5][5];
	for (register int i = 0; i < 5; ++i)
		for (register int j = 0; j < 5; ++j)
			_p[i][j] = 1;
	for (register int i = 1; i <= n; ++i){
		node u = a[i], v;
		for (register int dx = -2; dx <= 2; ++dx)
			for (register int dy = -2; dy <= 2; ++dy)
				if (dx || dy){
					v.x = u.x + dx, v.y = u.y + dy;
					if (v.x < 1 || v.x > r || v.y < 1 || v.y > c) continue;
					int &pp = _p[dx + 2][dy + 2];
					while (pp <= n && a[pp] < v) ++pp;
					if (pp <= n && a[pp] == v) continue;
					S[++m] = v;
				}
	}
	std :: sort(S + 1, S + 1 + m);
	m = std :: unique(S + 1, S + 1 + m) - S - 1;
	for (register int i = 1; i <= m; ++i) Vis[i] = 0;
	for (register int i = 0; i < 5; ++i)
		for (register int j = 0; j < 5; ++j)
			_p[i][j] = 1;
	for (register int i = 1; i <= n; ++i){
		node u = a[i], v;
		for (register int dx = -2; dx <= 2; ++dx)
			for (register int dy = -2; dy <= 2; ++dy)
				if (dx || dy){
					v.x = u.x + dx, v.y = u.y + dy;
					if (v.x < 1 || v.x > r || v.y < 1 || v.y > c) continue;
					int &pp = _p[dx + 2][dy + 2];
					while (pp <= m && S[pp] < v) ++pp;
					if (pp <= m && S[pp] == v && con8(u, v)) Vis[pp] = 1;
				}
	}
	edge = idx = cut_flag = 0;
	for (register int i = 1; i <= m; ++i) hd[i] = dfn[i] = 0;
	for (register int i = 1, p1 = 1, p2 = 1; i <= m; ++i){
		node v = {S[i].x, S[i].y + 1};
		while (p1 <= m && S[p1] < v) ++p1;
		if (p1 <= m && S[p1] == v) addedge(i, p1), addedge(p1, i);
		v = {S[i].x + 1, S[i].y};
		while (p2 <= m && S[p2] < v) ++p2;
		if (p2 <= m && S[p2] == v) addedge(i, p2), addedge(p2, i);
	}
	for (register int i = 1; i <= m; ++i)
		if (!dfn[i]) tarjan(i, i);
	return cut_flag;
}
void solve(){
	r = read(), c = read(), n = read();
	for (register int i = 1; i <= n; ++i) a[i].x = read(), a[i].y = read();
	std :: sort(a + 1, a + 1 + n);
	if (check_impos()) return puts("-1"), void(0);
	if (check_0()) return puts("0"), void(0);
	if (check_1()) return puts("1"), void(0);
	puts("2");
}
int main(){
	int T = read();
	while (T--) solve();
}
