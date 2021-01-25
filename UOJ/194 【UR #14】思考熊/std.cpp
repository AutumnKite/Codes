#include <bits/stdc++.h>

const int N = 300005, LG = 19;

int n, m;
std::vector<std::pair<int, int>> E[N];

int dep[N];
int dis[N];

int idx, dfn[N];
int Log[N * 2];
int st[LG + 1][N * 2];

void dfs(int u, int fa = 0) {
	dep[u] = dep[fa] + 1;
	dfn[u] = ++idx;
	st[0][idx] = u;
	for (auto p : E[u]) {
		int v = p.first, w = p.second;
		if (v != fa) {
			dis[v] = dis[u] + w;
			dfs(v, u);
			st[0][++idx] = u;
		}
	}
}

int dep_min(int x, int y) {
	return dep[x] < dep[y] ? x : y;
}

void initST() {
	Log[1] = 0;
	for (int i = 2; i <= idx; ++i) {
		Log[i] = Log[i >> 1] + 1;
	}
	for (int j = 1; j <= Log[idx]; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= idx; ++i) {
			st[j][i] = dep_min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
		}
	}
}

int query(int l, int r) {
	int t = Log[r - l + 1];
	return dep_min(st[t][l], st[t][r - (1 << t) + 1]);
}

int LCA(int u, int v) {
	if (dfn[u] > dfn[v]) {
		std::swap(u, v);
	}
	return query(dfn[u], dfn[v]);
}

int dist(int u, int v) {
	return dis[u] + dis[v] - 2 * dis[LCA(u, v)];
}

class VirtualTree {
	const int INF = 0x3f3f3f3f;

	std::vector<int> sta;

	void add(int u) {
		if (sta.empty()) {
			sta.push_back(u);
			return;
		}
		int x = sta.back(), y, lca = LCA(nodes[x], nodes[u]);
		if (lca == nodes[x]) {
			sta.push_back(u);
			return;
		}
		while ((int)sta.size() > 1 && dfn[nodes[y = sta[(int)sta.size() - 2]]] > dfn[lca]) {
			E[y].emplace_back(x, dis[nodes[x]] - dis[nodes[y]]);
			x = y;
			sta.pop_back();
		}
		sta.pop_back();
		if (sta.empty() || lca != sta.back()) {
			int id = nodes.size();
			sta.push_back(id);
			nodes.push_back(lca);
			E.emplace_back();
		}
		E[sta.back()].emplace_back(x, dis[nodes[x]] - dis[nodes[sta.back()]]);
		sta.push_back(u);
	}

	void dfs(int u) {
		dfs_nodes.push_back(nodes[u]);
		dfs_nodes_id.push_back(u);
		for (auto p : E[u]) {
			dfs(p.first);
		}
	}

	void get_f(int u) {
		f[u] = fc[u] = -INF;
		for (auto p : E[u]) {
			int v = p.first, w = p.second;
			get_f(v);
			if (f[v] + w > f[u]) {
				f[u] = f[v] + w;
			} else if (f[v] + w > fc[u]) {
				fc[u] = f[v] + w;
			}
		}
	}

	void get_g(int u) {
		for (auto p : E[u]) {
			int v = p.first, w = p.second;
			if (f[v] + w == f[u]) {
				g[v] = std::max(g[u], fc[u]) + w;
			} else {
				g[v] = std::max(g[u], f[u]) + w;
			}
			get_g(v);
		}
	}

public:
	std::vector<int> key_nodes;
	std::vector<int> nodes;
	std::vector<std::vector<std::pair<int, int>>> E;
	int rt;

	std::vector<int> f, fc, g;
	std::vector<int> mx_dis;

	std::vector<int> dfs_nodes, dfs_nodes_id;

	VirtualTree() : rt(-1) {}

	VirtualTree(const std::vector<int> &a) : key_nodes(a), nodes(a), E(a.size()) {
		for (int i = 0; i < (int)a.size(); ++i) {
			add(i);
		}
		while ((int)sta.size() > 1) {
			int x = sta.back();
			sta.pop_back();
			int y = sta.back();
			E[y].emplace_back(x, dis[nodes[x]] - dis[nodes[y]]);
		}
		rt = sta[0];

		dfs(rt);

		f.resize(nodes.size()), fc.resize(nodes.size()), g.resize(nodes.size());
		get_f(rt);
		g[rt] = 0, get_g(rt);

		mx_dis.resize(nodes.size());
		for (int i = 0; i < (int)nodes.size(); ++i) {
			mx_dis[i] = std::max(f[i], g[i]);
		}
	}

	void operator=(const VirtualTree &a) {
		key_nodes = a.key_nodes, nodes = a.nodes, E = a.E, rt = a.rt;
		f = a.f, fc = a.fc, g = a.g, mx_dis = a.mx_dis;
		dfs_nodes = a.dfs_nodes, dfs_nodes_id = a.dfs_nodes_id;
	}

	int max_dist(int u) {
		int p = std::lower_bound(dfs_nodes.begin(), dfs_nodes.end(), u, [&](int u, int v) {
			return dfn[u] < dfn[v];
		}) - dfs_nodes.begin();
		int ans = -INF;
		if (p < (int)dfs_nodes.size()) {
			ans = std::max(ans, mx_dis[dfs_nodes_id[p]] + dist(dfs_nodes[p], u));
		}
		if (p > 0) {
			ans = std::max(ans, mx_dis[dfs_nodes_id[p - 1]] + dist(dfs_nodes[p - 1], u));
		}
		return ans;
	}
};

VirtualTree merge(const VirtualTree &a, const VirtualTree &b) {
	std::vector<int> av = a.key_nodes, bv = b.key_nodes;
	std::vector<int> v(av.size() + bv.size());
	return VirtualTree(v);
}

int enlarge_to_pow2(int n) {
	int res = 1;
	while (res < n) {
		res <<= 1;
	}
	return res;
}

class SegmentTree {
	int n, now;
	std::vector<bool> ok;
	std::vector<VirtualTree> c;

	void up(int u) {
		c[u] = merge(c[u << 1], c[u << 1 | 1]);
	}

	void __insert(int u, int l, int r, int x) {
		if (l + 1 == r) {
			c[u] = VirtualTree(std::vector<int>(1, x));
			ok[u] = true;
			return;
		}
		int mid = (l + r + 1) >> 1;
		if (now <= mid) {
			__insert(u << 1, l, mid, x);
		} else {
			__insert(u << 1 | 1, mid, r, x);
			if (now == r && (u & (u - 1)) && !ok[u - 1]) {
				up(u - 1);
			}
		}
	}

	void __erase(int u, int l, int r) {
		ok[u] = false;
		if (l + 1 == r) {
			return;
		}
		int mid = (l + r + 1) >> 1;
		if (now <= mid) {
			__erase(u << 1, l, mid);
		} else {
			__erase(u << 1 | 1, mid, r);
		}
	}

	long long __query(int u, int l, int r, int L, int R, int x) {
		if (L <= l && r <= R && ok[u]) {
			return c[u].max_dist(x);
		}
		int mid = (l + r + 1) >> 1;
		if (R <= mid) {
			return __query(u << 1, l, mid, L, R, x);
		} else if (L >= mid) {
			return __query(u << 1 | 1, mid, r, L, R, x);
		} else {
			return std::max(__query(u << 1, l, mid, L, R, x), __query(u << 1 | 1, mid, r, L, R, x));
		}
	}

public:
	SegmentTree(int _n) : n(_n), now(0), ok(n << 1), c(n << 1) {}

	void insert(int a) {
		++now;
		__insert(1, 0, n, a);
	}

	void erase() {
		__erase(1, 0, n);
		--now;
	}

	int query(int l, int r, int a) {
		return __query(1, 0, n, l, r, a);
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		E[u].emplace_back(v, w);
		E[v].emplace_back(u, w);
	}
	dfs(1);
	initST();

	SegmentTree T(enlarge_to_pow2(m));
	int ans = 0, now = 0;
	while (m--) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int x;
			std::cin >> x;
			x = (x ^ abs(ans)) % n + 1;
			T.insert(x);
			++now;
		} else if (op == 2) {
			T.erase();
			--now;
		} else if (op == 3) {
			int l, r, x;
			std::cin >> l >> r >> x;
			l = (l ^ abs(ans)) % now + 1;
			r = (r ^ abs(ans)) % now + 1;
			if (l > r) {
				std::swap(l, r);
			}
			x = (x ^ abs(ans)) % n + 1;
			ans = T.query(l - 1, r, x);
			std::cout << ans << "\n";
		}
	}
}