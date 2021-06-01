#include <bits/stdc++.h>
#include <ext/rope>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, d, m, q;
	const int C = 50;
	std::cin >> n >> d >> m >> q;
	std::vector<int> H(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> H[i];
	}
	std::vector<std::vector<int>> t(n);
	std::vector<std::vector<int>> op(n);
	std::vector<std::vector<__gnu_cxx::rope<int>>> a(n);
	auto cmp = [&](int x, int y) {
		return H[x] < H[y] || (H[x] == H[y] && x < y);
	};
	auto add = [&](__gnu_cxx::rope<int> &S, int v) {
		auto it = std::lower_bound(S.begin(), S.end(), v, cmp);
		if (it != S.end() && *it == v) {
			S.erase(it - S.begin(), 1);
		} else {
			S.insert(it - S.begin(), v);
		}
	};
	for (int i = 0; i < m; ++i) {
		int u, v;
		std::cin >> u >> v;
		t[u].push_back(i);
		t[v].push_back(i);
		op[u].push_back(v);
		op[v].push_back(u);
	}
	for (int u = 0; u < n; ++u) {
		__gnu_cxx::rope<int> S;
		for (int i = 0; i <= (int)t[u].size(); ++i) {
			if (i % C == 0) {
				a[u].emplace_back(S);
			}
			if (i < (int)t[u].size()) {
				add(S, op[u][i]);
			}
		}
	}
	while (q--) {
		int u, v, p;
		std::cin >> u >> v >> p;
		int pu = std::lower_bound(t[u].begin(), t[u].end(), p) - t[u].begin();
		int pv = std::lower_bound(t[v].begin(), t[v].end(), p) - t[v].begin();
		auto Su = a[u][pu / C];
		auto Sv = a[v][pv / C];
		for (int i = pu / C * C; i < pu; ++i) {
			add(Su, op[u][i]);
		}
		for (int i = pv / C * C; i < pv; ++i) {
			add(Sv, op[v][i]);
		}
		int ans = 1000000000;
		for (auto i = Su.begin(), j = Sv.begin(); i != Su.end() && j != Sv.end(); ++i) {
			while (std::next(j) != Sv.end() && H[*std::next(j)] <= H[*i]) {
				++j;
			}
			ans = std::min(ans, abs(H[*j] - H[*i]));
			if (std::next(j) != Sv.end()) {
				ans = std::min(ans, abs(H[*std::next(j)] - H[*i]));
			}
		}
		std::cout << ans << std::endl;
	}
}
