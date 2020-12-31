#include <bits/stdc++.h>

const int N = 40005;

int n, a[N], sum[N];
int m, l[N], r[N], v[N];

class SegmentTree {
	static const int N = ::N << 2;

	int val[N];
	int tag[N];

	void add(int u, int v) {
		val[u] += v;
		tag[u] += v;
	}

	void down(int u) {
		add(u << 1, tag[u]);
		add(u << 1 | 1, tag[u]);
		tag[u] = 0;
	}

public:
	void build(int u, int l, int r, int *a) {
		if (l == r) {
			val[u] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(u << 1, l, mid, a);
		build(u << 1 | 1, mid + 1, r, a);
		val[u] = std::min(val[u << 1], val[u << 1 | 1]);
	}

	void modify(int u, int l, int r, int L, int R, int v) {
		if (L <= l && r <= R) {
			add(u, v);
			return;
		}
		int mid = (l + r) >> 1;
		down(u);
		if (L <= mid) {
			modify(u << 1, l, mid, L, R, v);
		}
		if (R > mid) {
			modify(u << 1 | 1, mid + 1, r, L, R, v);
		}
		val[u] = std::min(val[u << 1], val[u << 1 | 1]);
	}

	int query(int u, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return val[u];
		}
		int mid = (l + r) >> 1;
		down(u);
		if (R <= mid) {
			return query(u << 1, l, mid, L, R);
		} else if (L > mid) {
			return query(u << 1 | 1, mid + 1, r, L, R);
		} else {
			return std::min(query(u << 1, l, mid, L, R), query(u << 1 | 1, mid + 1, r, L, R));
		}
	}
} Tx, Ty;

void read_seq() {
	std::cin >> n;
	int x, y, z, P;
	std::cin >> x >> y >> z >> P;
	for (int i = 1; i <= n; ++i) {
		a[i] = (1ll * (x - i) * (x - i) + 1ll * (y - i) * (y - i) + 1ll * (z - i) * (z - i)) % P;
	}
}

void read_query() {
	std::cin >> m;
	int x, y, z, P;
	std::cin >> v[1] >> v[2] >> x >> y >> z >> P;
	for (int i = 3; i <= m; ++i) {
		v[i] = (1ll * x * v[i - 1] + 1ll * y * v[i - 2] + z) % P;
	}
	for (int i = 1; i <= m; ++i) {
		std::cin >> l[i] >> r[i];
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	read_seq();
	read_query();

	for (int i = 1; i <= n; ++i) {
		sum[i] = sum[i - 1] + a[i];
	}
	Ty.build(1, 0, n, sum);
	for (int i = 1; i <= n; ++i) {
		sum[i] = -sum[i];
	}
	Tx.build(1, 0, n, sum);

	for (int i = 1; i <= m; ++i) {
		int s = Ty.query(1, 0, n, r[i], n) + Tx.query(1, 0, n, 0, l[i] - 1);
		s = std::min(s, v[i]);
		std::cout << s << "\n";
		Ty.modify(1, 0, n, r[i], n, -s);
		Tx.modify(1, 0, n, l[i], n, s);
	}
}