#include <cstdio>
#include <algorithm>
#define N 100005
int n, q, a[N], p[N], ans;
bool b[N];
struct Segment_Tree{
	int val[N << 2];
	void build(int u, int l, int r){
		if (l == r) return val[u] = a[l], void(0);
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r);
		val[u] = std :: max(val[u << 1], val[u << 1 | 1]);
	}
	void modify(int u, int l, int r, int x, int y){
		if (l == r) return val[u] = y, (void)0;
		int md = (l + r) >> 1;
		if (x <= md) modify(u << 1, l, md, x, y);
		else modify(u << 1 | 1, md + 1, r, x, y);
		val[u] = std :: max(val[u << 1], val[u << 1 | 1]);
	}
	int query(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return val[u];
		int md = (l + r) >> 1, ans = 0;
		if (L <= md) ans = std :: max(ans, query(u << 1, l, md, L, R));
		if (R > md) ans = std :: max(ans, query(u << 1 | 1, md + 1, r, L, R));
		return ans;
	}
}T;
bool check(int i){
	return p[i] + 1 > p[i + 1] - 1 || T.query(1, 1, n, p[i] + 1, p[i + 1] - 1) < i;
}
void set(int x, bool y){
	if (!b[x] && y) ++ans, b[x] = y;
	if (b[x] && !y) --ans, b[x] = y;
}
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i), p[a[i]] = i;
	T.build(1, 1, n);
	ans = 0;
	for (register int i = 1; i < n; ++i)
		if (check(i)) b[i] = 1, ++ans; else b[i] = 0;
	scanf("%d", &q);
	for (register int i = 1, x; i <= q; ++i){
		scanf("%d", &x);
		std :: swap(p[a[x]], p[a[x + 1]]), std :: swap(a[x], a[x + 1]);
		T.modify(1, 1, n, x, a[x]), T.modify(1, 1, n, x + 1, a[x + 1]);
		if (a[x] > 1) set(a[x] - 1, check(a[x] - 1));
		if (a[x] < n) set(a[x], check(a[x]));
		if (a[x + 1] > 1) set(a[x + 1] - 1, check(a[x + 1] - 1));
		if (a[x + 1] < n) set(a[x + 1], check(a[x + 1]));
		printf(ans == n - 1 ? "Yes\n" : "No\n");
	}
}