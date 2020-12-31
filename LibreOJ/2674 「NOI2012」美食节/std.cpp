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
	std::vector<int> pre;

	bool SPFA() {
		std::fill(dis.begin(), dis.end(), INF_cost);
		std::fill(pre.begin(), pre.end(), -1);
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
					pre[v] = id;
					vis[v] = true;
					Q.push_back(v);
				}
			}
		}
		return dis[T] < INF_cost;
	}

public:
	MCMF_Network(int _n) : n(_n), E(_n), dis(_n), pre(_n) {}

	void add_edge(int u, int v, Flow cap, Cost cost) {
		E[u].push_back(edge.size()), edge.push_back({u, v, cap, cost});
		E[v].push_back(edge.size()), edge.push_back({v, u, 0, -cost});
	}

	int add_vertex() {
		E.push_back(std::vector<int>());
		dis.push_back(0);
		pre.push_back(0);
		return n++;
	}

	int slope(int _S, int _T, Flow &flow, Cost &cost) {
		S = _S, T = _T;
		if (SPFA()) {
			Flow tmp = INF_flow;
			for (int u = T; u != S; u = edge[pre[u]].u) {
				tmp = std::min(tmp, edge[pre[u]].flow);
			}
			for (int u = T; u != S; u = edge[pre[u]].u) {
				edge[pre[u]].flow -= tmp, edge[pre[u] ^ 1].flow += tmp;
			}
			flow += tmp;
			cost += tmp * dis[T];
			return edge[pre[T]].u;
		} else {
			return -1;
		}
	}
};

const int N = 40, M = 100, SP = 800;

int n, m;
int p[N];
int a[N][M];
int now[M];
int id[M + SP];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		std::cin >> p[i];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> a[i][j];
		}
	}
	
	MCMF_Network<int, int> G(n + 2);
	for (int i = 0; i < n; ++i) {
		G.add_edge(0, i + 2, p[i], 0);
	}
	for (int i = 0; i < m; ++i) {
		now[i] = 0;
	}
	auto add_dish = [&](int x) {
		int t = G.add_vertex();
		id[t - (n + 2)] = x;
		++now[x];
		for (int j = 0; j < n; ++j) {
			G.add_edge(j + 2, t, 1, now[x] * a[j][x]);
		}
		G.add_edge(t, 1, 1, 0);
	};
	for (int i = 0; i < m; ++i) {
		add_dish(i);
	}
	int flow = 0, cost = 0;
	while (1) {
		int t = G.slope(0, 1, flow, cost);
		if (t == -1) {
			break;
		}
		add_dish(id[t - (n + 2)]);
	}
	std::cout << cost << "\n";
}