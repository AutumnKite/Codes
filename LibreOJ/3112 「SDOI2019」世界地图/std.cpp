#include <bits/stdc++.h>

namespace Gen {
	unsigned SA, SB, SC;
	int lim;

	void init() {
		std::cin >> SA >> SB >> SC >> lim;
	}

	int getweight() {
		SA ^= SA << 16;
		SA ^= SA >> 5;
		SA ^= SA << 1;
		unsigned int t = SA;
		SA = SB;
		SB = SC;
		SC ^= t ^ SA;
		return SC % lim + 1;
	}
}

struct Edge {
	int u, v, w;

	Edge() : u(0), v(0), w(0) {}
	Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

	bool operator < (const Edge &rhs) const {
		return w < rhs.w;
	}
};

struct MST {
	int n;
	long long sum;
	std::vector<Edge> E;

	MST() : n(0), sum(0) {}
	MST(int _n, long long _sum, const std::vector<Edge> &_E) : n(_n), sum(_sum), E(_E) {}
};

MST one_col(const std::vector<int> &w) {
	std::vector<Edge> E(w.size());
	for (int i = 0; i < (int)w.size(); ++i) {
		E[i].u = i, E[i].v = i + 1, E[i].w = w[i];
	}
	return MST((int)w.size() + 1, 0, E);
}

struct DSU {
	std::vector<int> fa;

	DSU() {}
	DSU(int n) : fa(n) {
		for (int i = 0; i < n; ++i) {
			fa[i] = i;
		}
	}

	int find(int x) {
		return fa[x] == x ? x : (fa[x] = find(fa[x]));
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) {
			return false;
		}
		fa[y] = x;
		return true;
	}
};

MST merge(const MST &A, const MST &B, const std::vector<int> &w) {
	int n = A.n + B.n;
	std::vector<Edge> graph;
	for (auto e : A.E) {
		graph.push_back(Edge(e.u, e.v, e.w));
	}
	for (auto e : B.E) {
		graph.push_back(Edge(e.u + A.n, e.v + A.n, e.w));
	}
	for (int i = 0; i < (int)w.size(); ++i) {
		graph.push_back(Edge(A.n - (int)w.size() + i, A.n + i, w[i]));
	}
	std::sort(graph.begin(), graph.end());

	DSU S(n);
	std::vector<std::vector<std::pair<int, int>>> E(n);
	for (auto e : graph) {
		if (S.merge(e.u, e.v)) {
			E[e.u].push_back({e.v, e.w});
			E[e.v].push_back({e.u, e.w});
		}
	}

	std::vector<int> id(n, -1);

	std::function<bool(int, int)> build = [&](int u, int fa) {
		int d = 0;
		for (auto p : E[u]) {
			int v = p.first;
			if (v != fa) {
				d += build(v, u);
			}
		}
		if (d >= 2 || u < (int)w.size() || u >= n - (int)w.size()) {
			id[u] = 0;
		}
		return d > 0 || id[u] != -1;
	};

	build(0, 0);
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (id[i] != -1) {
			id[i] = cnt++;
		}
	}

	long long sum = A.sum + B.sum;
	std::vector<Edge> nE;

	std::function<void(int, int, int, int)> dfs = [&](int u, int fa, int lst, int mx) {
		if (id[u] != -1) {
			if (lst != -1) {
				sum -= mx;
				nE.push_back(Edge(lst, id[u], mx));
			}
			mx = 0;
			lst = id[u];
		}
		for (auto p : E[u]) {
			int v = p.first, w = p.second;
			if (v != fa) {
				sum += w;
				dfs(v, u, lst, std::max(mx, w));
			}
		}
	};
	
	dfs(0, 0, -1, 0);
	return MST(cnt, sum, nE);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	Gen::init();
	std::vector<std::vector<int>> a(m, std::vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			a[j][i] = Gen::getweight();
		}
	}
	std::vector<std::vector<int>> b(m, std::vector<int>(n - 1, 0));
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < m; ++j) {
			b[j][i] = Gen::getweight();
		}
	}

	std::vector<MST> pre(m), suf(m);
	pre[0] = one_col(b[0]);
	for (int i = 1; i < m; ++i) {
		pre[i] = merge(pre[i - 1], one_col(b[i]), a[i - 1]);
	}
	suf[m - 1] = one_col(b[m - 1]);
	for (int i = m - 2; i >= 0; --i) {
		suf[i] = merge(one_col(b[i]), suf[i + 1], a[i]);
	}

	int q;
	std::cin >> q;
	while (q--) {
		int l, r;
		std::cin >> l >> r;
		l -= 2;
		MST ans = merge(suf[r], pre[l], a[m - 1]);
		long long sum = ans.sum;
		for (auto e : ans.E) {
			sum += e.w;
		}
		std::cout << sum << "\n";
	}
}
