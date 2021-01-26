#include <bits/stdc++.h>

const int N = 50005, M = 55;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n, m;
int bel[N];

bool a[M][M];

std::vector<int> id[M];

struct Graph {
	static const int N = ::N * 3;

	std::vector<std::pair<int, int>> G[N];

	void add_edge(int u, int v, int w) {
		G[u].emplace_back(v, w);
	}

	bool vis[N];
	long long dis[N];

	long long dijkstra(int n, int s, int t) {
		for (int i = 0; i < n; ++i) {
			dis[i] = INF;
			vis[i] = false;
		}
		std::priority_queue<std::pair<long long, int>> Q;
		dis[s] = 0;
		Q.emplace(0, s);
		while (!Q.empty()) {
			int u = Q.top().second;
			Q.pop();
			if (vis[u]) {
				continue;
			}
			vis[u] = true;
			for (auto p : G[u]) {
				int v = p.first, w = p.second;
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					Q.emplace(-dis[v], v);
				}
			}
		}
		return dis[t];
	}
} G;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		std::cin >> bel[i];
		--bel[i];
		id[bel[i]].push_back(i);
	}
	for (int i = 0; i < m; ++i) {
		std::string str;
		std::cin >> str;
		for (int j = 0; j < m; ++j) {
			a[i][j] = str[j] - '0';
		}
	}
	for (int i = 0; i < n; ++i) {
		G.add_edge(i + n, i, 0);
		G.add_edge(i + 2 * n, i, 0);
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 1; j < (int)id[i].size(); ++j) {
			G.add_edge(id[i][j - 1] + n, id[i][j] + n, id[i][j] - id[i][j - 1]);
			G.add_edge(id[i][j] + 2 * n, id[i][j - 1] + 2 * n, id[i][j] - id[i][j - 1]);
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!id[j].empty() && a[bel[i]][j]) {
				int pl = std::lower_bound(id[j].begin(), id[j].end(), i) - id[j].begin();
				int pr = std::upper_bound(id[j].begin(), id[j].end(), i) - id[j].begin() - 1;
				if (pl < (int)id[j].size()) {
					G.add_edge(i, id[j][pl] + n, id[j][pl] - i);
				}
				if (pr >= 0) {
					G.add_edge(i, id[j][pr] + 2 * n, i - id[j][pr]);
				}
			}
		}
	}

	long long ans = G.dijkstra(n * 3, 0, n - 1);
	if (ans == INF) {
		std::cout << -1 << "\n";
	} else {
		std::cout << ans << "\n";
	}
}