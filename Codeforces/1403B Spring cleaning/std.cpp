#include <bits/stdc++.h>

class Tree {
	int n, rt;
	std::vector<std::vector<int>> E;
	std::vector<int> fa, dep, sz, son, top, dfn;
	std::vector<int> szl;
	std::vector<std::array<int, 2>> sum;
	int ans;

	void dfs(int u) {
		if (fa[u] != -1) {
			E[u].erase(std::find(E[u].begin(), E[u].end(), fa[u]));
		}
		szl[u] = E[u].empty();
		sz[u] = 1;
		son[u] = -1;
		for (int v : E[u]) {
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs(v);
			sz[u] += sz[v];
			if (son[u] == -1 || sz[v] > sz[son[u]]) {
				son[u] = v;
			}
			szl[u] ^= szl[v];
		}
		if (fa[u] != -1) {
			ans += !szl[u];
		}
	}

	int idx;

	void dfs(int u, int tp) {
		dfn[u] = idx++;
		if (fa[u] != -1) {
			sum[u][0] = sum[fa[u]][0];
			sum[u][1] = sum[fa[u]][1];
		}
		++sum[u][szl[u]];
		top[u] = tp;
		if (son[u] != -1) {
			dfs(son[u], tp);
		}
		for (int v : E[u]) {
			if (v != son[u]) {
				dfs(v, v);
			}
		}
	}

	int LCA(int u, int v) {
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) {
				v = fa[top[v]];
			} else {
				u = fa[top[u]];
			}
		}
		return dep[u] < dep[v] ? u : v;
	}

	std::vector<int> delta;
	std::vector<std::vector<int>> G;

public:
	Tree(std::vector<std::vector<int>> _E) : n(_E.size()), E(_E), 
	                                         fa(n), dep(n), sz(n), son(n), top(n), dfn(n),
		                                     szl(n), sum(n), ans(0), delta(n), G(n) {
		rt = 0;
		while (rt < n - 1 && (int)E[rt].size() <= 1) {
			++rt;
		}
		fa[rt] = -1, dep[rt] = 0;
		dfs(rt);
		idx = 0;
		dfs(rt, rt);
	}

	int get_ans(std::vector<int> id) {
		std::sort(id.begin(), id.end(), [&](int x, int y) {
			return dfn[x] < dfn[y];
		});
		int nans = ans + id.size();
		std::vector<int> sta;
		auto add = [&](int u) {
			if (sta.empty()) {
				sta.push_back(u);
				return;
			}
			int x = sta.back(), z = LCA(x, u), y;
			if (z == x) {
				sta.push_back(u);
				return;
			}
			while ((int)sta.size() > 1 && dfn[y = sta[(int)sta.size() - 2]] > dfn[z]) {
				G[y].push_back(x);
				sta.pop_back();
				x = y;
			}
			G[z].push_back(x);
			sta.pop_back();
			if (sta.empty() || sta.back() != z) {
				sta.push_back(z);
			}
			sta.push_back(u);
		};
		for (int x : id) {
			delta[x] ^= 1;
		}
		id.erase(std::unique(id.begin(), id.end()), id.end());
		add(rt);
		for (int x : id) {
			if (x != rt) {
				add(x);
			}
			if (E[x].empty()) {
				delta[x] ^= 1;
			}
		}
		while ((int)sta.size() > 1) {
			int x = sta.back();
			sta.pop_back();
			int y = sta.back();
			G[y].push_back(x);
		}
		std::vector<int> nd;
		std::function<void(int)> dfs = [&](int u) {
			nd.push_back(u);
			for (int v : G[u]) {
				dfs(v);
				delta[u] ^= delta[v];
				nans -= sum[v][0] - sum[u][0];
				nans += sum[v][delta[v]] - sum[u][delta[v]];
			}
		};
		dfs(rt);
		if (szl[rt] ^ delta[rt]) {
			nans = -n;
		}
		for (int x : nd) {
			delta[x] = 0;
			G[x].clear();
		}
		return n - 1 + nans;
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, q;
	std::cin >> n >> q;
	std::vector<std::vector<int>> E(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		std::cin >> u >> v;
		--u, --v;
		E[u].push_back(v);
		E[v].push_back(u);
	}

	Tree T(E);
	while (q--) {
		int k;
		std::cin >> k;
		std::vector<int> id(k);
		for (int &x : id) {
			std::cin >> x;
			--x;
		}
		std::cout << T.get_ans(id) << "\n";
	}
}
