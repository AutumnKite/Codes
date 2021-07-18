#include <bits/stdc++.h>

const int P = 998244353, inv2 = (P + 1) / 2;
const int B = 233;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	std::vector<std::vector<int>> E(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		std::cin >> u >> v;
		--u, --v;
		E[u].push_back(v);
		E[v].push_back(u);
	}

	bool flag = true;
	for (int i = 0; i < n; ++i) {
		flag &= (int)E[i].size() <= 2;
	}

	if (flag) {
		int ans = 1;
		for (int i = 0; i < n; ++i) {
			ans = 1ll * ans * (n - i) % P;
			if (i == 0 && (n & 1)) {
				std::cout << 1ll * (ans + 1) * inv2 % P << " ";
			} else {
				std::cout << 1ll * ans * inv2 % P << " ";
			}
		}
		std::cout << "\n";
		return 0;
	}

	std::vector<std::vector<int>> C(n + 1, std::vector<int>(n + 1));
	for (int i = 0; i <= n; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
	}

	std::vector<int> pw(2 * n + 1);
	pw[0] = 1;
	for (int i = 1; i <= 2 * n; ++i) {
		pw[i] = 1ll * pw[i - 1] * B % P;
	}

	std::vector<int> hash(n), sz(n);
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		sz[u] = 1;
		std::vector<std::pair<int, int>> tmp;
		for (int v : E[u]) {
			if (v != fa) {
				dfs(v, u);
				sz[u] += sz[v];
				tmp.emplace_back(hash[v], sz[v] * 2);
			}
		}
		std::sort(tmp.begin(), tmp.end());
		hash[u] = 1;
		for (auto p : tmp) {
			hash[u] = (1ll * hash[u] * pw[p.second] + p.first) % P;
		}
		hash[u] = (1ll * hash[u] * B + 2) % P;
	};

	std::vector<std::vector<int>> f(n);
	std::function<void(int, int)> dp = [&](int u, int fa) {
		std::map<int, int> mp, id;
		for (int v : E[u]) {
			if (v != fa) {
				if (!mp.count(hash[v])) {
					dp(v, u);
					id[hash[v]] = v;
				}
				++mp[hash[v]];
			}
		}
		f[u] = std::vector<int>(fa == -1 ? 1 : 2, 1);
		for (auto p : mp) {
			int h = p.first, c = p.second, v = id[h];
			std::vector<int> g(1, 1);
			for (int k = 0; k < c; ++k) {
				std::vector<int> t(g.size() + sz[v]);
				for (int i = 0; i < (int)g.size(); ++i) {
					for (int j = 0; j <= sz[v]; ++j) {
						t[i + j] = (t[i + j] + 1ll * g[i] * f[v][j] % P * (i + j == 0 ? 1 : C[i + j - 1][i])) % P;
					}
				}
				g.swap(t);
			}
			std::vector<int> t(f[u].size() + sz[v] * c);
			for (int i = 0; i < (int)f[u].size(); ++i) {
				for (int j = 0; j <= sz[v] * c; ++j) {
					t[i + j] = (t[i + j] + 1ll * f[u][i] * g[j] % P * C[i + j][i]) % P;
				}
			}
			f[u].swap(t);
		}
	};

	std::set<int> S;
	std::vector<int> ans(n);
	for (int rt = 0; rt < n; ++rt) {
		dfs(rt, -1);
		if (S.count(hash[rt])) {
			continue;
		}
		S.insert(hash[rt]);
		dp(rt, -1);
		for (int i = 0; i < n; ++i) {
			ans[i] = (ans[i] + f[rt][i]) % P;
		}
	}
	for (int i = 0; i < n; ++i) {
		std::cout << ans[i] << " ";
	}
	std::cout << "\n";
}
