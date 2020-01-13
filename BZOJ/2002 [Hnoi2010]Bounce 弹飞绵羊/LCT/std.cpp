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
const int N = 200005;
int n, q, a[N];
struct LCT{
	int fa[N], son[N][2], sz[N], rev[N];
	bool is_root(int u){ return son[fa[u]][0] != u && son[fa[u]][1] != u; }
	int dir(int u){ return son[fa[u]][1] == u; }
	void up(int u){ sz[u] = sz[son[u][0]] + sz[son[u][1]] + 1; }
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
		if (is_root(v)) fa[u] = fa[v]; else change(fa[v], dir(v), u);
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
			if (is_root(v)){ rotate(u); break; }
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
	int get_dep(int u){
		return split(n + 1, u), sz[u];
	}
}T;
int get(int x){ return std::min(n + 1, x + a[x]); }
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i)
		a[i] = read(), T.link(i, get(i));
	q = read();
	while (q--){
		int op = read(), x = read() + 1, v;
		if (op == 1) print(T.get_dep(x) - 1);
		else v = read(), T.cut(x, get(x)), a[x] = v, T.link(x, get(x));
	}
}