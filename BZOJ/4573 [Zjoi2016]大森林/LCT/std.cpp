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
const int N = 300005;
int n, q, m, id[N], l[N], r[N], ans[N];
struct node{
	int u, v, t;
};
std::vector<node> mfy[N], qry[N];
struct LCT{
	int cnt, fa[N], son[N][2], a[N], sum[N];
	int new_node(int _v){
		int u = ++cnt;
		return fa[u] = son[u][0] = son[u][1] = 0, a[u] = sum[u] = _v, u;
	}
	bool is_root(int u){ return son[fa[u]][0] != u && son[fa[u]][1] != u; }
	int dir(int u){ return son[fa[u]][1] == u; }
	void up(int u){ sum[u] = sum[son[u][0]] + sum[son[u][1]] + a[u]; }
	void change(int u, int k, int v){ son[u][k] = v, fa[v] = u; }
	void rotate(int u){
		int v = fa[u], d = dir(u);
		change(v, d, son[u][!d]);
		if (is_root(v)) fa[u] = fa[v]; else change(fa[v], dir(v), u);
		change(u, !d, v);
		up(v), up(u);
	}
	void splay(int u){
		while (!is_root(u)){
			int v = fa[u];
			if (is_root(v)){ rotate(u); break; }
			dir(u) == dir(v) ? rotate(v) : rotate(u), rotate(u);
		}
	}
	int access(int u){
		int v = 0;
		for (; u; v = u, u = fa[u]) splay(u), son[u][1] = v, up(u);
		return v;
	}
	void link(int u, int v){ splay(u), fa[u] = v; }
	void cut(int u){ access(u), splay(u), son[u][0] = fa[son[u][0]] = 0, up(u); }
	int dis(int u, int v){
		access(u), splay(u);
		int res = sum[u], LCA = access(v);
		splay(v), res += sum[v];
		return access(LCA), splay(LCA), res -= 2 * sum[LCA];
	}
}T;
int main(){
	n = read(), q = read(), m = 1;
	int rt = T.new_node(1);
	int lst = T.new_node(0);
	l[1] = 1, r[1] = n, id[1] = rt, T.link(lst, rt);
	int cnt = 0;
	for (register int i = 1; i <= q; ++i){
		int op = read();
		if (op == 0){
			++m, l[m] = read(), r[m] = read();
			id[m] = T.new_node(1), T.link(id[m], lst);
		}
		if (op == 1){
			int L = read(), R = read(), x = read();
			L = std::max(L, l[x]), R = std::min(R, r[x]);
			if (L > R) continue;
			int p = T.new_node(0);
			T.link(p, lst);
			mfy[L].push_back((node){p, id[x], 0}), mfy[R + 1].push_back((node){p, lst, 0});
			lst = p;
		}
		if (op == 2){
			int x = read(), u = read(), v = read();
			qry[x].push_back((node){id[u], id[v], ++cnt});
		}
	}
	for (register int i = 1; i <= n; ++i){
		for (register int j = 0; j < (int)mfy[i].size(); ++j)
			T.cut(mfy[i][j].u), T.link(mfy[i][j].u, mfy[i][j].v);
		for (register int j = 0; j < (int)qry[i].size(); ++j)
			ans[qry[i][j].t] = T.dis(qry[i][j].u, qry[i][j].v);
	}
	for (register int i = 1; i <= cnt; ++i) print(ans[i]);
}