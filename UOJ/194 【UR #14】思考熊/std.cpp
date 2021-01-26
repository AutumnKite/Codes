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

int buf[50000000], *ps = buf;

int *new_vector(int n) {
	int *res = ps;
	ps += n;
	return res;
}

class VirtualTree {
	static const int INF = 0x3f3f3f3f;

public:
	int n, m;

	int *nd, *fa, *f, *g, *id;

	VirtualTree() {}

	VirtualTree(const std::vector<int> &a) {
		n = m = a.size();
		nd = new_vector(m);
		for (int i = 0; i < m; ++i) {
			nd[i] = a[i];
		}
		static int sta[N];
		int top = 0;
		static std::vector<std::pair<int, int>> E[N];

		for (int i = 0; i < m; ++i) {
			E[i].clear();
		}

		auto add = [&](int u) {
			if (!top) {
				sta[top++] = u;
				return;
			}
			int x = sta[top - 1], y, lca = LCA(nd[x], nd[u]);
			if (lca == nd[x]) {
				sta[top++] = u;
				return;
			}
			while (top > 1 && dfn[nd[y = sta[top - 2]]] > dfn[lca]) {
				E[y].emplace_back(x, dis[nd[x]] - dis[nd[y]]);
				x = y;
				--top;
			}
			--top;
			if (!top || lca != nd[sta[top - 1]]) {
				int id = m;
				sta[top++] = id;
				*ps++ = lca, ++m;
				E[id].clear();
			}
			E[sta[top - 1]].emplace_back(x, dis[nd[x]] - dis[nd[sta[top - 1]]]);
			sta[top++] = u;
		};

		for (int i = 0; i < (int)a.size(); ++i) {
			add(i);
		}
		while (top > 1) {
			int x = sta[--top];
			int y = sta[top - 1];
			E[y].emplace_back(x, dis[nd[x]] - dis[nd[y]]);
		}
		int rt = sta[0];

		std::function<void(int)> dfs = [&](int u) {
			*(ps++) = u;
			for (auto p : E[u]) {
				fa[p.first] = u;
				dfs(p.first);
			}
		};

		fa = new_vector(m);
		id = ps;
		dfs(rt);

		f = new_vector(m);
		g = new_vector(m);
		int *fc = new_vector(m);
		for (int i = m - 1; i >= 0; --i) {
			int u = id[i];
			f[u] = u < n ? 0 : -INF;
			fc[u] = -INF;
			for (auto p : E[u]) {
				int v = p.first, w = p.second;
				if (f[v] + w > f[u]) {
					fc[u] = f[u];
					f[u] = f[v] + w;
				} else if (f[v] + w > fc[u]) {
					fc[u] = f[v] + w;
				}
			}
		}
		int *fw = new_vector(m);
		g[rt] = -INF;
		for (int i = 0; i < m; ++i) {
			int u = id[i];
			for (auto p : E[u]) {
				int v = p.first, w = p.second;
				if (f[v] + w == f[u]) {
					g[v] = std::max(g[u] + fw[u], fc[u]);
				} else {
					g[v] = std::max(g[u] + fw[u], f[u]);
				}
				fw[v] = w;
			}
		}
		ps -= 2 * m;
	}

	void operator=(const VirtualTree &a) {
		n = a.n, m = a.m;
		nd = a.nd, fa = a.fa, f = a.f, g = a.g, id = a.id;
	}

	int max_dist(int u) {
		int p = std::lower_bound(id, id + m, u, [&](int x, int y) {
			return dfn[nd[x]] < dfn[y];
		}) - id;
		int v = 0;
		if (p < m) {
			v = std::max(v, LCA(nd[id[p]], u), [&](int x, int y) {
				return dep[x] < dep[y];
			});
		}
		if (p > 0) {
			v = std::max(v, LCA(nd[id[p - 1]], u), [&](int x, int y) {
				return dep[x] < dep[y];
			});
		}
		int q = std::lower_bound(id, id + m, v, [&](int x, int y) {
			return dfn[nd[x]] < dfn[y];
		}) - id;
		return dis[u] - dis[v]
		  + std::max(f[id[q]] + dis[nd[id[q]]] - dis[v], 
		  q ? g[id[q]] + dis[v] - dis[nd[fa[id[q]]]] : -INF);
	}
};

VirtualTree merge(const VirtualTree &a, const VirtualTree &b) {
	std::vector<int> v(a.n + b.n);
	std::merge(a.nd, a.nd + a.n, b.nd, b.nd + b.n, v.begin(), [&](int x, int y) {
		return dfn[x] < dfn[y];
	});
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
	bool ok[N << 2];
	VirtualTree c[N << 2];

	void up(int u) {
		c[u] = merge(c[u << 1], c[u << 1 | 1]);
		ok[u] = true;
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
	void set(int _n) {
		n = _n;
	}

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

	int len() {
		return now;
	}
};

SegmentTree T;

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

	T.set(enlarge_to_pow2(m));
	int ans = 0;
	while (m--) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int x;
			std::cin >> x;
			x = (x ^ abs(ans)) % n + 1;
			T.insert(x);
		} else if (op == 2) {
			T.erase();
		} else if (op == 3) {
			int l, r, x;
			std::cin >> l >> r >> x;
			l = (l ^ abs(ans)) % T.len() + 1;
			r = (r ^ abs(ans)) % T.len() + 1;
			if (l > r) {
				std::swap(l, r);
			}
			x = (x ^ abs(ans)) % n + 1;
			ans = T.query(l - 1, r, x);
			std::cout << ans << "\n";
		}
	}
}