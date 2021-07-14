#include <bits/stdc++.h>

class segment_tree {
	static int enlarge(int n) {
		int res = 1;
		while (res < n) {
			res <<= 1;
		}
		return res;
	}

	int n;
	std::vector<std::set<std::pair<int, int>>> S;

	void insert(int u, int l, int r, int x, int y, int id) {
		S[u].emplace(y, id);
		if (l + 1 == r) {
			return;
		}
		int mid = (l + r + 1) >> 1;
		if (x < mid) {
			insert(u << 1, l, mid, x, y, id);
		} else {
			insert(u << 1 | 1, mid, r, x, y, id);
		}
	}

	void get(int u, int l, int r, int L, int R, int D, int U, std::vector<int> &id) {
		if (L <= l && r <= R) {
			auto it = S[u].lower_bound(std::make_pair(D, 0));
			while (it != S[u].end() && it->first < U) {
				id.push_back(it->second);
				it = S[u].erase(it);
			}
			return;
		}
		int mid = (l + r + 1) >> 1;
		if (L < mid) {
			get(u << 1, l, mid, L, R, D, U, id);
		}
		if (mid < R) {
			get(u << 1 | 1, mid, r, L, R, D, U, id);
		}
	}

public:
	segment_tree(int _n) : n(_n), S(enlarge(n) << 1) {}

	void insert(int x, int y, int id) {
		insert(1, 0, n, x, y, id);
	}

	std::vector<int> get(int l, int r, int d, int u) {
		std::vector<int> res;
		get(1, 0, n, l, r, d, u, res);
		return res;
	}
};

int main() {
	freopen("jump.in", "r", stdin);
	freopen("jump.out", "w", stdout);

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m, W, H;
	std::cin >> n >> m >> W >> H;
	std::vector<int> x(n), y(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> x[i] >> y[i];
		--x[i], --y[i];
	}
	std::vector<int> t(m), L(m), R(m), D(m), U(m);
	std::vector<std::vector<int>> id(n);
	for (int i = 0; i < m; ++i) {
		int p;
		std::cin >> p >> t[i] >> L[i] >> R[i] >> D[i] >> U[i];
		--p;
		id[p].push_back(i);
		--L[i], --D[i];
	}

	segment_tree T(W);
	for (int i = 0; i < n; ++i) {
		T.insert(x[i], y[i], i);
	}
	std::vector<int> dis(n, 1 << 30);
	std::priority_queue<std::pair<int, int>> Q;
	dis[0] = 0;
	for (int i : id[0]) {
		Q.emplace(-t[i], i);
	}
	std::vector<bool> vis(m);
	while (!Q.empty()) {
		int u = Q.top().second, d = -Q.top().first;
		Q.pop();
		if (vis[u]) {
			continue;
		}
		vis[u] = true;
		auto S = T.get(L[u], R[u], D[u], U[u]);
		for (int x : S) {
			if (d < dis[x]) {
				dis[x] = d;
				for (int i : id[x]) {
					Q.emplace(-dis[x] - t[i], i);
				}
			}
		}
	}
	for (int i = 1; i < n; ++i) {
		std::cout << dis[i] << "\n";
	}
}