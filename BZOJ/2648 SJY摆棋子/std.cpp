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

int dist(const Point &a, const Point &b) {
	int ans = 0;
	for (int i = 0; i < K; ++i) {
		ans += abs(a[i] - b[i]);
	}
	return ans;
}

class KD_Tree {
	static const int N = 1000005;

	const int INF = 0x3f3f3f3f;
	const double alpha = 0.75;

	struct Node {
		Point v, mx, mn;
		int sz;

		Node() : sz(0) {}

		Node(const Point &a) : v(a), mx(a), mn(a), sz(1) {}
	};

	int rt;
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

	int get_dis(int u, const Point &a) {
		int ans = 0;
		for (int i = 0; i < K; ++i) {
			if (a[i] < T[u].mn[i]) {
				ans += abs(T[u].mn[i] - a[i]);
			} else if (a[i] > T[u].mx[i]) {
				ans += abs(a[i] - T[u].mx[i]);
			}
		}
		return ans;
	}

	void __query(int u, const Point &a, std::pair<int, Point> &now) {
		int dl = INF, dr = INF;
		if (ls[u] != -1) {
			dl = get_dis(ls[u], a);
		}
		if (rs[u] != -1) {
			dr = get_dis(rs[u], a);
		}
		int d = dist(T[u].v, a);
		if (d < now.first) {
			now = std::make_pair(d, T[u].v);
		}
		if (dl < dr) {
			if (dl < now.first) {
				__query(ls[u], a, now);
				if (dr < now.first) {
					__query(rs[u], a, now);
				}
			}
		} else {
			if (dr < now.first) {
				__query(rs[u], a, now);
				if (dl < now.first) {
					__query(ls[u], a, now);
				}
			}
		}
	}

public:
	KD_Tree() : rt(-1) {}

	KD_Tree(Point *a, int n) {
		rt = build(a, 0, n, 0);
	}

	Point query(const Point &a) {
		std::pair<int, Point> now(INF, Point());
		__query(rt, a, now);
		return now.second;
	}

	void insert(const Point &a) {
		int lst = -1, ld = -1;
		rt = __insert(rt, a, 0, lst, ld);
		if (lst != -1) {
			static Point tmp[N];
			int n = 0;
			get_points(lst, tmp, n);
			assert(lst == build(tmp, 0, n, ld));
		}
	}
};

Point a[500005];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, q;
	std::cin >> n >> q;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 2; ++j) {
			std::cin >> a[i][j];
		}
	}
	KD_Tree T(a, n);

	while (q--) {
		int op;
		std::cin >> op;
		Point p;
		for (int i = 0; i < 2; ++i) {
			std::cin >> p[i];
		}
		if (op == 1) {
			T.insert(p);
		} else {
			std::cout << dist(p, T.query(p)) << "\n";
		}
	}
}