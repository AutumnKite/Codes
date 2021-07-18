#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int tp;
	std::cin >> tp;
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		--a[i];
	}
	std::vector<int> fa(n);
	std::vector<std::vector<int>> E(n);
	for (int i = 1; i < n; ++i) {
		std::cin >> fa[i];
		--fa[i];
		E[fa[i]].push_back(i);
	}

	std::vector<int> p(n);
	int idx = 0;
	std::function<bool(int)> check = [&](int u) {
		if (p[u] != idx) {
			return false;
		}
		++idx;
		std::sort(E[u].begin(), E[u].end(), [&](int x, int y) {
			return p[x] < p[y];
		});
		for (int v : E[u]) {
			if (!check(v)) {
				return false;
			}
		}
		return true;
	};

	std::iota(p.begin(), p.end(), 0);
	std::vector<std::vector<int>> Q;
	std::map<std::vector<int>, std::vector<int>> mp;
	do {
		idx = 0;
		if (check(0)) {
			Q.push_back(p);
			mp[p] = p;
		}
	} while (std::next_permutation(p.begin(), p.end()));
	for (int i = 0; i < (int)Q.size(); ++i) {
		auto u = Q[i];
		for (int x = 1; x < n; ++x) {
			auto v(u);
			if (v[fa[x]] < v[x]) {
				std::swap(v[fa[x]], v[x]);
				if (!mp.count(v)) {
					mp[v] = mp[u];
					Q.push_back(v);
				}
			}
		}
	}
	if (!mp.count(a)) {
		std::cout << -1 << "\n";
	} else {
		auto ans = mp[a];
		for (int i = 0; i < n; ++i) {
			std::cout << ans[i] + 1 << " ";
		}
		std::cout << "\n";
	}
}
