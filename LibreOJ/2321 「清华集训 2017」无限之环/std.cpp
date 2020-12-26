#include <bits/stdc++.h>

template <class Flow, class Cost>
class MCMF_Network {
	const Flow INF_flow = std::numeric_limits<Flow>::max();
	const Cost INF_cost = std::numeric_limits<Cost>::max();

	struct Edge {
		int u, v;
		Flow flow;
		Cost cost;
	};

	int n, S, T;
	std::vector<Edge> edge;
	std::vector<std::vector<int>> E;

	std::vector<Cost> dis;

	bool SPFA() {
		std::fill(dis.begin(), dis.end(), INF_cost);
		std::vector<bool> vis(n);
		std::vector<int> Q;
		dis[S] = 0;
		vis[S] = true;
		Q.push_back(S);
		for (int i = 0; i < (int)Q.size(); ++i) {
			int u = Q[i];
			vis[u] = false;
			for (int id : E[u]) {
				int v = edge[id].v;
				Flow flow = edge[id].flow;
				Cost cost = edge[id].cost;
				if (flow > 0 && dis[u] + cost < dis[v]) {
					dis[v] = dis[u] + cost;
					vis[v] = true;
					Q.push_back(v);
				}
			}
		}
		return dis[T] < INF_cost;
	}

	std::vector<int> iter;
	std::vector<bool> vis;

	Flow dfs(int u, Flow all) {
		if (u == T || !all) {
			return all;
		}
		vis[u] = true;
		Flow res = 0;
		for (int &i = iter[u]; i < (int)E[u].size(); ++i) {
			int id = E[u][i];
			int v = edge[id].v;
			Flow flow = edge[id].flow;
			Cost cost = edge[id].cost;
			if (!vis[v] && dis[v] == dis[u] + cost) {
				Flow tmp = dfs(v, std::min(all, flow));
				if (tmp) {
					edge[id].flow -= tmp, edge[id ^ 1].flow += tmp;
					res += tmp, all -= tmp;
					if (!all) {
						break;
					}
				}
			}
		}
		vis[u] = false;
		if (!res) {
			dis[u] = INF_cost;
		}
		return res;
	}

public:
	MCMF_Network(int _n) : n(_n), E(_n), dis(_n), iter(_n), vis(_n) {}

	void addEdge(int u, int v, Flow cap, Cost cost) {
		E[u].push_back(edge.size()), edge.push_back({u, v, cap, cost});
		E[v].push_back(edge.size()), edge.push_back({v, u, 0, -cost});
	}

	void slope(int _S, int _T, Flow &flow, Cost &cost) {
		std::fill(vis.begin(), vis.end(), false);
		S = _S, T = _T;
		flow = 0;
		cost = 0;
		while (SPFA()) {
			std::fill(iter.begin(), iter.end(), 0);
			Flow tmp = dfs(S, INF_flow);
			flow += tmp;
			cost += tmp * dis[T];
		}
	}

	Flow edge_flow(int id) {
		return edge[id << 1 | 1].flow;
	}
};

const int N = 2005;

int n, m, a[N][N];
int id[N][N][5];

/*
 * 0 - up
 * 1 - right
 * 2 - down
 * 3 - left
 */

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	int cnt = 2;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			std::cin >> a[i][j];
			for (int k = 0; k < 5; ++k) {
				id[i][j][k] = cnt;
				++cnt;
			}
		}
	}

	MCMF_Network<int, int> G(cnt);
	auto addEdge = [&](int u, int v, int cap, int cost, int dir) {
		if (dir == 0) {
			G.addEdge(u, v, cap, cost);
		} else {
			G.addEdge(v, u, cap, cost);
		}
	};
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (i < n) {
				addEdge(id[i][j][2], id[i + 1][j][0], 1, 0, (i + j) & 1);
			}
			if (j < m) {
				addEdge(id[i][j][1], id[i][j + 1][3], 1, 0, (i + j) & 1);
			}
			int t = __builtin_popcount(a[i][j]);
			if ((i + j) & 1) {
				G.addEdge(id[i][j][4], 1, t, 0);
			} else {
				G.addEdge(0, id[i][j][4], t, 0);
				sum += t;
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			int v = a[i][j];
			int t = __builtin_popcount(v);
			if (!t) {
				continue;
			}
			if (v == 5 || v == 10) {
				for (int k = 0; k < 4; ++k) {
					if (v >> k & 1) {
						addEdge(id[i][j][4], id[i][j][k], 1, 0, (i + j) & 1);
					}
				}
				continue;
			}
			if (t == 1) {
				int p = 0;
				while (!(v >> p & 1)) {
					++p;
				}
				for (int k = 0; k < 4; ++k) {
					int w = std::min((k + 4 - p) % 4, (p + 4 - k) % 4);
					addEdge(id[i][j][4], id[i][j][k], 1, w, (i + j) & 1);
				}
				continue;
			}
			if (t == 2) {
				for (int k = 0; k < 4; ++k) {
					if (v >> k & 1) {
						addEdge(id[i][j][4], id[i][j][k], 1, 0, (i + j) & 1);
						addEdge(id[i][j][k], id[i][j][(k + 2) % 4], 1, 1, (i + j) & 1);
					}
				}
				continue;
			}
			if (t == 3) {
				int p = 0;
				while (v >> p & 1) {
					++p;
				}
				for (int k = 0; k < 4; ++k) {
					if (v >> k & 1) {
						int w = std::min((k + 4 - p) % 4, (p + 4 - k) % 4);
						addEdge(id[i][j][4], id[i][j][k], 1, 0, (i + j) & 1);
						addEdge(id[i][j][k], id[i][j][p], 1, w, (i + j) & 1);
					}
				}
				continue;
			}
			if (t == 4) {
				for (int k = 0; k < 4; ++k) {
					addEdge(id[i][j][4], id[i][j][k], 1, 0, (i + j) & 1);
				}
				continue;
			}
		}
	}
	
	int flow, cost;
	G.slope(0, 1, flow, cost);

	int idx = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (i < n) {
				++idx;
			}
			if (j < m) {
				++idx;
			}
			int t = __builtin_popcount(a[i][j]);
			if (G.edge_flow(idx) < t) {
				std::cout << -1 << "\n";
				return 0;
			}
			++idx;
		}
	}
	std::cout << cost << "\n";
}