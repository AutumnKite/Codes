#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
const int N = 100005;
int n, m, a[N], q;
struct node{
	int op, l, r;
}Q[N];
namespace segt{
	int sum[N << 2], lz[N << 2];
	void up(int u){ sum[u] = sum[u << 1] + sum[u << 1 | 1]; }
	void build(int u, int l, int r, int x){
		lz[u] = -1;
		if (l == r) return sum[u] = a[l] > x, void(0);
		int md = (l + r) >> 1;
		build(u << 1, l, md, x), build(u << 1 | 1, md + 1, r, x);
		up(u);
	}
	void mod(int u, int l, int r, int x){ sum[u] = x * (r - l + 1), lz[u] = x; }
	void down(int u, int l, int md, int r){
		if (~lz[u]) mod(u << 1, l, md, lz[u]), mod(u << 1 | 1, md + 1, r, lz[u]), lz[u] = -1;
	}
	void modify(int u, int l, int r, int L, int R, int x){
		if (L > R) return;
		if (L <= l && r <= R) return mod(u, l, r, x), void(0);
		int md = (l + r) >> 1;
		down(u, l, md, r);
		if (L <= md) modify(u << 1, l, md, L, R, x);
		if (R > md) modify(u << 1 | 1, md + 1, r, L, R, x);
		up(u);
	}
	int query(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return sum[u];
		int md = (l + r) >> 1;
		down(u, l, md, r);
		if (R <= md) return query(u << 1, l, md, L, R);
		else if (L > md) return query(u << 1 | 1, md + 1, r, L, R);
		else return query(u << 1, l, md, L, R) + query(u << 1 | 1, md + 1, r, L, R);
	}
}
bool check(int md){
	segt :: build(1, 1, n, md);
	for (register int i = 1; i <= m; ++i){
		int s = segt :: query(1, 1, n, Q[i].l, Q[i].r);
		if (Q[i].op){
			segt :: modify(1, 1, n, Q[i].l, Q[i].l + s - 1, 1);
			segt :: modify(1, 1, n, Q[i].l + s, Q[i].r, 0);
		}
		else{
			segt :: modify(1, 1, n, Q[i].l, Q[i].r - s, 0);
			segt :: modify(1, 1, n, Q[i].r - s + 1, Q[i].r, 1);
		}
	}
	return segt :: query(1, 1, n, q, q) == 0;
}
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= m; ++i)
		Q[i].op = read(), Q[i].l = read(), Q[i].r = read();
	q = read();
	int l = 1, r = n, md, ans = 0;
	while (l <= r) if (check(md = (l + r) >> 1)) r = md - 1, ans = md; else l = md + 1;
	printf("%d\n", ans);
}