#include <bits/stdc++.h>

struct edge {
	int v, id, dir;

	edge() {}
	edge(int _v, int _id, int _dir) : v(_v), id(_id), dir(_dir) {}

	bool operator<(const edge &rhs) const {
		return v < rhs.v;
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int m, n;
	std::cin >> m >> n;
	std::vector<std::vector<edge>> E(n + 1);
	for (int i = 0; i < m; ++i) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int u;
			std::cin >> u;
			--u;
			E[n].emplace_back(u, i, 0);
			E[u].emplace_back(n, i, 1);
		} else {
			int u, v;
			std::cin >> u >> v;
			--u, --v;
			E[u].emplace_back(v, i, 0);
			E[v].emplace_back(u, i, 1);
		}
	}

	std::vector<int> cur(n + 1);
	std::vector<bool> vis(m);
	std::vector<edge> path;

	std::function<void(int)> dfs = [&](int u) {
		while (cur[u] < (int)E[u].size()) {
			edge e = E[u][cur[u]++];
			if (vis[e.id]) {
				continue;
			}
			vis[e.id] = true;
			dfs(e.v);
			path.push_back(e);
		}
	};

	dfs(n);
	std::reverse(path.begin(), path.end());

	std::vector<std::pair<int, edge>> rem;
	for (int u = 0; u < n; ++u) {
		for (auto e : E[u]) {
			if (!vis[e.id] && (u < e.v || (u == e.v && e.dir == 0))) {
				rem.emplace_back(u, e);
			}
		}
	}
	std::sort(rem.begin(), rem.end());

	std::vector<std::pair<int, int>> a, b;
	for (int i = 0; i < (int)rem.size(); i += 2) {
		if (i + 1 < (int)rem.size() && rem[i].first == rem[i + 1].first && rem[i].second.v == rem[i + 1].second.v) {
			a.emplace_back(rem[i].second.id, rem[i].second.dir);
			b.emplace_back(rem[i + 1].second.id, !rem[i + 1].second.dir);
			vis[rem[i].second.id] = true;
			vis[rem[i + 1].second.id] = true;
		} else {
			--i;
		}
	}
	int now = n;
	bool par = false;
	for (auto e : path) {
		if (now == n) {
			par = false;
		}
		par = !par;
		now = e.v;
		if (par) {
			a.emplace_back(e.id, e.dir);
		} else {
			b.emplace_back(e.id, !e.dir);
		}
	}

	std::vector<std::pair<int, int>> ans(a);
	for (int i = 0; i < m; ++i) {
		if (!vis[i]) {
			ans.emplace_back(i, 0);
		}
	}
	ans.insert(ans.end(), b.rbegin(), b.rend());
	for (int i = 0; i < m; ++i) {
		std::cout << ans[i].first + 1 << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < m; ++i) {
		std::cout << ans[i].second << " ";
	}
	std::cout << "\n";
}
