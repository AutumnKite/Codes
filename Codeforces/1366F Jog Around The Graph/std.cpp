#include <bits/stdc++.h>

const int P = 1000000007;
const int INF = 2000000001;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m, q;
	std::cin >> n >> m >> q;
	std::vector<std::vector<std::pair<int, int>>> E(n);
	std::vector<int> mx(n);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		--u, --v;
		E[u].emplace_back(v, w);
		E[v].emplace_back(u, w);
		mx[u] = std::max(mx[u], w);
		mx[v] = std::max(mx[v], w);
	}

	std::vector<int> f(n, -INF), b(n, -INF);
	f[0] = 0;
	for (int i = 0; i < n; ++i) {
		std::vector<int> g(n, -INF);
		for (int u = 0; u < n; ++u) {
			if (f[u] != -INF) {
				b[u] = std::max(b[u], f[u] - mx[u] * i);
				for (auto [v, w] : E[u]) {
					g[v] = std::max(g[v], f[u] + w);
				}
			}
		}
	}

	std::vector<int> id(n);
	std::iota(id.begin(), id.end(), 0);
	std::sort(id.begin(), id.end(), [&](int x, int y) {
		return mx[x] < mx[y];
	});

	std::vector<int> sta;
	for (int i : id) {
		while ((int)sta.size() > 1 && 
	}
}