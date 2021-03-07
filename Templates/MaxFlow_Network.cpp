#include <bits/stdc++.h>

template <class Flow>
class MaxFlow_Network {
	const Flow INF = std::numeric_limits<Flow>::max();

	struct Edge {
		int u, v;
		Flow c;

		Edge() : u(0), v(0), c(0) {}
		Edge(int _u, int _v, Flow _c) : u(_u), v(_v), c(_c) {}
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
		E[u].push_back(edge.size()), edge.push_back(Edge(u, v, c));
		E[v].push_back(edge.size()), edge.push_back(Edge(v, u, 0));
	}

	int edge_size() {
		return edge.size() >> 1;
	}

	void slope(int _S, int _T, Flow &flow) {
		S = _S, T = _T;
		flow = 0;
		while (bfs()) {
			std::fill(iter.begin(), iter.end(), 0);
			flow += dfs(S, INF);
		}
	}

	Flow edge_flow(int id) {
		return edge[id << 1 | 1].c;
	}
};