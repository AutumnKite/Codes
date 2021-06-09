#include <bits/stdc++.h>

const int P = 1000000007;

bool check(int x) {
	for (int i = 2; i * i <= x; ++i) {
		if (x % i == 0) {
			return false;
		}
	}
	return true;
}

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

	std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());
	std::set<int> S;
	std::vector<int> prime(n);
	for (int i = 0; i < n; ++i) {
		do {
			prime[i] = rnd() % (P - 2) + 2;
		} while (S.count(prime[i]) || !check(prime[i]));
		S.insert(prime[i]);
	}

	int rt = -1;
	std::vector<int> sz(n), mx(n);
	std::vector<int> id;
	std::function<void(int, int)> dfs = [&](int u, int fa) {
		id.push_back(u);
		sz[u] = 1;
		mx[u] = 0;
		for (int v : E[u]) {
			if (v != fa && v != rt) {
				dfs(v, u);
				sz[u] += sz[v];
				mx[u] = std::max(mx[u], sz[v]);
			}
		}
	};

	dfs(0, -1);
	for (int v : id) {
		if (std::max(mx[v], n - sz[v]) <= n / 2) {
			rt = v;
		}
	}

	std::function<int(int, int)> hash = [&](int u, int fa) {
		int res = 1;
		sz[u] = 1;
		for (int v : E[u]) {
			if (v != fa && v != rt) {
				int tmp = hash(v, u);
				res = (res + 1ll * tmp * prime[sz[v]]) % P;
				sz[u] += sz[v];
			}
		}
		return res;
	};

	bool flag = true;
	std::vector<std::vector<int>> ha;
	for (int u : E[rt]) {
		id.clear();
		dfs(u, -1);
		flag &= sz[u] == (n - 1) / (int)E[rt].size();
		std::vector<int> c;
		for (int v : id) {
			if (std::max(mx[v], sz[u] - sz[v]) <= sz[u] / 2) {
				c.push_back(v);
			}
		}
		std::vector<int> h;
		for (int v : c) {
			h.push_back(hash(v, -1));
		}
		ha.push_back(h);
	}
	for (int i = 1; i < (int)ha.size(); ++i) {
		bool ex = false;
		for (int x : ha[0]) {
			for (int y : ha[i]) {
				ex |= x == y;
			}
		}
		flag &= ex;
	}
	if (flag) {
		std::cout << E[rt].size() << "\n";
	} else {
		std::cout << -1 << "\n";
	}
}