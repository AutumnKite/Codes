#include <bits/stdc++.h>

const long long INF = 0x3f3f3f3f3f3f3f3fll;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	std::vector<std::map<int, std::vector<std::pair<int, long long>>>> E(n);
	std::vector<std::map<int, long long>> sum(n);
	std::vector<std::map<int, long long>> dis(n);
	for (int i = 0; i < m; ++i) {
		int u, v, c;
		long long w;
		std::cin >> u >> v >> c >> w;
		--u, --v, --c;
		E[u][c].emplace_back(v, w);
		E[v][c].emplace_back(u, w);
		sum[u][c] += w;
		sum[v][c] += w;
		dis[u][c] = dis[v][c] = INF;
	}
	for (int i = 0; i < n; ++i) {
		dis[i][-1] = INF;
	}

	std::vector<std::set<int>> vis(n);
	std::priority_queue<std::tuple<long long, int, int>> Q;
	Q.emplace(0, 0, -1);
	dis[0][-1] = 0;
	while (!Q.empty()) {
		int u = std::get<1>(Q.top()), c = std::get<2>(Q.top());
		Q.pop();
		if (vis[u].count(c)) {
			continue;
		}
		vis[u].insert(c);
		if (c == -1) {
			for (const auto &p : E[u]) {
				long long tot = sum[u][p.first];
				for (auto e : p.second) {
					int v = e.first, nc = p.first;
					if (!vis[v].count(nc) && dis[u][c] < dis[v][nc]) {
						dis[v][nc] = dis[u][c];
						Q.emplace(-dis[v][nc], v, nc);
					}
					long long w = std::min(e.second, tot - e.second);
					if (!vis[v].count(-1) && dis[u][c] + w < dis[v][-1]) {
						dis[v][-1] = dis[u][c] + w;
						Q.emplace(-dis[v][-1], v, -1);
					}
				}
			}
		} else {
			for (auto e : E[u][c]) {
				int v = e.first;
				long long w = sum[u][c] - e.second;
				if (!vis[v].count(-1) && dis[u][c] + w < dis[v][-1]) {
					dis[v][-1] = dis[u][c] + w;
					Q.emplace(-dis[v][-1], v, -1);
				}
			}
		}
	}
	long long ans = dis[n - 1][-1];
	if (ans == INF) {
		std::cout << -1 << "\n";
	} else {
		std::cout << ans << "\n";
	}
}
