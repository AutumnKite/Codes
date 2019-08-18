#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
#define N 20005
int n, q, m, a[N], b[N], rt[N], tmp[4];
std :: vector<int> pos[N];
struct node{
	int sum, pre, suf;
	node operator + (const node &res) const {
		node ret;
		ret.sum = sum + res.sum;
		ret.pre = std :: max(pre, sum + res.pre);
		ret.suf = std :: max(res.suf, suf + res.sum);
		return ret;
	}
};
struct Segment_Tree{
	int cnt, ls[N * 18], rs[N * 18];
	node a[N * 18];
	void build(int &u, int l, int r){
		u = ++cnt;
		if (l == r) return a[u] = (node){-1, -1, -1}, void(0);
		int md = (l + r) >> 1;
		build(ls[u], l, md), build(rs[u], md + 1, r);
		a[u] = a[ls[u]] + a[rs[u]];
	}
	void insert(int &u, int u_, int l, int r, int x){
//		printf("%d %d %d %d %d\n", u, u_, l, r, x);
		u = ++cnt, ls[u] = ls[u_], rs[u] = rs[u_];
		if (l == r) return a[u] = (node){1, 1, 1}, void(0);
		int md = (l + r) >> 1;
		if (x <= md) insert(ls[u], ls[u_], l, md, x);
		else insert(rs[u], rs[u_], md + 1, r, x);
		a[u] = a[ls[u]] + a[rs[u]];
	}
	node query(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return a[u];
		int md = (l + r) >> 1;
		if (R <= md) return query(ls[u], l, md, L, R);
		else if (L > md) return query(rs[u], md + 1, r, L, R);
		else return query(ls[u], l, md, L, R) + query(rs[u], md + 1, r, L, R);
	}
//	void print(int u){
//		if (!u) return;
//		printf("%d: %d %d %d\n", u, a[u].sum, a[u].pre, a[u].suf);
//		print(ls[u]), print(rs[u]);
//	}
}T;
bool check(int md){
	int s = 0;
	if (tmp[1] + 1 <= tmp[2] - 1) s += T.query(rt[md], 1, n, tmp[1] + 1, tmp[2] - 1).sum;
	s += T.query(rt[md], 1, n, tmp[0], tmp[1]).suf + T.query(rt[md], 1, n, tmp[2], tmp[3]).pre;
	return s >= 0;
}
int main(){
	n = read();
	for (register int i = 1; i <= n; ++i) a[i] = b[i] = read();
	std :: sort(b + 1, b + 1 + n);
	m = std :: unique(b + 1, b + 1 + n) - b - 1;
	for (register int i = 1; i <= n; ++i)
		a[i] = std :: lower_bound(b + 1, b + 1 + m, a[i]) - b;
	for (register int i = 1; i <= n; ++i) pos[a[i]].push_back(i);
	T.build(rt[m + 1], 1, n);
//	T.print(rt[m + 1]);
	for (register int i = m; i; --i)
		for (register int j = 0, last = rt[i + 1]; j < pos[i].size(); ++j)
			T.insert(rt[i], last, 1, n, pos[i][j]), last = rt[i];
	int ans = 0;
	q = read();
	while (q--){
		for (register int i = 0; i < 4; ++i) tmp[i] = (read() + ans) % n + 1;
		std :: sort(tmp, tmp + 4);
		int l = 1, r = m, md;
		while (l <= r) if (check(md = (l + r) >> 1)) ans = md, l = md + 1; else r = md - 1;
		ans = b[ans];
		printf("%d\n", ans);
	}
}
