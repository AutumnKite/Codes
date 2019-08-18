#include <cstdio>
#include <cctype>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) ch == '-' ? f = 0 : 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x;
}
#define N 50005
int n, m, a[N];
int rnd(){
	static int seed = 19260817;
	return seed = ((1ll * seed * 14078917 + 72813473) % 1000000007 * 36947741ll + 52175171) % 998244353;
}
struct Segment_FHQ_Treap{
	int rt[N << 2], cnt, val[N << 5], key[N << 5], sz[N << 5], ls[N << 5], rs[N << 5], x, y, z;
	int new_node(int v){
		return val[++cnt] = v, key[cnt] = rnd(), ls[cnt] = rs[cnt] = 0, sz[cnt] = 1, cnt;
	}
	void update(int u){
		sz[u] = sz[ls[u]] + sz[rs[u]] + 1;
	}
	void split(int u, int v, int &x, int &y){
		if (!u) return x = 0, y = 0, void(0);
		if (v <= val[u]) split(ls[u], v, x, y), ls[u] = y, update(u), y = u;
		else split(rs[u], v, x, y), rs[u] = x, update(u), x = u;
	}
	void split_num(int u, int v, int &x, int &y){
		if (!u) return x = 0, y = 0, void(0);
		if (v <= sz[ls[u]]) split_num(ls[u], v, x, y), ls[u] = y, update(u), y = u;
		else split_num(rs[u], v - sz[ls[u]] - 1, x, y), rs[u] = x, update(u), x = u;
	}
	int merge(int u, int v){
		if (!u || !v) return u + v;
		if (key[u] < key[v]) return rs[u] = merge(rs[u], v), update(u), u;
		else return ls[v] = merge(u, ls[v]), update(v), v;
	}
	void Insert(int &Rt, int v){
		split(Rt, v, x, y), Rt = merge(merge(x, new_node(v)), y);
	}
	void Delete(int &Rt, int v){
		split(Rt, v, x, y), split_num(y, 1, y, z), Rt = merge(x, z);
	}
	int Rank(int u, int v){
		return !u ? 0 : (v <= val[u] ? Rank(ls[u], v) : Rank(rs[u], v) + sz[ls[u]] + 1);
	}
	void build(int u, int l, int r){
		if (l == r) return rt[u] = new_node(a[l]), void(0);
		int mid = (l + r) >> 1;
		build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
		for (register int i = l; i <= r; ++i) Insert(rt[u], a[i]);
	}
	void Modify(int u, int l, int r, int x, int y){ // Note: After this, don't forget a[x] = y.
		if (l == r) return val[rt[u]] = y, void(0);
		int mid = (l + r) >> 1;
		if (x <= mid) Modify(u << 1, l, mid, x, y);
		else Modify(u << 1 | 1, mid + 1, r, x, y);
		Delete(rt[u], a[x]), Insert(rt[u], y);
	}
	int Rank(int u, int l, int r, int L, int R, int x){ // Note: The real rank must +1.
		if (L <= l && r <= R) return Rank(rt[u], x);
		int mid = (l + r) >> 1, ans = 0;
		if (L <= mid) ans += Rank(u << 1, l, mid, L, R, x);
		if (R > mid) ans += Rank(u << 1 | 1, mid + 1, r, L, R, x);
		return ans;
	}
	int Kth(int L, int R, int K){
		int l = 0, r = 2e8, mid, ans = -2147483647;
		while (l <= r)
			Rank(1, 1, n, L, R, mid = (l + r) >> 1) + 1 <= K ? l = mid + 1, ans = mid : r = mid - 1;
		return ans == 2e8 ? 2147483647 : ans;
	}
}T;
int main(){
	n = read(), m = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	T.build(1, 1, n);
	while (m--){
		int opt = read(), l = read(), r = read();
		if (opt == 1) printf("%d\n", T.Rank(1, 1, n, l, r, read()) + 1);
		if (opt == 2) printf("%d\n", T.Kth(l, r, read()));
		if (opt == 3) T.Modify(1, 1, n, l, r), a[l] = r;
		if (opt == 4) printf("%d\n", T.Kth(l, r, T.Rank(1, 1, n, l, r, read())));
		if (opt == 5) printf("%d\n", T.Kth(l, r, T.Rank(1, 1, n, l, r, read() + 1) + 1));
	}
}