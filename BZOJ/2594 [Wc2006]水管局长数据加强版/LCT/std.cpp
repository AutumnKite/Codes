#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
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
const int N = 100005;
int n, m, q, ans[N];
struct edge{
	int u, v, w;
	bool vis;
	bool operator < (const edge &rhs) const {
		return u < rhs.u || (u == rhs.u && v < rhs.v);
	}
}E[1000005];
bool cmp(edge a, edge b){ return a.w < b.w; }
struct query{
	int op, u, v, w;
}Q[N];
struct DSU{
	int fa[N];
	void init(){
		for (register int i = 1; i <= n; ++i) fa[i] = i;
	}
	int find(int x){ return fa[x] == x ? x : (fa[x] = find(fa[x])); }
	bool merge(int x, int y){
		x = find(x), y = find(y);
		if (x == y) return 0;
		return fa[y] = x, 1;
	}
}D;
struct LCT{
	static const int N = 200005;
	int fa[N], son[N][2], rev[N], a[N];
	std::pair<int, int> mx[N];
	bool is_root(int u){ return son[fa[u]][0] != u && son[fa[u]][1] != u; }
	int dir(int u){ return son[fa[u]][1] == u; }
	void up(int u){
		mx[u] = std::max(mx[son[u][0]], mx[son[u][1]]);
		if (a[u] > mx[u].first) mx[u].first = a[u], mx[u].second = u;
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
	void split(int u, int v){
		make_root(u), access(v), splay(v);
	}
	std::pair<int, int> query(int u, int v){
		return split(u, v), mx[v];
	}
}T;
int main(){
	n = read(), m = read(), q = read();
	for (register int i = 1; i <= m; ++i){
		E[i].u = read(), E[i].v = read(), E[i].w = read();
		if (E[i].u > E[i].v) std::swap(E[i].u, E[i].v);
	}
	std::sort(E + 1, E + 1 + m);
	for (register int i = 1; i <= q; ++i){
		Q[i].op = read(), Q[i].u = read(), Q[i].v = read();
		if (Q[i].u > Q[i].v) std::swap(Q[i].u, Q[i].v);
		if (Q[i].op == 2){
			int p = std::lower_bound(E + 1, E + 1 + m, (edge){Q[i].u, Q[i].v, 0, 0}) - E;
			E[p].vis = 1, Q[i].w = E[p].w;
		}
	}
	D.init();
	std::sort(E + 1, E + 1 + m, cmp);
	int k = 0;
	for (register int i = 1; i <= m; ++i)
		if (!E[i].vis && D.merge(E[i].u, E[i].v)) E[++k] = E[i];
	for (register int i = 1; i <= n; ++i)
		T.a[i] = T.mx[i].first = 0, T.mx[i].second = i;
	for (register int i = 1; i < n; ++i)
		T.a[n + i] = T.mx[n + i].first = E[i].w, T.mx[n + i].second = n + i;
	for (register int i = 1; i < n; ++i)
		T.link(n + i, E[i].u), T.link(n + i, E[i].v);
	int cnt = 0;
	for (register int i = q; i; --i)
		if (Q[i].op == 1) ans[++cnt] = T.query(Q[i].u, Q[i].v).first;
		else{
			std::pair<int, int> tmp = T.query(Q[i].u, Q[i].v);
			int mx = tmp.first, id = tmp.second - n;
			if (mx > Q[i].w){
				T.cut(n + id, E[id].u), T.cut(n + id, E[id].v);
				T.a[n + id] = T.mx[n + id].first = Q[i].w;
				E[id].u = Q[i].u, E[id].v = Q[i].v, E[id].w = Q[i].w;
				T.link(n + id, E[id].u), T.link(n + id, E[id].v);
			}
		}
	while (cnt) print(ans[cnt]), --cnt;
}