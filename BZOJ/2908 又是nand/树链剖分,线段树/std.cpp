#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
// char buf[1 << 23], *ps = buf, *pt = buf;
// #define getchar() (ps == pt && (pt = (ps = buf) + fread(buf, 1, 1 << 23, stdin), ps == pt) ? EOF : *ps++)
unsigned read(){
	register unsigned x = 0;
	register char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) ;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x;
}
// char pbuf[1 << 23], *pp = pbuf;
// #define putchar(x) (pp == pbuf + (1 << 23) ? fwrite(pbuf, 1, 1 << 23, stdout), pp = pbuf : 0, *pp++ = x)
// struct __IO_flusher{ ~__IO_flusher(){ fwrite(pbuf, 1, pp - pbuf, stdout); } } IO_flusher;
void print(unsigned x, char ch = '\n'){
	if (x == 0) return putchar('0'), putchar(ch), void(0);
	int cnt = 0, num[25];
	for (; x; x /= 10) num[++cnt] = x % 10;
	while (cnt) putchar(num[cnt] ^ '0'), --cnt;
	putchar(ch);
}
const int N = 100005;
int n, m, k;
unsigned a[N], U;
std::vector<int> E[N];
int fa[N], dep[N], sz[N], son[N];
int tp[N], idx, dfn[N], idt[N];
void dfs(int u){
	dep[u] = dep[fa[u]] + 1, sz[u] = 1, son[u] = 0;
	for (register int i = 0, v; i < (int)E[u].size(); ++i)
		if ((v = E[u][i]) != fa[u]) fa[v] = u, dfs(v), sz[u] += sz[v], !son[u] || sz[v] > sz[son[u]] ? son[u] = v : 0;
}
void dfs(int u, int _tp){
	tp[u] = _tp, dfn[u] = ++idx, idt[idx] = u;
	if (son[u]) dfs(son[u], _tp);
	for (register int i = 0, v; i < (int)E[u].size(); ++i)
		if ((v = E[u][i]) != fa[u] && v != son[u]) dfs(v, v);
}
struct node{
	unsigned v0, v1;
	void init(unsigned v){ v0 = U, v1 = U ^ v; }
	node operator + (const node &rhs) const {
		return (node){(v0 & rhs.v1) | (~v0 & rhs.v0), (v1 & rhs.v1) | (~v1 & rhs.v0)};
	}
};
struct Segment_Tree{
	node val[2][N << 2];
	void build(int u, int l, int r){
		if (l == r) return val[0][u].init(a[idt[l]]), val[1][u] = val[0][u], void(0);
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r);
		val[0][u] = val[0][u << 1] + val[0][u << 1 | 1];
		val[1][u] = val[1][u << 1 | 1] + val[1][u << 1];
	}
	void modify(int u, int l, int r, int x, unsigned v){
		if (l == r) return val[0][u].init(v), val[1][u] = val[0][u], void(0);
		int md = (l + r) >> 1;
		if (x <= md) modify(u << 1, l, md, x, v);
		else modify(u << 1 | 1, md + 1, r, x, v);
		val[0][u] = val[0][u << 1] + val[0][u << 1 | 1];
		val[1][u] = val[1][u << 1 | 1] + val[1][u << 1];
	}
	node query(int u, int l, int r, int L, int R, int d){
		if (L <= l && r <= R) return val[d][u];
		int md = (l + r) >> 1;
		if (R <= md) return query(u << 1, l, md, L, R, d);
		if (L > md) return query(u << 1 | 1, md + 1, r, L, R, d);
		if (!d) return query(u << 1, l, md, L, R, d) + query(u << 1 | 1, md + 1, r, L, R, d);
		else return query(u << 1 | 1, md + 1, r, L, R, d) + query(u << 1, l, md, L, R, d);
	}
}T;
unsigned query(int u, int v){
	node s = {0u, U};
	std::vector<node> qu, qv;
	while (tp[u] != tp[v]){
		if (dep[tp[u]] > dep[tp[v]])
			qu.push_back(T.query(1, 1, n, dfn[tp[u]], dfn[u], 1)), u = fa[tp[u]];
		else
			qv.push_back(T.query(1, 1, n, dfn[tp[v]], dfn[v], 0)), v = fa[tp[v]];
	}
	if (dep[u] > dep[v]) qu.push_back(T.query(1, 1, n, dfn[v], dfn[u], 1));
	else qv.push_back(T.query(1, 1, n, dfn[u], dfn[v], 0));
	for (register int i = 0; i < (int)qu.size(); ++i) s = s + qu[i];
	for (register int i = (int)qv.size() - 1; ~i; --i) s = s + qv[i];
	return s.v0;
}
int main(){
	n = read(), m = read(), k = read();
	for (register int i = 0; i < k; ++i) U |= 1u << i;
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1, u, v; i < n; ++i)
		u = read(), v = read(), E[u].push_back(v), E[v].push_back(u);
	dfs(1), dfs(1, 1), T.build(1, 1, n);
	while (m--){
		char op;
		while (!isalpha(op = getchar())) ;
		int x, y;
		unsigned z;
		if (op == 'Q') x = read(), y = read(), print(query(x, y));
		else x = read(), z = read(), T.modify(1, 1, n, dfn[x], z);
	}
}