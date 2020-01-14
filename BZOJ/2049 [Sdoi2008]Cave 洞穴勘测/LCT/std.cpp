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
const int N = 50005, M = 100005, INF = 0x3f3f3f3f;
int n, m, ans, cnt;
struct edge{
	int u, v, w;
}ne[N];
std::vector<edge> E[N];
struct LCT{
	static const int N = 100005;
	int fa[N], son[N][2], rev[N];
	bool is_root(int u){ return son[fa[u]][0] != u && son[fa[u]][1] != u; }
	int dir(int u){ return son[fa[u]][1] == u; }
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
			splay(u), son[u][1] = v;
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
		if (find_root(v) == u && fa[v] == u && !son[v][0]) fa[v] = son[u][1] = 0;
	}
	bool is_connected(int u, int v){
		make_root(u);
		return find_root(v) == u;
	}
}T;
int main(){
	n = read(), m = read();
	while (m--){
		char op;
		while (!isalpha(op = getchar())) ;
		int u = read(), v = read();
		if (op == 'C') T.link(u, v);
		if (op == 'D') T.cut(u, v);
		if (op == 'Q') if (T.is_connected(u, v)) puts("Yes"); else puts("No");
	}
}