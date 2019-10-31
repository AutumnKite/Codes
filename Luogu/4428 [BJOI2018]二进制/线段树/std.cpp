#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 100005;
int n, q, a[N];
namespace segt{
	struct node{
		int c0, cl[2][2], cr[2][2], pl[2], pr[2];
		long long s0, s1, s2;
		void init(int x){
			c0 = !x, cl[0][0] = cl[0][1] = cr[0][0] = cr[0][1] = s1 = s2 = 0, pl[1] = pr[1] = 1;
			if (x) cl[1][0] = cr[1][0] = 1, cl[1][1] = cr[1][1] = 0, pl[0] = pr[0] = 0, s0 = 1;
			else cl[1][0] = cr[1][0] = 0, cl[1][1] = cr[1][1] = 1, pl[0] = pr[0] = 1, s0 = 0;
		}
	}val[N << 2];
	node up(const node &a, const node &b, int wa, int wb){
		node c;
		c.c0 = a.c0 + b.c0;
		if (a.c0) c.cl[0][0] = a.cl[0][0], c.cl[1][0] = a.cl[1][0];
		else c.cl[0][0] = a.cl[0][0] + b.cl[wa & 1][0], c.cl[1][0] = a.cl[1][0] + b.cl[~wa & 1][0];
		if (a.c0 > 1) c.cl[0][1] = a.cl[0][1], c.cl[1][1] = a.cl[1][1];
		else if (!a.c0) c.cl[0][1] = b.cl[wa & 1][1], c.cl[1][1] = b.cl[~wa & 1][1];
		else c.cl[0][1] = a.cl[0][1] + b.cl[wa & 1][0], c.cl[1][1] = a.cl[1][1] + b.cl[~wa & 1][0];
		if (a.c0 == wa) c.pl[0] = wa + b.pl[0], c.pl[1] = wa + b.pl[1];
		else if (wa - a.c0 > 1) c.pl[0] = a.pl[0], c.pl[1] = a.pl[1];
		else c.pl[0] = a.pl[0], c.pl[1] = wa + b.pl[0];
		if (b.c0) c.cr[0][0] = b.cr[0][0], c.cr[1][0] = b.cr[1][0];
		else c.cr[0][0] = b.cr[0][0] + a.cr[wb & 1][0], c.cr[1][0] = b.cr[1][0] + a.cr[~wb & 1][0];
		if (b.c0 > 1) c.cr[0][1] = b.cr[0][1], c.cr[1][1] = b.cr[1][1];
		else if (!b.c0) c.cr[0][1] = a.cr[wb & 1][1], c.cr[1][1] = a.cr[~wb & 1][1];
		else c.cr[0][1] = b.cr[0][1] + a.cr[wb & 1][0], c.cr[1][1] = b.cr[1][1] + a.cr[~wb & 1][0];
		if (b.c0 == wb) c.pr[0] = wb + a.pr[0], c.pr[1] = wb + a.pr[1];
		else if (wb - b.c0 > 1) c.pr[0] = b.pr[0], c.pr[1] = b.pr[1];
		else c.pr[0] = b.pr[0], c.pr[1] = wb + a.pr[0];
		c.s0 = a.s0 + b.s0 + 1ll * a.cr[0][0] * b.cl[1][0] + 1ll * a.cr[1][0] * b.cl[0][0];
		c.s1 = a.s1 + b.s1 + 1ll * a.cr[0][0] * b.cl[0][1] + 1ll * a.cr[1][0] * b.cl[1][1];
		c.s1 += 1ll * a.cr[0][1] * b.cl[0][0] + 1ll * a.cr[1][1] * b.cl[1][0];
		c.s2 = a.s2 + b.s2;
		c.s2 += 1ll * (a.pr[1] - a.pr[0]) * b.pl[0];
		c.s2 += 1ll * (b.pl[1] - b.pl[0]) * a.pr[0];
		if ((a.pr[0] && !b.pl[0]) || (!a.pr[0] && b.pl[0])) --c.s2;
		return c;
	}
	void build(int u, int l, int r){
		if (l == r) return val[u].init(a[l]), void(0);
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r);
		val[u] = up(val[u << 1], val[u << 1 | 1], md - l + 1, r - md);
	}
	void modify(int u, int l, int r, int x, int v){
		if (l == r) return val[u].init(v), void(0);
		int md = (l + r) >> 1;
		if (x <= md) modify(u << 1, l, md, x, v);
		else modify(u << 1 | 1, md + 1, r, x, v);
		val[u] = up(val[u << 1], val[u << 1 | 1], md - l + 1, r - md);
	}
	node query(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return val[u];
		int md = (l + r) >> 1;
		if (R <= md) return query(u << 1, l, md, L, R);
		if (L > md) return query(u << 1 | 1, md + 1, r, L, R);
		return up(query(u << 1, l, md, L, md), query(u << 1 | 1, md + 1, r, md + 1, R), md - L + 1, R - md);
	}
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	segt :: build(1, 1, n);
	q = read();
	while (q--){
		int op = read();
		if (op == 1){
			int x = read();
			a[x] ^= 1, segt :: modify(1, 1, n, x, a[x]);
		}
		else{
			int l = read(), r = read();
			long long sum = 1ll * (r - l + 1) * (r - l + 2) >> 1;
			segt :: node tmp = segt :: query(1, 1, n, l, r);
			printf("%lld\n", sum - tmp.s0 - tmp.s1 - tmp.s2);
		}
	}
}
