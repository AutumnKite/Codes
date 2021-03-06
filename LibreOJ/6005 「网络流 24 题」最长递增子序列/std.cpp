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

	std::vector<int> iter;

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

	void addEdge(int u, int v, Flow c) {
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
};

const int N = 505, INF = 0x3f3f3f3f;

int n;
int a[N];
int f[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}

	int res = 0;
	for (int i = 1; i <= n; ++i) {
		f[i] = 1;
		for (int j = 1; j < i; ++j) {
			if (a[j] <= a[i]) {
				f[i] = std::max(f[i], f[j] + 1);
			}
		}
		res = std::max(res, f[i]);
	}
	std::cout << res << "\n";

	MaxFlow_Network<int> G1(2 * n + 2);
	for (int i = 1; i <= n; ++i) {
		G1.addEdge(i * 2, i * 2 + 1, 1);
		if (f[i] == 1) {
			G1.addEdge(0, i * 2, 1);
		}
		for (int j = 1; j < i; ++j) {
			if (a[j] <= a[i] && f[i] == f[j] + 1) {
				G1.addEdge(j * 2 + 1, i * 2, 1);
			}
		}
		if (f[i] == res) {
			G1.addEdge(i * 2 + 1, 1, 1);
		}
	}
	std::cout << G1.slope(0, 1) << "\n";

	if (n == 1) {
		std::cout << 1 << "\n";
		return 0;
	}

	MaxFlow_Network<int> G2(2 * n + 2);
	for (int i = 1; i <= n; ++i) {
		G2.addEdge(i * 2, i * 2 + 1, i == 1 || i == n ? INF : 1);
		if (f[i] == 1) {
			G2.addEdge(0, i * 2, i == 1 ? INF : 1);
		}
		for (int j = 1; j < i; ++j) {
			if (a[j] <= a[i] && f[i] == f[j] + 1) {
				G2.addEdge(j * 2 + 1, i * 2, 1);
			}
		}
		if (f[i] == res) {
			G2.addEdge(i * 2 + 1, 1, i == n ? INF : 1);
		}
	}
	std::cout << G2.slope(0, 1) << "\n";
}