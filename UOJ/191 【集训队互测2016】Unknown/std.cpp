#include <bits/stdc++.h>

struct Point {
	int x, y;

	Point() {}
	Point(int _x, int _y) : x(_x), y(_y) {}


	Point operator + (const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	Point operator - (const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

	bool operator < (const Point &rhs) const {
		if (x != rhs.x) {
			return x < rhs.x;
		}
		return y < rhs.y;
	}
};

long long cross(const Point &a, const Point &b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

typedef std::vector<Point> Convex;

Convex get_convex(const std::vector<Point> &a) {
	Convex res;
	for (int i = 0; i < (int)a.size(); ++i) {
		while ((int)res.size() >= 2 && cross(res.back() - res[(int)res.size() - 2], a[i] - res.back()) >= 0) {
			res.pop_back();
		}
		res.push_back(a[i]);
	}
	return res;
}

Convex merge(const Convex &a, const Convex &b) {
	std::vector<Point> res(a.size() + b.size());
	std::merge(a.begin(), a.end(), b.begin(), b.end(), res.begin());
	return get_convex(res);
}

Point get_point(const Convex &a, const Point &p) {
	int l = 1, r = (int)a.size() - 1, ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (cross(p, a[mid] - a[mid - 1]) >= 0) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return a[ans];
}

const int P = 998244353;

int tp;
int m;

int get(int n) {
	int res = 1;
	while (res < n) {
		res <<= 1;
	}
	return res;
}

class SegmentTree {
	int n, now;
	std::vector<Convex> c;

	void up(int u) {
		c[u] = merge(c[u << 1], c[u << 1 | 1]);
	}

	void __insert(int u, int l, int r, Point a) {
		if (l + 1 == r) {
			c[u] = Convex(1, a);
			return;
		}
		int mid = (l + r + 1) >> 1;
		if (now <= mid) {
			__insert(u << 1, l, mid, a);
		} else {
			__insert(u << 1 | 1, mid, r, a);
			if (now == r && (u & (u - 1)) && c[u - 1].empty()) {
				up(u - 1);
			}
		}
	}

	void __erase(int u, int l, int r) {
		c[u].clear();
		if (l + 1 == r) {
			return;
		}
		int mid = (l + r + 1) >> 1;
		if (now <= mid) {
			__erase(u << 1, l, mid);
		} else {
			__erase(u << 1 | 1, mid, r);
		}
	}

	long long __query(int u, int l, int r, int L, int R, Point a) {
		if (L <= l && r <= R && !c[u].empty()) {
			return cross(a, get_point(c[u], a));
		}
		int mid = (l + r + 1) >> 1;
		if (R <= mid) {
			return __query(u << 1, l, mid, L, R, a);
		} else if (L >= mid) {
			return __query(u << 1 | 1, mid, r, L, R, a);
		} else {
			return std::max(__query(u << 1, l, mid, L, R, a), __query(u << 1 | 1, mid, r, L, R, a));
		}
	}

public:
	SegmentTree(int _n) : n(_n), now(0), c(n << 1) {}

	void insert(Point a) {
		++now;
		__insert(1, 0, n, a);
	}

	void erase() {
		__erase(1, 0, n);
		--now;
	}

	long long query(int l, int r, Point a) {
		return __query(1, 0, n, l, r, a);
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> tp;
	while (1) {
		std::cin >> m;
		if (m == 0) {
			break;
		}
		SegmentTree T(get(m));
		int ans = 0;
		while (m--) {
			int op;
			std::cin >> op;
			if (op == 1) {
				int x, y;
				std::cin >> x >> y;
				T.insert(Point(x, y));
			} else if (op == 2) {
				T.erase();
			} else if (op == 3) {
				int l, r, x, y;
				std::cin >> l >> r >> x >> y;
				--l;
				ans ^= (T.query(l, r, Point(x, y)) % P + P) % P;
			}
		}
		std::cout << ans << "\n";
	}
}