#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
// char buf[1 << 23], *ps = buf, *pt = buf;
// #define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
// char pbuf[1 << 23], *pp = pbuf;
// #define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
// struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
void print(int x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (x < 0 ? putchar('-'), x = -x : 0; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 50005, M = 100005, INF = 0x3f3f3f3f;
int n, m, ans, cnt;
struct edge{
	int u, v, w;
}ne[N];
std::vector<edge> E[N];
struct LCT{
	static const int N = 100005;
	int fa[N], son[N][2], rev[N];
	std::pair<int, int> mx[N], a[N];
	bool is_root(int u){ return son[fa[u]][0] != u && son[fa[u]][1] != u; }
	int dir(int u){ return son[fa[u]][1] == u; }
	void up(int u){
		mx[u] = std::max(a[u], std::max(mx[son[u][0]], mx[son[u][1]]));
	}
	void reverse(int u){
		if (u) std::swap(son[u][0], son[u][1]), rev[u] ^= 1;
	}
	void down(int u){
		if (rev[u]) reverse(son[u][0]), reverse(son[u][1]), rev[u] = 0;
	}
	void change(int u, int k, int v){ son[u][k] = v, fa[v] = u; }
	void rotate(int u){
		int v = fa[u], d = dir(u);
		change(v, d, son[u][!d]);
		if (!is_root(v)) change(fa[v], dir(v), u); else fa[u] = fa[v];
		change(u, !d, v);
		up(v), up(u);
	}
	int tp, sta[N];
	void splay(int u){
		tp = 1, sta[tp] = u;
		for (register int i = u; !is_root(i); i = fa[i]) sta[++tp] = fa[i];
		while (tp) down(sta[tp]), --tp;
		while (!is_root(u)){
			int v = fa[u];
			if (is_root(v)){ rotate(u); continue; }
			dir(u) == dir(v) ? rotate(v) : rotate(u), rotate(u);
		}
	}
	void access(int u){
		for (register int v = 0; u; v = u, u = fa[u])
			splay(u), son[u][1] = v, up(u);
	}
	void make_root(int u){
		access(u), splay(u), reverse(u);
	}
	int find_root(int u){
		access(u), splay(u);
		while (son[u][0]) down(u), u = son[u][0];
		return splay(u), u;
	}
	void link(int u, int v){
		make_root(u);
		if (find_root(v) != u) fa[u] = v;
	}
	void cut(int u, int v){
		make_root(u);
		if (find_root(v) == u && fa[v] == u && !son[v][0]) fa[v] = son[u][1] = 0, up(u);
	}
	bool split(int u, int v){
		make_root(u);
		if (find_root(v) == u) return splay(v), 1;
		else return 0;
	}
	std::pair<int, int> query(int u, int v){
		if (split(u, v)) return mx[v];
		else return std::make_pair(INF, 0);
	}
}T;
void add(edge e){
	std::pair<int, int> tmp = T.query(e.u, e.v);
	int mx = tmp.first, id = tmp.second;
	if (e.w > mx) return;
	if (mx == INF) ne[++cnt] = e, id = cnt;
	else T.cut(n + id, ne[id].u), T.cut(n + id, ne[id].v), ne[id] = e;
	T.a[n + id] = T.mx[n + id] = std::make_pair(e.w, id);
	T.link(n + id, e.u), T.link(n + id, e.v);
}
int main(){
	n = read(), m = read();
	int mx = 0;
	for (register int i = 1; i <= m; ++i){
		int u = read(), v = read(), a = read(), b = read();
		mx = std::max(mx, a), E[a].push_back((edge){u, v, b});
	}
	ans = INF;
	for (register int i = 1; i <= mx; ++i){
		for (register int j = 0; j < (int)E[i].size(); ++j) add(E[i][j]);
		ans = std::min(ans, i + T.query(1, n).first);
	}
	if (ans == INF) print(-1);
	else print(ans);
}