#include <bits/stdc++.h>

template <class Flow>
class MaxFlow_Network {
	const Flow INF = std::numeric_limits<Flow>::max();

	struct Edge {
		int u, v;
		Flow c;
	};

	int n, S, T;
	std::vector<Edge> edge;
	std::vector<std::vector<int>> E;

	std::vector<int> dep;

	bool bfs() {
		std::fill(dep.begin(), dep.end(), -1);
		std::vector<int> Q;
		dep[S] = 0;
		Q.push_back(S);
		if (S == T) {
			return true;
		}
		for (int i = 0; i < (int)Q.size(); ++i) {
			int u = Q[i];
			for (int id : E[u]) {
				int v = edge[id].v;
				Flow c = edge[id].c;
				if (c > 0 && dep[v] == -1) {
					dep[v] = dep[u] + 1;
					Q.push_back(v);
					if (v == T) {
						return true;
					}
				}
			}
		}
		return false;
	}

	std::vector<int> iter;

	Flow dfs(int u, Flow flow) {
		if (u == T || !flow) {
			return flow;
		}
		Flow res = 0;
		for (int &i = iter[u]; i < (int)E[u].size(); ++i) {
			int id = E[u][i];
			int v = edge[id].v;
			Flow c = edge[id].c;
			if (dep[v] == dep[u] + 1) {
				Flow tmp = dfs(v, std::min(flow, c));
				if (tmp) {
					edge[id].c -= tmp, edge[id ^ 1].c += tmp;
					res += tmp, flow -= tmp;
					if (!flow) {
						break;
					}
				}
			}
		}
		if (!res) {
			dep[u] = -1;
		}
		return res;
	}

public:
	MaxFlow_Network(int _n) : n(_n), E(_n), dep(_n), iter(_n) {}

	void add_edge(int u, int v, Flow c) {
		E[u].push_back(edge.size()), edge.push_back({u, v, c});
		E[v].push_back(edge.size()), edge.push_back({v, u, 0});
	}

	Flow slope(int _S, int _T) {
		S = _S, T = _T;
		Flow ans = 0;
		while (bfs()) {
			std::fill(iter.begin(), iter.end(), 0);
			ans += dfs(S, INF);
		}
		return ans;
	}

	Flow edge_flow(int id) {
		return edge[id << 1 | 1].c;
	}
};

const int N = 105, M = 1005;

int n, m, c, mx;

struct Edge {
	int u, v, w;
} E[M];

int max_flow;

bool check(double mid) {
	MaxFlow_Network<double> G(n);
	for (int i = 0; i < m; ++i) {
		G.add_edge(E[i].u, E[i].v, std::min<double>(E[i].w, mid));
	}
	return G.slope(0, n - 1) >= max_flow;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cout.setf(std::ios::fixed);
	std::cout.precision(4);

	std::cin >> n >> m >> c;
	MaxFlow_Network<int> G(n);
	for (int i = 0; i < m; ++i) {
		std::cin >> E[i].u >> E[i].v >> E[i].w;
		--E[i].u, --E[i].v;
		mx = std::max(mx, E[i].w);
		G.add_edge(E[i].u, E[i].v, E[i].w);
	}
	max_flow = G.slope(0, n - 1);

	double l = 0, r = mx, ans = 0;
	for (int i = 0; i < 60; ++i) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			ans = mid;
			r = mid;
		} else {
			l = mid;
		}
	}

	std::cout << max_flow << "\n";
	std::cout << ans * c << "\n";
}