#include <cstdio>
#include <cctype>
#include <assert.h>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch) && ch != EOF; ch = getchar()) if (ch == '-') f ^= 1;
	if (ch == EOF) return -1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define N 100005
int n, k, a[N], id[N], opt;
struct Segment_Tree{
	int mx[N << 2];
	long long lz[N << 2], sum[N << 2];
	void modify_a(int u, int l, int r, int x, int v){
		if (l == r) return mx[u] = v, void(0);
		int md = (l + r) >> 1;
		if (x <= md) modify_a(u << 1, l, md, x, v);
		else modify_a(u << 1 | 1, md + 1, r, x, v);
		mx[u] = std :: max(mx[u << 1], mx[u << 1 | 1]);
	}
	int getl(int u, int l, int r, int x){
		if (l == r) return l < x && mx[u] >= a[x] ? l : 0;
		int md = (l + r) >> 1, res = 0;
		if (x > md + 1 && mx[u << 1 | 1] >= a[x]) res = getl(u << 1 | 1, md + 1, r, x);
		return res ? res : getl(u << 1, l, md, x);
	}
	int getr(int u, int l, int r, int x){
		if (l == r) return l > x && mx[u] >= a[x] ? l : n + 1;
		int md = (l + r) >> 1, res = n + 1;
		if (x < md && mx[u << 1] >= a[x]) res = getr(u << 1, l, md, x);
		return res <= n ? res : getr(u << 1 | 1, md + 1, r, x);
	}
	void add(int u, int l, int r, long long v){
		sum[u] += (r - l + 1) * v, lz[u] += v;
	}
	void down(int u, int l, int md, int r){
		if (lz[u]) add(u << 1, l, md, lz[u]), add(u << 1 | 1, md + 1, r, lz[u]), lz[u] = 0;
	}
	void modify_e(int u, int l, int r, int x, int v){
		if (l == r) return sum[u] = v, void(0);
		int md = (l + r) >> 1;
		down(u, l, md, r);
		if (x <= md) modify_e(u << 1, l, md, x, v);
		else modify_e(u << 1 | 1, md + 1, r, x, v);
		sum[u] = sum[u << 1] + sum[u << 1 | 1];
	}
	void inc_e(int u, int l, int r, int L, int R, int v){
		if (L <= l && r <= R) return add(u, l, r, v), void(0);
		int md = (l + r) >> 1;
		down(u, l, md, r);
		if (L <= md) inc_e(u << 1, l, md, L, R, v);
		if (R > md) inc_e(u << 1 | 1, md + 1, r, L, R, v);
		sum[u] = sum[u << 1] + sum[u << 1 | 1];
	}
	long long query(int u, int l, int r, int L, int R){
		if (L <= l && r <= R) return sum[u];
		int md = (l + r) >> 1;
		down(u, l, md, r);
		long long res = 0;
		if (L <= md) res += query(u << 1, l, md, L, R);
		if (R > md) res += query(u << 1 | 1, md + 1, r, L, R);
		return res;
	}
}T;
void update(int x, int pl, int pr){
	int p = a[pl] <= a[pr] ? pl : pr, w = 0;
	if (p && p <= n) w = T.query(1, 1, n, p, p) + (a[x] != a[p]);
	T.modify_e(1, 1, n, x, w);
}
void modify(int x, int pl, int pr, int w){
	if (a[pl] > a[x] && pl + 1 < x) T.inc_e(1, 1, n, pl + 1, x - 1, w);
	if (a[pr] > a[x] && x < pr - 1) T.inc_e(1, 1, n, x + 1, pr - 1, w);
}
bool cmp(int x, int y){
	return a[x] > a[y] || (a[x] == a[y] && x < y);
}
int main(){
	n = read(), k = read(), a[0] = a[n + 1] = 0x3f3f3f3f;
	for (register int i = 1; i <= n; ++i) a[i] = read(), id[i] = i;
	std :: sort(id + 1, id + 1 + n, cmp);
	for (register int i = 1; i <= n; ++i)
		T.modify_a(1, 1, n, id[i], a[id[i]]), update(id[i], T.getl(1, 1, n, id[i]), T.getr(1, 1, n, id[i]));
	while (opt = read(), opt == 1 || opt == 2){
		if (opt == 1){
			int x = read(), y = x + 1, l, r;
			if (a[x] == a[y]) continue;
			modify(x, T.getl(1, 1, n, x), T.getr(1, 1, n, x), -1);
			modify(y, T.getl(1, 1, n, y), T.getr(1, 1, n, y), -1);
			std :: swap(a[x], a[y]);
			T.modify_a(1, 1, n, x, a[x]), T.modify_a(1, 1, n, y, a[y]);
			if (a[x] < a[y]) std :: swap(x, y);
			update(x, l = T.getl(1, 1, n, x), r = T.getr(1, 1, n, x)), modify(x, l, r, 1);
			update(y, l = T.getl(1, 1, n, y), r = T.getr(1, 1, n, y)), modify(y, l, r, 1);
		}
		else{
			int l = read(), r = read();
			printf("%lld\n", T.query(1, 1, n, l, r) * k + 1ll * (r - l + 1) * (n - 1));
		}
	}
}