// This program need O2.
#include <cstdio>
#include <algorithm>
#define N 100005
int n, m, a[N], t, b[N << 1], x[N], y[N], k[N];
char opt[N][2];
struct Fenwick_Segment_Tree{ // Oh, I think this program will be FST. :>
	int rt[N], cnt, sum[N * 400], ls[N * 400], rs[N * 400];
	int cntr, ur[N], cntl, ul[N];
	void add(int &u, int l, int r, int x, int y){
		if (!u) sum[u = ++cnt] = 0, ls[u] = rs[u] = 0;
		if (l == r) return sum[u] += y, void(0);
		int mid = (l + r) >> 1;
		if (x <= mid) add(ls[u], l, mid, x, y);
		else add(rs[u], mid + 1, r, x, y);
		sum[u] = sum[ls[u]] + sum[rs[u]];
	}
	void go_to_ls(){
		for (register int i = 1; i <= cntr; ++i) ur[i] = ls[ur[i]];
		for (register int i = 1; i <= cntl; ++i) ul[i] = ls[ul[i]];
	}
	void go_to_rs(){
		for (register int i = 1; i <= cntr; ++i) ur[i] = rs[ur[i]];
		for (register int i = 1; i <= cntl; ++i) ul[i] = rs[ul[i]];
	}
	int query(int l, int r, int k){
		if (l == r) return l;
		int mid = (l + r) >> 1, S = 0;
		for (register int i = 1; i <= cntr; ++i) S += sum[ls[ur[i]]];
		for (register int i = 1; i <= cntl; ++i) S -= sum[ls[ul[i]]];
		if (k <= S) return go_to_ls(), query(l, mid, k);
		else return go_to_rs(), query(mid + 1, r, k - S);
	}
	void Modify(int x, int y){
		for (register int i = x; i <= n; i += i & -i) add(rt[i], 1, b[t], y, 1);
		if (a[x]) for (register int i = x; i <= n; i += i & -i) add(rt[i], 1, b[t], a[x], -1);
		a[x] = y;
	}
	int Query(int l, int r, int k){
		--l, cntl = cntr = 0;
		for (register int i = l; i; i -= i & -i) ul[++cntl] = rt[i];
		for (register int i = r; i; i -= i & -i) ur[++cntr] = rt[i];
		return query(1, b[t], k);
	}
}T;
int main(){
	scanf("%d%d", &n, &m);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i), b[++t] = a[i];
	for (register int i = 1; i <= m; ++i){
		scanf("%s%d%d", opt[i], x + i, y + i);
		if (opt[i][0] == 'C') b[++t] = y[i]; else scanf("%d", k + i);
	}
	std :: sort(b + 1, b + 1 + t);
	t = std :: unique(b + 1, b + 1 + t) - b - 1;
	for (register int i = 1; i <= n; ++i)
		a[i] = std :: lower_bound(b + 1, b + 1 + t, a[i]) - b;
	for (register int i = 1; i <= m; ++i)
		if (opt[i][0] == 'C') y[i] = std :: lower_bound(b + 1, b + 1 + t, y[i]) - b;
	for (register int i = 1, x; i <= n; ++i) x = a[i], a[i] = 0, T.Modify(i, x);
	for (register int i = 1; i <= m; ++i)
		if (opt[i][0] == 'C') T.Modify(x[i], y[i]);
		else printf("%d\n", b[T.Query(x[i], y[i], k[i])]);
}