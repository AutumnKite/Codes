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

	Flow edge_flow(int id) {
		return edge[id << 1 | 1].c;
	}
};

const int N = 1005, M = 2005;

int n, m, mx;

struct Edge {
	int u, v, a, b;
} edge[M];

int d[N];

int in[N], out[N];

bool get_graph(int mid, MaxFlow_Network<int> &G) {
	for (int i = 1; i <= n; ++i) {
		in[i] = out[i] = false;
	}
	for (int i = 1; i <= m; ++i) {
		if (edge[i].a <= mid) {
			++out[edge[i].u];
			++in[edge[i].v];
		} else {
			return false;
		}
	}
	int res = 0;
	for (int i = 1; i <= n; ++i) {
		if (out[i] < in[i]) {
			G.addEdge(0, i, (in[i] - out[i]) >> 1);
			res += (in[i] - out[i]) >> 1;
		} else if (in[i] < out[i]) {
			G.addEdge(i, n + 1, (out[i] - in[i]) >> 1);
		}
	}
	for (int i = 1; i <= m; ++i) {
		if (edge[i].b <= mid) {
			G.addEdge(edge[i].v, edge[i].u, 1);
		}
	}
	return G.slope(0, n + 1) == res;
}

bool check(int mid) {
	MaxFlow_Network<int> G(n + 2);
	return get_graph(mid, G);
}

std::vector<std::pair<int, int>> E[N];
int iter[N];
bool vis[M];
int top, sta[M];

void dfs(int u) {
	for (int &i = iter[u]; i < (int)E[u].size(); ++i) {
		int v = E[u][i].first, id = E[u][i].second;
		if (vis[id]) {
			continue;
		}
		vis[id] = true;
		dfs(v);
		sta[++top] = id;
	}
}

std::vector<int> euler_circuit(int mid) {
	MaxFlow_Network<int> G(n + 2);
	assert(get_graph(mid, G));
	int idx = 0;
	for (int i = 1; i <= n; ++i) {
		idx += in[i] != out[i];
	}
	for (int i = 1; i <= m; ++i) {
		if (edge[i].b <= mid && G.edge_flow(idx)) {
			E[edge[i].v].push_back({edge[i].u, i});
		} else {
			E[edge[i].u].push_back({edge[i].v, i});
		}
		idx += edge[i].b <= mid;
	}
	dfs(1);
	std::vector<int> res;
	while (top) {
		res.push_back(sta[top]);
		--top;
	}
	return res;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		std::cin >> edge[i].u >> edge[i].v >> edge[i].a >> edge[i].b;
		if (edge[i].a > edge[i].b) {
			std::swap(edge[i].u, edge[i].v);
			std::swap(edge[i].a, edge[i].b);
		}
		mx = std::max(mx, edge[i].b);
		++d[edge[i].u], ++d[edge[i].v];
	}
	for (int i = 1; i <= n; ++i) {
		if (d[i] & 1) {
			std::cout << "NIE\n";
			return 0;
		}
	}

	int l = 0, r = mx, ans = mx;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}

	std::cout << ans << "\n";
	std::vector<int> path = euler_circuit(ans);
	for (int v : path) {
		std::cout << v << " ";
	}
	std::cout << "\n";
}