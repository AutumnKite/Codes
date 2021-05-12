#include <bits/stdc++.h>

void solve() {
	int n;
	std::cin >> n;
	std::vector<std::vector<int>> E(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		std::cin >> u >> v;
		--u, --v;
		E[u].push_back(v);
		E[v].push_back(u);
	}

	std::vector<std::tuple<int, int, int, int>> ans;

	std::function<int(int, int)> dfs = [&](int u, int fa) {
		int lst = u;
		for (int v : E[u]) {
			if (v != fa) {
				int leaf = dfs(v, u);
				if (lst != u) {
					ans.emplace_back(u, v, lst, v);
				}
				lst = leaf;
			}
		}
		return lst;
	};

	for (int i = 0; i < n; ++i) {
		if ((int)E[i].size() <= 1) {
			dfs(i, -1);
			break;
		}
	}

	std::cout << ans.size() << "\n";
	for (auto p : ans) {
		std::cout << std::get<0>(p) + 1 << " " << std::get<1>(p) + 1 << " "
		          << std::get<2>(p) + 1 << " " << std::get<3>(p) + 1 << "\n";
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int T;
	std::cin >> T;
	while (T--) {
		solve();
	}
}
