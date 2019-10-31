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
const int N = 500005;
int n, m, a[N], c[N], fa[N], sz[N], id[N];
double k;
namespace segt{
	int val[N << 2], lz[N << 2];
	void build(int u, int l, int r){
		lz[u] = 0;
		if (l == r) return val[u] = c[l], void(0);
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r);
		val[u] = std :: min(val[u << 1], val[u << 1 | 1]);
	}
	void add(int u, int v){ val[u] += v, lz[u] += v; }
	void down(int u){
		if (lz[u]) add(u << 1, lz[u]), add(u << 1 | 1, lz[u]), lz[u] = 0;
	}
	void modify(int u, int l, int r, int L, int R, int v){
		if (L <= l && r <= R) return add(u, v), void(0);
		int md = (l + r) >> 1;
		down(u);
		if (L <= md) modify(u << 1, l, md, L, R, v);
		if (R > md) modify(u << 1 | 1, md + 1, r, L, R, v);
		val[u] = std :: min(val[u << 1], val[u << 1 | 1]);
	}
	int query(int u, int l, int r, int v){
		if (l == r) return val[u] >= v ? l : l - 1;
		int md = (l + r) >> 1;
		down(u);
		if (val[u << 1] >= v) return query(u << 1 | 1, md + 1, r, v);
		else return query(u << 1, l, md, v);
	}
}
int main(){
	n = read(), scanf("%lf", &k);
	for (register int i = 1; i <= n; ++i) a[i] = read();
	std :: sort(a + 1, a + 1 + n);
	m = 1, c[1] = 1;
	for (register int i = 2; i <= n; ++i)
		if (a[i] == a[i - 1]) ++c[m];
		else a[++m] = a[i], c[m] = 1;
	for (register int i = m - 1; i; --i) c[i] += c[i + 1];
	for (register int i = n; i; --i) ++sz[i], sz[fa[i] = int(i / k)] += sz[i];
	segt :: build(1, 1, m);
	for (register int i = 1; i <= n; ++i){
		if (fa[i] && fa[i] != fa[i - 1]) segt :: modify(1, 1, m, 1, id[fa[i]], sz[fa[i]] - 1);
		int k = segt :: query(1, 1, m, sz[i]);
		segt :: modify(1, 1, m, 1, k, -sz[i]);
		printf("%d ", a[id[i] = k]);
	}
}
