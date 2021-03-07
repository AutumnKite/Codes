#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	std::vector<std::vector<std::pair<int, std::pair<int, int>>>> E(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v, w1, w2;
		std::cin >> u >> v >> w1 >> w2;
		--u, --v;
		E[u].emplace_back(v, std::make_pair(w1, w2));
		E[v].emplace_back(u, std::make_pair(w1, w2));
	}

	std::vector<int> A(n), B(n);
	int SA = 0, SB = 0;

	std::function<void(int, int)> dfs = [&](int u, int fa) {
		SA ^= A[u];
		SB ^= B[u];
		for (auto p : E[u]) {
			int v = p.first;
			auto w = p.second;
			if (v != fa) {
				A[v] = A[u] ^ w.first;
				B[v] = B[u] ^ w.second;
				dfs(v, u);
			}
		}
	};

	dfs(0, -1);
	for (int i = 0; i < n; ++i) {
		A[i] ^= SA;
		B[i] ^= SB;
	}
	std::sort(A.begin(), A.end());
	std::sort(B.begin(), B.end());

	for (int i = 0; i < n; ++i) {
		if (A[i] != B[i]) {
			std::cout << "NO\n";
			return 0;
		}
	}
	std::cout << "YES\n";
}