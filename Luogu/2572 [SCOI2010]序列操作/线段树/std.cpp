#include <cstdio>
#include <cctype>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
#define N 400005
int n, m, a[N];
struct Segment_Tree{
	struct node{
		int len, s, l, r, m;
		node operator + (const node &res) const {
			node ret;
			ret.len = res.len + len, ret.s = s + res.s;
			if (s == len) ret.l = s + res.l; else ret.l = l;
			if (res.s == res.len) ret.r = r + res.s; else ret.r = res.r;
			ret.m = std :: max(std :: max(m, res.m), r + res.l);
			return ret;
		}
	}d[2][N];
	int c[2][N], o[N];
	void up(int u){
		d[0][u] = d[0][u << 1] + d[0][u << 1 | 1], d[1][u] = d[1][u << 1] + d[1][u << 1 | 1];
	}
	void cov(int u, int l, int r, int x){
		d[x][u].s = d[x][u].l = d[x][u].r = d[x][u].m = r - l + 1, c[x][u] = 1;
		x ^= 1;
		d[x][u].s = d[x][u].l = d[x][u].r = d[x][u].m = 0, c[x][u] = 0;
		o[u] = 0;
	}
	void rev(int u){
		std :: swap(d[0][u], d[1][u]);
		if (c[0][u] || c[1][u]) std :: swap(c[0][u], c[1][u]); else o[u] ^= 1;
	}
	void down(int u, int l, int r){
		if (o[u]) return rev(u << 1), rev(u << 1 | 1), o[u] = 0, void(0);
		if (c[0][u] || c[1][u]){
			int x = c[1][u], md = (l + r) >> 1;
			return cov(u << 1, l, md, x), cov(u << 1 | 1, md + 1, r, x), c[x][u] = 0, void(0);
		}
	}
	void build(int u, int l, int r){
		if (l == r){
			d[a[l]][u] = (node){1, 1, 1, 1, 1}, d[!a[l]][u] = (node){1, 0, 0, 0, 0};
			c[0][u] = c[1][u] = o[u] = 0;
			return;
		}
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r), up(u);
	}
	void Cov(int u, int l, int r, int L, int R, int x){
		if (L <= l && r <= R) return cov(u, l, r, x), void(0);
		int md = (l + r) >> 1;
		down(u, l, r);
		if (L <= md) Cov(u << 1, l, md, L, R, x);
		if (R > md) Cov(u << 1 | 1, md + 1, r, L, R, x);
		up(u);
	}
	void Rev(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return rev(u), void(0);
		int md = (l + r) >> 1;
		down(u, l, r);
		if (L <= md) Rev(u << 1, l, md, L, R);
		if (R > md) Rev(u << 1 | 1, md + 1, r, L, R);
		up(u);
	}
	node Query(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return d[1][u];
		int md = (l + r) >> 1;
		down(u, l, r);
		if (R <= md) return Query(u << 1, l, md, L, R);
		else if (L > md) return Query(u << 1 | 1, md + 1, r, L, R);
		else return Query(u << 1, l, md, L, R) + Query(u << 1 | 1, md + 1, r, L, R);
	}
}T;
int main(){
	freopen("test.in", "r", stdin);
	freopen("wei.out", "w", stdout);
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	T.build(1, 1, n);
	for (register int i = 1; i <= m; ++i){
		int opt = read(), l = read() + 1, r = read() + 1;
		if (opt == 0) T.Cov(1, 1, n, l, r, 0);
		if (opt == 1) T.Cov(1, 1, n, l, r, 1);
		if (opt == 2) T.Rev(1, 1, n, l, r);
		if (opt == 3) printf("%d\n", T.Query(1, 1, n, l, r).s);
		if (opt == 4) printf("%d\n", T.Query(1, 1, n, l, r).m);
	}
}

