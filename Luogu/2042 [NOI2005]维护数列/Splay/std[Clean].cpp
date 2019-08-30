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
#define N 500005
#define INF 500000000
int n, m, a[N];
char opt[15];
int k, x, tot, c[N];
struct Splay{
	int rt, cnt, son[N][2], fa[N], sz[N], val[N];
	int rev[N], cov[N], sum[N], la[N], ra[N], ma[N];
	int top, rb[5000005];
	Splay(){
		rt = 0, cnt = 0, top = 0;
		fa[0] = son[0][0] = son[0][1] = sz[0] = rev[0] = cov[0] = 0;
		val[0] = sum[0] = la[0] = ra[0] = 0, ma[0] = -INF;
	}
	int new_node(int _val){
		int x = top ? rb[top--] : ++cnt;
		son[x][0] = son[x][1] = fa[x] = rev[x] = cov[x] = 0, sz[x] = 1;
		val[x] = ma[x] = sum[x] = _val, la[x] = ra[x] = std :: max(_val, 0);
		return x;
	}
	void recycle(int u){
		int ls = son[u][0], rs = son[u][1];
		if (ls) recycle(ls);
		if (rs) recycle(rs);
		rb[++top] = u;
	}
	void up(int u){
		int ls = son[u][0], rs = son[u][1];
		sz[u] = sz[ls] + sz[rs] + 1, sum[u] = sum[ls] + sum[rs] + val[u];
		la[u] = std :: max(la[ls], sum[ls] + val[u] + la[rs]);
		ra[u] = std :: max(ra[rs], sum[rs] + val[u] + ra[ls]);
		ma[u] = std :: max(std :: max(ma[ls], ma[rs]), ra[ls] + val[u] + la[rs]);
	}
	void down(int u){
		int ls = son[u][0], rs = son[u][1];
		if (cov[u]){
			if (ls) val[ls] = val[u], cov[ls] = 1, sum[ls] = sz[ls] * val[u];
			if (rs) val[rs] = val[u], cov[rs] = 1, sum[rs] = sz[rs] * val[u];
			if (val[u] > 0){
				if (ls) la[ls] = ra[ls] = ma[ls] = sum[ls];
				if (rs) la[rs] = ra[rs] = ma[rs] = sum[rs];
			}
			else{
				if (ls) la[ls] = ra[ls] = 0, ma[ls] = val[u];
				if (rs) la[rs] = ra[rs] = 0, ma[rs] = val[u];
			}
			cov[u] = 0;
		}
		if (rev[u]){
			if (ls) rev[ls] ^= 1, std :: swap(son[ls][0], son[ls][1]), std :: swap(la[ls], ra[ls]);
			if (rs) rev[rs] ^= 1, std :: swap(son[rs][0], son[rs][1]), std :: swap(la[rs], ra[rs]);
			rev[u] = 0;
		}
	}
	int dir(int x){ return son[fa[x]][1] == x; }
	void set(int x, int k, int y){ son[x][k] = y, fa[y] = x; }
	void rotate(int x){
		int y = fa[x], d = dir(x);
		set(fa[y], dir(y), x), set(y, d, son[x][!d]), set(x, !d, y);
		up(y), up(x);
	}
	void splay(int x, int g = 0){
		while (fa[x] != g){
			int y = fa[x];
			if (fa[y] != g) dir(y) == dir(x) ? rotate(y) : rotate(x);
			rotate(x);
		}
		if (!g) rt = x;
	}
	int build(int l, int r, int *a){
		if (l > r) return 0;
		if (l == r) return new_node(a[l]);
		int mid = (l + r) >> 1, u = new_node(a[mid]);
		son[u][0] = build(l, mid - 1, a), son[u][1] = build(mid + 1, r, a);
		fa[son[u][0]] = fa[son[u][1]] = u;
		return up(u), u;
	}
	int kth(int u, int k){
		down(u);
		int ls = son[u][0], rs = son[u][1];
		if (k == sz[ls] + 1) return u;
		else if (k <= sz[ls]) return kth(ls, k);
		else return kth(rs, k - sz[ls] - 1);
	}
	void insert(int x, int tot, int *a){
		int t = build(1, tot, a);
		int u = kth(rt, x); splay(u);
		int v = kth(rt, x + 1); splay(v, u);
		son[v][0] = t, fa[t] = v, up(v), up(u);
	}
	void erase(int l, int r){
		int u = kth(rt, l - 1); splay(u);
		int v = kth(rt, r + 1); splay(v, u);
		recycle(son[v][0]), son[v][0] = 0, up(v), up(u);
	}
	void cover(int l, int r, int c){
		int u = kth(rt, l - 1); splay(u);
		int v = kth(rt, r + 1); splay(v, u);
		int t = son[v][0];
		val[t] = c, cov[t] = 1, sum[t] = sz[t] * c;
		if (c > 0) la[t] = ra[t] = ma[t] = sum[t];
		else la[t] = ra[t] = 0, ma[t] = c;
		up(v), up(u);
	}
	void reverse(int l, int r){
		int u = kth(rt, l - 1); splay(u);
		int v = kth(rt, r + 1); splay(v, u);
		int t = son[v][0];
		rev[t] ^= 1, std :: swap(son[t][0], son[t][1]), std :: swap(la[t], ra[t]);
		up(v), up(u);
	}
	void query_sum(int l, int r){
		int u = kth(rt, l - 1); splay(u);
		int v = kth(rt, r + 1); splay(v, u);
		printf("%d\n", sum[son[v][0]]);
	}
	void query_max_sum(){ printf("%d\n", ma[rt]); }
}T;
int main(){
	n = read(), m = read(), n += 2, a[1] = a[n] = -INF;
	for (register int i = 2; i < n; ++i) a[i] = read();
	T.rt = T.build(1, n, a);
	while (m--){
		scanf("%s", opt);
		if (opt[0] == 'M' && opt[2] == 'X') T.query_max_sum();
		else x = read() + 1, tot = read();
		if (opt[0] == 'I'){
			for (register int i = 1; i <= tot; ++i) c[i] = read();
			T.insert(x, tot, c);
		}
		if (opt[0] == 'D') T.erase(x, x + tot - 1);
		if (opt[0] == 'M' && opt[2] == 'K') T.cover(x, x + tot - 1, read());
		if (opt[0] == 'R') T.reverse(x, x + tot - 1);
		if (opt[0] == 'G') T.query_sum(x, x + tot - 1);
	}
}
