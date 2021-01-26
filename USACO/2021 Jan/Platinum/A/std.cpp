#include <bits/stdc++.h>

const int P = 1000000007;

struct Graph {
	int n;
	std::vector<std::vector<int>> E;

	Graph() : n(0) {}
	Graph(int _n) : n(_n), E(n) {}

	void add_edge(int u, int v) {
		E[u].push_back(v);
		E[v].push_back(u);
	}

	std::pair<std::vector<int>, std::vector<int>> BFS(int s) {
		std::vector<std::vector<int>> dis(2, std::vector<int>(n, 2 * n));
		std::vector<std::pair<int, int>> Q;
		dis[0][s] = 0;
		Q.emplace_back(0, s);
		for (int i = 0; i < (int)Q.size(); ++i) {
			int odd = Q[i].first, u = Q[i].second;
			for (int v : E[u]) {
				if (dis[odd ^ 1][v] == 2 * n) {
					Q.emplace_back(odd ^ 1, v);
					dis[odd ^ 1][v] = dis[odd][u] + 1;
				}
			}
		}
		return std::make_pair(dis[0], dis[1]);
	}
};

std::vector<int> solve(std::vector<std::vector<int>> d) {
	int n = d.size();
	int m = 0;
	for (int i = 0; i < n; ++i) {
		m = std::max(m, (int)d[i].size() + 1);
		for (int j = 1; j < (int)d[i].size(); ++j) {
			d[i][j] += d[i][j - 1];
		}
	}
	std::vector<int> f(m + 1, 1), tag(m, 1);
	auto mul = [&](int x, int v) {
		f[x] = 1ll * f[x] * v % P;
		tag[x] = 1ll * tag[x] * v % P;
	};
	auto down = [&](int x) {
		if (x + 1 < m) {
			mul(x + 1, tag[x]);
		}
		tag[x] = 1;
	};
	for (int i = 0; i < n; ++i) {
		int sz = (int)d[i].size() - 1;
		for (int j = 0; j < sz - 1; ++j) {
			down(j);
			f[j] = 1ll * f[j] * d[i][j] % P;
		}
		mul(sz - 1, d[i][sz - 1]);
		f[m] = 1ll * f[m] * d[i][sz] % P;
	}
	for (int i = 0; i < m; ++i) {
		down(i);
	}
	for (int i = m; i; --i) {
		f[i] = (f[i] + P - f[i - 1]) % P;
	}
	return f;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	std::vector<Graph> G(n);
	std::vector<std::vector<int>> d0(n), d1(n), d2(n);
	for (int i = 0; i < n; ++i) {
		int sz, ec;
		std::cin >> sz >> ec;
		G[i] = Graph(sz);
		for (int j = 0; j < ec; ++j) {
			int u, v;
			std::cin >> u >> v;
			--u, --v;
			G[i].add_edge(u, v);
		}
		std::pair<std::vector<int>, std::vector<int>> dis(G[i].BFS(0));
		d0[i].resize(2 * sz + 1), d1[i].resize(2 * sz + 1), d2[i].resize(2 * sz + 1);
		for (int j = 0; j < sz; ++j) {
			++d0[i][dis.first[j]];
			++d1[i][dis.second[j]];
			++d2[i][std::max(dis.first[j], dis.second[j])];
		}
	}

	std::vector<int> f0(solve(d0)), f1(solve(d1)), f2(solve(d2));
	int ans = 0;
	for (int i = 0; i < (int)f0.size() - 1; ++i) {
		ans = (ans + 1ll * (f0[i] + f1[i]) * i + 1ll * (P - f2[i]) * i) % P;
	}
	std::cout << ans << "\n";
}