#include <bits/stdc++.h>

const int N = 100005, B = 400, LG = 17;

int n, q;
std::vector<std::pair<int, int>> E[N];

struct Tree {
	static const int N = ::N * 2, LG = ::LG + 1;

	int cnt;
	std::vector<int> E[N * 2];

	void add_edge(int u, int v, int w) {
		int lst = u;
		for (int i = 1; i < w; ++i) {
			++cnt;
			E[lst].push_back(cnt);
			E[cnt].push_back(lst);
			lst = cnt;
		}
		E[lst].push_back(v);
		E[v].push_back(lst);
	}

	int fa[N][LG], dep[N];
	int son[N], dis[N];

	void dfs(int u) {
		for (int i = 1; i < LG; ++i) {
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
		}
		dep[u] = dep[fa[u][0]] + 1;
		dis[u] = 0, son[u] = 0;
		for (int v : E[u]) {
			if (v != fa[u][0]) {
				fa[v][0] = u;
				dfs(v);
				if (!son[u] || dis[v] + 1 > dis[son[u]]) {
					dis[u] = dis[v] + 1;
					son[u] = v;
				}
			}
		}
	}

	int top[N];
	std::vector<int> up[N], down[N];

	void get_top(int u, int tp) {
		top[u] = tp;
		if (u == tp) {
			for (int x = u; (int)up[u].size() <= dis[u] && x; x = fa[x][0]) {
				up[u].push_back(x);
			}
		}
		down[tp].push_back(u);
		if (son[u]) {
			get_top(son[u], tp);
		}
		for (int v : E[u]) {
			if (v != fa[u][0] && v != son[u]) {
				get_top(v, v);
			}
		}
	}

	int highbit[N];

	void init() {
		fa[1][0] = 0, dfs(1);
		get_top(1, 1);
		for (int i = 1; i <= cnt; ++i) {
			int j = LG - 1;
			while (!(i >> j & 1)) {
				--j;
			}
			highbit[i] = j;
		}
	}

	int kth(int u, int k) {
		if (k == 0) {
			return u;
		}
		u = fa[u][highbit[k]];
		k ^= 1 << highbit[k];
		int v = top[u];
		int d = dep[u] - k;
		if (d >= dep[v]) {
			return down[v][d - dep[v]];
		} else {
			return up[v][dep[v] - d];
		}
	}

	int real_kth(int u, int k) {
		if (k == 0) {
			return u;
		}
		u = kth(u, k - 1);
		if (fa[u][0] <= n) {
			return fa[u][0];
		} else {
			return u;
		}
	}
} T;

struct Query {
	int u, v, d, id;

	bool operator < (const Query &rhs) const {
		return d < rhs.d;
	}
} Q[N];

int ans[N];

int dep[N], fa[N][LG];
int fw[N], dis[N];
bool key[N];

void dfs(int u, int lst) {
	dis[u] = dis[fa[u][0]] + fw[u];
	if (dis[u] - lst >= B) {
		key[u] = true;
		lst = dis[u];
	}
	dep[u] = dep[fa[u][0]] + 1;
	for (int i = 1; i < LG; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	}
	for (auto p : E[u]) {
		int v = p.first,w = p.second;
		if (v != fa[u][0]) {
			fa[v][0] = u, fw[v] = w;
			dfs(v, lst);
		}
	}
}

int LCA(int u, int v) {
	if (dep[u] < dep[v]) {
		std::swap(u, v);
	}
	for (int i = LG - 1; i >= 0; --i) {
		if (dep[fa[u][i]] >= dep[v]) {
			u = fa[u][i];
		}
	}
	if (u == v) {
		return u;
	}
	for (int i = LG - 1; i >= 0; --i) {
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

struct State {
	int u, c;

	State() {}
	State(int _u, int _c) : u(_u), c(_c) {}
};

int jump[N], rem[N];
State jumps[N];

void get_jumps(int u, int lst) {
	if (dep[jump[u]] <= dep[lst]) {
		jumps[u] = State(jump[u], 1);
	} else {
		jumps[u] = jumps[jump[u]];
		++jumps[u].c;
	}
	if (key[u]) {
		u = lst;
	}
	for (auto p : E[u]) {
		int v = p.first;
		if (v != fa[u][0]) {
			get_jumps(v, lst);
		}
	}
}

State jump_small(int u, int v, int k) {
	int c = 0;
	while (dis[jumps[u].u] - dis[v] > k) {
		c += jumps[u].c;
		u = jumps[u].u;
	}
	while (dis[u] - dis[v] > k) {
		++c;
		u = jump[u];
	}
	return State(u, c);
}

State jump_large(int u, int v, int k) {
	int c = 0;
	while (dis[u] - dis[v] > k) {
		++c;
		u = T.real_kth(u, k);
	}
	return State(u, c);
}

int merge(const State &a, const State &b, int v, int k) {
	int d = dis[a.u] + dis[b.u] - 2 * dis[v];
	return a.c + b.c + (d + k - 1) / k;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	T.cnt = n;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		E[u].emplace_back(v, w);
		E[v].emplace_back(u, w);
		T.add_edge(u, v, w);
	}
	T.init();
	fa[1][0] = 0, fw[1] = 0, dfs(1, 0);

	std::cin >> q;
	for (int i = 1; i <= q; ++i) {
		std::cin >> Q[i].u >> Q[i].v >> Q[i].d;
		Q[i].id = i;
	}
	std::sort(Q + 1, Q + 1 + q);

	for (int i = 1; i <= n; ++i) {
		jump[i] = i, rem[i] = 0;
	}
	int lst = 0;
	for (int k = 1; k <= q; ++k) {
		int z = LCA(Q[k].u, Q[k].v);
		State a, b;
		if (Q[k].d < B) {
			if (Q[k].d > lst) {
				while (Q[k].d > lst) {
					for (int i = 1; i <= n; ++i) {
						++rem[i];
						if (rem[i] >= fw[jump[i]]) {
							jump[i] = fa[jump[i]][0];
							rem[i] = 0;
						}
					}
					++lst;
				}
				get_jumps(1, 0);
			}
			a = jump_small(Q[k].u, z, Q[k].d);
			b = jump_small(Q[k].v, z, Q[k].d);
		} else {
			a = jump_large(Q[k].u, z, Q[k].d);
			b = jump_large(Q[k].v, z, Q[k].d);
		}
		ans[Q[k].id] = merge(a, b, z, Q[k].d);
	}

	for (int i = 1; i <= q; ++i) {
		std::cout << ans[i] << "\n";
	}
}
