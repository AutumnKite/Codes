#include <bits/stdc++.h>

const int N = 100005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n, q;
int lst[N];
long long t[N], w[N], sum, a[N];

long long times(long long a, long long b) {
	return !b || a < INF / b ? a * b : INF;
}

long long plus(long long a, long long b) {
	return a + b < INF ? a + b : INF;
}

struct Line {
	long long k, b;

	Line() {}
	Line(long long _k, long long _b) : k(_k), b(_b) {}

	long long get(long long x) {
		return plus(times(k, x), b);
	}
};

struct LiChaoTree {
	static const int N = ::N * 50;

	int cnt, ls[N], rs[N];
	Line val[N];

	void clear() {
		cnt = 0;
	}

	void insert(int &u, long long l, long long r, Line v) {
		if (!u) {
			u = ++cnt;
			ls[u] = rs[u] = 0;
			val[u] = v;
			return;
		}
		if (val[u].get(l) <= v.get(l) && val[u].get(r) <= v.get(r)) {
			return;
		}
		if (v.get(l) <= val[u].get(l) && v.get(r) <= val[u].get(r)) {
			val[u] = v;
			return;
		}
		long long mid = (l + r) >> 1;
		if (v.get(mid) <= val[u].get(mid)) {
			std::swap(val[u], v);
		}
		if (v.get(l) <= val[u].get(l)) {
			insert(ls[u], l, mid, v);
		} else {
			insert(rs[u], mid + 1, r, v);
		}
	}

	long long query(int u, long long l, long long r, long long x) {
		if (!u) {
			return INF;
		}
		if (l == r) {
			return val[u].get(x);
		}
		long long mid = (l + r) >> 1;
		if (x <= mid) {
			return std::min(val[u].get(x), query(ls[u], l, mid, x));
		} else {
			return std::min(val[u].get(x), query(rs[u], mid + 1, r, x));
		}
	}
} __T;

struct SegmentTree {
	static const int N = ::N << 2;

	int rt[N];

	void build(int u, int l, int r) {
		rt[u] = 0;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}

	void modify(int u, int l, int r, int x, Line v) {
		__T.insert(rt[u], 0, sum, v);
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid) {
			modify(u << 1, l, mid, x, v);
		} else {
			modify(u << 1 | 1, mid + 1, r, x, v);
		}
	}
	
	long long query(int u, int l, int r, int L, int R, long long x) {
		if (L <= l && r <= R) {
			return __T.query(rt[u], 0, sum, x);
		}
		int mid = (l + r) >> 1;
		if (R <= mid) {
			return query(u << 1, l, mid, L, R, x);
		} else if (L > mid) {
			return query(u << 1 | 1, mid + 1, r, L, R, x);
		} else {
			return std::min(query(u << 1, l, mid, L, R, x), query(u << 1 | 1, mid + 1, r, L, R, x));
		}
	}
} T;

long long tmp[N];
long long f[N], minf[N];

void solve(int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	tmp[mid] = 0;
	minf[mid + 1] = INF;
	minf[mid] = f[mid];
	for (int i = mid; i > l; --i) {
		tmp[i - 1] = std::max(tmp[i], t[i]);
		minf[i - 1] = std::min(minf[i], f[i - 1]);
	}
	__T.clear();
	T.build(1, l, mid);
	for (int i = l; i <= mid; ++i) {
		T.modify(1, l, mid, i, Line(tmp[i], f[i]));
	}
	long long mx = 0;
	int pr = mid;
	for (int i = mid + 1; i <= r; ++i) {
		mx = std::max(mx, t[i]);
		while (pr >= l && tmp[pr] < mx) {
			--pr;
		}
		int pl = std::max(lst[i], l);
		if (pl <= mid) {
			f[i] = std::min(f[i], plus(times(mx, a[i]), minf[std::max(pr + 1, pl)]));
			if (pl <= pr) {
				f[i] = std::min(f[i], T.query(1, l, mid, pl, pr, a[i]));
			}
		}
	}
	solve(mid + 1, r);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> lst[i] >> t[i] >> w[i];
		sum += w[i];
	}
	a[n] = 0;
	for (int i = n; i; --i) {
		a[i - 1] = plus(a[i], w[i]);
	}

	f[0] = 0;
	for (int i = 1; i <= n; ++i) {
		f[i] = INF;
	}
	solve(0, n);

	std::cout << f[n] << "\n";
}