#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 300005
int n, m;
struct Link_Cut_Tree{
	int a[N], fa[N], son[N][2], val[N], rev[N], tp, sta[N];
	void up(int u){
		val[u] = val[son[u][0]] ^ val[son[u][1]] ^ a[u];
	}
	void reverse(int u){
		if (u) std :: swap(son[u][0], son[u][1]), rev[u] ^= 1;
	}
	void down(int u){
		if (rev[u]) reverse(son[u][0]), reverse(son[u][1]), rev[u] = 0;
	}
	bool is_root(int u){
		return son[fa[u]][0] != u && son[fa[u]][1] != u;
	}
	int dir(int u){
		return son[fa[u]][1] == u;
	}
	void change(int u, int k, int v){
		fa[v] = u, son[u][k] = v;
	}
	void rotate(int u){
		int v = fa[u], k = dir(u);
		change(v, k, son[u][!k]);
		if (!is_root(v)) change(fa[v], dir(v), u); else fa[u] = fa[v];
		change(u, !k, v);
		up(v), up(u);
	}
	void splay(int u){
		tp = 1, sta[tp] = u;
		for (register int i = u; !is_root(i); i = fa[i]) sta[++tp] = fa[i];
		for (; tp; --tp) down(sta[tp]);
		while (!is_root(u)){
			int v = fa[u];
			if (is_root(v)){ rotate(u); break; }
			dir(u) == dir(v) ? rotate(v) : rotate(u);
			rotate(u);
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
		splay(u);
		return u;
	}
	int query(int u, int v){
		make_root(u), access(v), splay(v);
		return val[v];
	}
	void link(int u, int v){
		make_root(u);
		if (find_root(v) != u) fa[u] = v;
	}
	void cut(int u, int v){
		make_root(u);
		if (find_root(v) == u && fa[v] == u && !son[v][0])
			fa[v] = son[u][1] = 0, up(u);
	}
	void modify(int u, int k){
		a[u] = k, splay(u);
	}
}T;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i)
		T.a[i] = T.val[i] = read();
	for (register int i = 1; i <= m; ++i){
		int opt = read(), x = read(), y = read();
		if (opt == 0) printf("%d\n", T.query(x, y));
		if (opt == 1) T.link(x, y);
		if (opt == 2) T.cut(x, y);
		if (opt == 3) T.modify(x, y);
	}
}
