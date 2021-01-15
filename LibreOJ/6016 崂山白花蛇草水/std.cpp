#include <bits/stdc++.h>

const int K = 2;

struct Point {
	int a[2];

	Point() {
		a[0] = a[1] = 0;
	}

	int &operator[](int x) {
		return a[x];
	}

	const int &operator[](int x) const {
		return a[x];
	}
};

class KD_Tree {
	static const int N = 3000005;

	const int INF = 0x3f3f3f3f;
	const double alpha = 0.75;

	struct Node {
		Point v, mx, mn;
		int sz;

		Node() : sz(0) {}

		Node(const Point &a) : v(a), mx(a), mn(a), sz(1) {}
	};

	int cnt;
	Node T[N];
	int ls[N], rs[N];

	int top, rub[N];

	int new_node(const Point &a) {
		int u = top ? rub[--top] : cnt++;
		T[u] = Node(a);
		ls[u] = rs[u] = -1;
		return u;
	}

	void up(int u) {
		T[u].mx = T[u].mn = T[u].v;
		T[u].sz = 1;
		if (ls[u] != -1) {
			T[u].sz += T[ls[u]].sz;
			for (int i = 0; i < K; ++i) {
				T[u].mx[i] = std::max(T[u].mx[i], T[ls[u]].mx[i]);
				T[u].mn[i] = std::min(T[u].mn[i], T[ls[u]].mn[i]);
			}
		}
		if (rs[u] != -1) {
			T[u].sz += T[rs[u]].sz;
			for (int i = 0; i < K; ++i) {
				T[u].mx[i] = std::max(T[u].mx[i], T[rs[u]].mx[i]);
				T[u].mn[i] = std::min(T[u].mn[i], T[rs[u]].mn[i]);
			}
		}
	}

	int build(Point *a, int l, int r, int d) {
		if (l >= r) {
			return -1;
		}
		int mid = (l + r) >> 1;
		std::nth_element(a + l, a + mid, a + r, [&](const Point &a, const Point &b) {
			return a[d] < b[d];
		});
		int u = new_node(a[mid]);
		int _ls = build(a, l, mid, (d + 1) % K);
		int _rs = build(a, mid + 1, r, (d + 1) % K);
		ls[u] = _ls, rs[u] = _rs;
		up(u);
		return u;
	}

	int __insert(int u, const Point &a, int d, int &lst, int &ld) {
		if (u == -1) {
			return new_node(a);
		}
		if (a[d] <= T[u].v[d]) {
			int _ls = __insert(ls[u], a, (d + 1) % K, lst, ld);
			ls[u] = _ls;
			up(u);
			if (T[ls[u]].sz > T[u].sz * alpha) {
				lst = u;
				ld = d;
			}
		} else {
			int _rs = __insert(rs[u], a, (d + 1) % K, lst, ld);
			rs[u] = _rs;
			up(u);
			if (T[rs[u]].sz > T[u].sz * alpha) {
				lst = u;
				ld = d;
			}
		}
		return u;
	}

	void get_points(int u, Point *res, int &n) {
		if (u == -1) {
			return;
		}
		res[n++] = T[u].v;
		get_points(ls[u], res, n);
		get_points(rs[u], res, n);
		rub[top++] = u;
	}

	bool inclusive(int u, const Point &mn, const Point &mx) {
		for (int i = 0; i < K; ++i) {
			if (T[u].mn[i] < mn[i] || T[u].mx[i] > mx[i]) {
				return false;
			}
		}
		return true;
	}

	bool intersect(int u, const Point &mn, const Point &mx) {
		for (int i = 0; i < K; ++i) {
			if (T[u].mx[i] < mn[i] || T[u].mn[i] > mx[i]) {
				return false;
			}
		}
		return true;
	}

	bool contain(int u, const Point &mn, const Point &mx) {
		for (int i = 0; i < K; ++i) {
			if (T[u].v[i] < mn[i] || T[u].v[i] > mx[i]) {
				return false;
			}
		}
		return true;
	}

	int __query(int u, const Point &mn, const Point &mx) {
		if (u == -1 || !intersect(u, mn, mx)) {
			return 0;
		}
		if (inclusive(u, mn, mx)) {
			return T[u].sz;
		}
		return contain(u, mn, mx) + __query(ls[u], mn, mx) + __query(rs[u], mn, mx);
	}

public:
	KD_Tree() {}

	void insert(int &rt, const Point &a) {
		int lst = -1, ld = -1;
		rt = __insert(rt, a, 0, lst, ld);
		if (lst != -1) {
			static Point tmp[N];
			int n = 0;
			get_points(lst, tmp, n);
			assert(lst == build(tmp, 0, n, ld));
		}
	}

	int query(int rt, const Point &mn, const Point &mx) {
		return __query(rt, mn, mx);
	}
} KDT;

class SegmentTree {
	static const int N = 3000005;

	int Rt;
	int cnt;
	int ls[N], rs[N];
	int rt[N];

	int new_node() {
		int u = cnt++;
		rt[u] = -1;
		ls[u] = rs[u] = -1;
		return u;
	}

	void __insert(int &u, int l, int r, int x, const Point &p) {
		if (u == -1) {
			u = new_node();
		}
		KDT.insert(rt[u], p);
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid) {
			__insert(ls[u], l, mid, x, p);
		} else {
			__insert(rs[u], mid + 1, r, x, p);
		}
	}

	int __query(int u, int l, int r, int k, const Point &mn, const Point &mx) {
		if (l == r) {
			return l;
		}
		int mid = (l + r) >> 1;
		int tmp = rs[u] == -1 ? 0 : KDT.query(rt[rs[u]], mn, mx);
		if (k <= tmp) {
			return __query(rs[u], mid + 1, r, k, mn, mx);
		} else {
			return __query(ls[u], l, mid, k - tmp, mn, mx);
		}
	}

public:
	SegmentTree() : Rt(-1) {}

	void insert(const Point &a, int v) {
		__insert(Rt, 1, 1000000000, v, a);
	}

	int query(const Point &mn, const Point &mx, int k) {
		if (Rt == -1 || k > KDT.query(rt[Rt], mn, mx)) {
			return -1;
		}
		return __query(Rt, 1, 1000000000, k, mn, mx);
	}
} T;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, q;
	std::cin >> n >> q;
	int ans = 0;
	while (q--) {
		int op;
		std::cin >> op;
		if (op == 1) {
			Point p;
			int v;
			std::cin >> p[0] >> p[1] >> v;
			p[0] ^= ans, p[1] ^= ans, v ^= ans;
			T.insert(p, v);
		} else {
			Point mn, mx;
			int k;
			std::cin >> mn[0] >> mn[1] >> mx[0] >> mx[1] >> k;
			mn[0] ^= ans, mn[1] ^= ans, mx[0] ^= ans, mx[1] ^= ans, k ^= ans;
			ans = T.query(mn, mx, k);
			if (ans == -1) {
				std::cout << "NAIVE!ORZzyz.\n";
				ans = 0;
			} else {
				std::cout << ans << "\n";
			}
		}
	}
}