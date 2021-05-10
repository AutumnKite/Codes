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

	void add_edge(int u, int v, Flow cap, Cost cost) {
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

struct Point {
	int x, y;

	Point() {}
	Point(int _x, int _y) : x(_x), y(_y) {}
};

long long cross(const Point &a, const Point &b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

class DSU {
	std::vector<int> fa, cnt;

public:
	DSU(int n) : fa(n), cnt(n) {
		for (int i = 0; i < n; ++i) {
			fa[i] = i;
		}
	}

	int find(int x) {
		return fa[x] == x ? x : (fa[x] = find(fa[x]));
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		++cnt[x];
		if (x == y) {
			return false;
		}
		fa[y] = x;
		cnt[x] += cnt[y];
		return true;
	}

	int edge_num(int u) {
		return cnt[find(u)];
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	std::vector<Point> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i].x >> a[i].y;
	}

	auto calc = [&](int u, int v) {
		if (a[u].x >= 0 && a[v].x < 0 && cross(a[v], a[u]) > 0) {
			return 1;
		}
		if (a[u].x <= 0 && a[v].x > 0 && cross(a[u], a[v]) > 0) {
			return -1;
		}
		return 0;
	};

	DSU D(n);
	std::vector<int> d(n);
	MCMF_Network<int, int> G(n + 2);
	int ans = 0;
	for (int i = 0; i < m; ++i) {
		int u, v;
		std::cin >> u >> v;
		--u, --v;
		D.merge(u, v);
		int wuv = calc(u, v), wvu = calc(v, u);
		if (wuv < wvu) {
			std::swap(u, v);
			std::swap(wuv, wvu);
		}
		ans += wuv;
		++d[u], --d[v];
		G.add_edge(u, v, 1, wuv - wvu);
	}
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		if (d[i] & 1 || (0 < D.edge_num(i) && D.edge_num(i) < m)) {
			std::cout << "-1\n";
			return 0;
		}
		if (d[i] > 0) {
			sum += d[i] / 2;
			G.add_edge(n, i, d[i] / 2, 0);
		} else if (d[i] < 0) {
			G.add_edge(i, n + 1, -d[i] / 2, 0);
		}
	}
	int flow, cost;
	G.slope(n, n + 1, flow, cost);
	assert(flow == sum);
	std::cout << ans - cost << "\n";
}
