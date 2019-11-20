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
const int N = 500005, INF = 0x3f3f3f3f;
int n, m, cnt, p[N << 1], ans;
struct node{
	int l, r, len;
	bool operator < (const node &rhs) const { return len < rhs.len; }
}a[N];
struct segt{
	int mx[N << 3], lz[N << 3];
	void up(int u){ mx[u] = std :: max(mx[u << 1], mx[u << 1 | 1]); }
	void add(int u, int v){ mx[u] += v, lz[u] += v; }
	void down(int u){
		if (lz[u]) add(u << 1, lz[u]), add(u << 1 | 1, lz[u]), lz[u] = 0;
	}
	void modify(int u, int l, int r, int L, int R, int v){
		if (L <= l && r <= R) return add(u, v), void(0);
		int md = (l + r) >> 1;
		down(u);
		if (L <= md) modify(u << 1, l, md, L, R, v);
		if (R > md) modify(u << 1 | 1, md + 1, r, L, R, v);
		up(u);
	}
}T;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i){
		a[i].l = read(), a[i].r = read(), a[i].len = a[i].r - a[i].l;
		p[++cnt] = a[i].l, p[++cnt] = a[i].r;
	}
	std :: sort(p + 1, p + 1 + cnt);
	cnt = std :: unique(p + 1, p + 1 + cnt) - p - 1;
	for (register int i = 1; i <= n; ++i){
		a[i].l = std :: lower_bound(p + 1, p + 1 + cnt, a[i].l) - p;
		a[i].r = std :: lower_bound(p + 1, p + 1 + cnt, a[i].r) - p;
	}
	std :: sort(a + 1, a + 1 + n);
	ans = INF;
	for (register int i = 1, j = 1; i <= n; ++i){
		while (j <= n && T.mx[1] < m) T.modify(1, 1, cnt, a[j].l, a[j].r, 1), ++j;
		if (T.mx[1] >= m) ans = std :: min(ans, a[j - 1].len - a[i].len);
		T.modify(1, 1, cnt, a[i].l, a[i].r, -1);
	}
	if (ans == INF) puts("-1"); else printf("%d\n", ans);
}
