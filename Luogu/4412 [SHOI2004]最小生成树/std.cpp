#include <bits/stdc++.h>

template <class Tp>
class Bigraph {
	const Tp INF = std::numeric_limits<Tp>::max();

	int n;
	std::vector<std::vector<Tp>> E;
	std::vector<Tp> a, b;
	std::vector<int> p;

	void bfs(int x) {
		std::vector<bool> vis(n + 1, false);
		std::vector<Tp> d(n + 1, INF);
		std::vector<int> pre(n + 1, -1);
		p[0] = x;
		int u = 0, v = 0;
		while (p[v]) {
			u = p[v];
			vis[v] = true;
			Tp c = INF;
			int nxt = 0;
			for (int i = 1; i <= n; ++i) {
				if (!vis[i]) {
					Tp val = a[u] + b[i] - E[u - 1][i - 1];
					if (val < d[i]) {
						d[i] = val;
						pre[i] = v;
					}
					if (d[i] < c) {
						c = d[i];
						nxt = i;
					}
				}
			}
			for (int i = 0; i <= n; ++i) {
				if (vis[i]) {
					a[p[i]] -= c;
					b[i] += c;
				} else {
					d[i] -= c;
				}
			}
			v = nxt;
		}
		while (v) {
			p[v] = p[pre[v]];
			v = pre[v];
		}
	}

public:
	Bigraph(int _n, std::vector<std::vector<Tp>> _E) : n(_n), E(_E), a(_n + 1), b(_n + 1), p(_n + 1) {}

	std::vector<int> match() {
		for (int i = 1; i <= n; ++i) {
			a[i] = *std::max_element(E[i - 1].begin(), E[i - 1].end());
			b[i] = 0;
			p[i] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			bfs(i);
		}
		std::vector<int> res(n);
		for (int i = 1; i <= n; ++i) {
			res[i - 1] = p[i] - 1;
		}
		return res;
	}
};

const int N = 55, M = 805;

int n, m;

struct Edge {
	int u, v, w;
} edge[M];

bool tree[N][N];
int id[N][N];

std::vector<int> E[N];

int fa[N];

void dfs(int u) {
	for (int v : E[u]) {
		if (fa[u] != v) {
			fa[v] = u;
			dfs(v);
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		std::cin >> edge[i].u >> edge[i].v >> edge[i].w;
		id[edge[i].u][edge[i].v] = i;
		id[edge[i].v][edge[i].u] = i;
	}
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		std::cin >> u >> v;
		tree[u][v] = tree[v][u] = true;
		E[u].push_back(v);
		E[v].push_back(u);
	}

	std::vector<std::vector<int>> a(m, std::vector<int>(m, 0));
	for (int i = 0; i < m; ++i) {
		if (!tree[edge[i].u][edge[i].v]) {
			fa[edge[i].u] = 0;
			dfs(edge[i].u);
			for (int x = edge[i].v; x != edge[i].u; x = fa[x]) {
				int eu = id[x][fa[x]], ev = id[edge[i].u][edge[i].v];
				a[eu][ev] = std::max(edge[eu].w - edge[ev].w, 0);
			}
		}
	}
	Bigraph<int> G(m, a);
	std::vector<int> res(G.match());
	int ans = 0;
	for (int i = 0; i < m; ++i) {
		ans += a[res[i]][i];
	}
	std::cout << ans << "\n";
}