#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 300005
struct Segment_Tree{
	int val[N << 2], lz[N << 2];
	void up(int u){
		val[u] = std :: min(val[u << 1], val[u << 1 | 1]);
	}
	void add(int u, int x){
		lz[u] += x, val[u] += x;
	}
	void down(int u){
		if (lz[u]) add(u << 1, lz[u]), add(u << 1 | 1, lz[u]), lz[u] = 0;
	}
	void modify(int u, int l, int r, int L, int R, int x){
		if (L <= l && r <= R) return add(u, x), void(0);
		int md = (l + r) >> 1;
		down(u);
		if (L <= md) modify(u << 1, l, md, L, R, x);
		if (R > md) modify(u << 1 | 1, md + 1, r, L, R, x);
		up(u);
	}
	bool query(){ return val[1] >= 0; }
}T;
int n, m, h, a[N], b[N], t, c[N], ans;
int main(){
	n = read(), m = read(), h = read();
	for (register int i = 1; i <= m; ++i) b[i] = h - read(), c[++t] = b[i];
	for (register int i = 1; i <= n; ++i) a[i] = read(), c[++t] = a[i];
	std :: sort(c + 1, c + 1 + t);
	t = std :: unique(c + 1, c + 1 + t) - c - 1;
	for (register int i = 1; i <= m; ++i)
		b[i] = std :: lower_bound(c + 1, c + 1 + t, b[i]) - c;
	for (register int i = 1; i <= n; ++i)
		a[i] = std :: lower_bound(c + 1, c + 1 + t, a[i]) - c;
	for (register int i = 1; i <= m; ++i)
		T.modify(1, 1, t, b[i], t, 1), T.modify(1, 1, t, a[i], t, -1);
	ans = T.query();
	for (register int i = m + 1; i <= n; ++i)
		T.modify(1, 1, t, a[i], t, -1), T.modify(1, 1, t, a[i - m], t, 1), ans += T.query();
	printf("%d\n", ans);
}