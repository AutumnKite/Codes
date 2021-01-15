#include <bits/stdc++.h>

typedef std::vector<int> Point;

long long sqr(int x) {
	return 1ll * x * x;
}

long long dist(const Point &a, const Point &b) {
	long long ans = 0;
	for (int i = 0; i < (int)a.size(); ++i) {
		ans += sqr(a[i] - b[i]);
	}
	return ans;
}

class KD_Tree {
	const long long INF = 0x3f3f3f3f3f3f3f3fll;

	int K;

	struct Node {
		Point v, mx, mn;

		Node() {}

		Node(const Point &a) : v(a), mx(a), mn(a) {}
	};

	int rt;
	std::vector<Node> T;
	std::vector<int> ls, rs;

	int new_node(const Point &a) {
		int u = T.size();
		T.push_back(Node(a));
		ls.push_back(-1), rs.push_back(-1);
		return u;
	}

	void up(int u) {
		T[u].mx = T[u].mn = T[u].v;
		if (ls[u] != -1) {
			for (int i = 0; i < K; ++i) {
				T[u].mx[i] = std::max(T[u].mx[i], T[ls[u]].mx[i]);
				T[u].mn[i] = std::min(T[u].mn[i], T[ls[u]].mn[i]);
			}
		}
		if (rs[u] != -1) {
			for (int i = 0; i < K; ++i) {
				T[u].mx[i] = std::max(T[u].mx[i], T[rs[u]].mx[i]);
				T[u].mn[i] = std::min(T[u].mn[i], T[rs[u]].mn[i]);
			}
		}
	}

	int build(std::vector<Point> &a, int l, int r, int d) {
		if (l >= r) {
			return -1;
		}
		int mid = (l + r) >> 1;
		std::nth_element(a.begin() + l, a.begin() + mid, a.begin() + r, [&](const Point &a, const Point &b) {
			return a[d] < b[d];
		});
		int u = new_node(a[mid]);
		int _ls = build(a, l, mid, (d + 1) % K);
		int _rs = build(a, mid + 1, r, (d + 1) % K);
		ls[u] = _ls, rs[u] = _rs;
		up(u);
		return u;
	}

	long long get_dis(int u, const Point &a) {
		long long ans = 0;
		for (int i = 0; i < K; ++i) {
			if (a[i] < T[u].mn[i]) {
				ans += sqr(T[u].mn[i] - a[i]);
			} else if (a[i] > T[u].mx[i]) {
				ans += sqr(a[i] - T[u].mx[i]);
			}
		}
		return ans;
	}

	void __query(int u, const Point &a, std::priority_queue<std::pair<long long, Point>> &Q) {
		long long dl = INF, dr = INF;
		if (ls[u] != -1) {
			dl = get_dis(ls[u], a);
		}
		if (rs[u] != -1) {
			dr = get_dis(rs[u], a);
		}
		long long d = dist(T[u].v, a);
		if (d < Q.top().first) {
			Q.pop();
			Q.emplace(d, T[u].v);
		}
		if (dl < dr) {
			if (dl < Q.top().first) {
				__query(ls[u], a, Q);
				if (dr < Q.top().first) {
					__query(rs[u], a, Q);
				}
			}
		} else {
			if (dr < Q.top().first) {
				__query(rs[u], a, Q);
				if (dl < Q.top().first) {
					__query(ls[u], a, Q);
				}
			}
		}
	}

public:
	KD_Tree() : rt(-1) {}

	KD_Tree(std::vector<Point> a, int k) : K(k) {
		rt = build(a, 0, a.size(), 0);
	}

	std::vector<Point> query(const Point &a, int m) {
		std::priority_queue<std::pair<long long, Point>> Q;
		for (int i = 0; i < m; ++i) {
			Q.emplace(INF, Point(K));
		}
		__query(rt, a, Q);
		std::vector<Point> res(m);
		for (int i = m - 1; i >= 0; --i) {
			res[i] = Q.top().second;
			Q.pop();
		}
		return res;
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, k;
	while (std::cin >> n >> k) {
		std::vector<Point> a(n, Point(k));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < k; ++j) {
				std::cin >> a[i][j];
			}
		}

		KD_Tree T(a, k);
		
		int q;
		std::cin >> q;
		while (q--) {
			Point p(k);
			for (int i = 0; i < k; ++i) {
				std::cin >> p[i];
			}
			int m;
			std::cin >> m;
			std::vector<Point> res;
			res = T.query(p, m);
			std::cout << "the closest " << m << " points are:\n";
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < k; ++j) {
					std::cout << res[i][j] << " \n"[j == k - 1];
				}
			}
		}
	}
}