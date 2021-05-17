#include <bits/stdc++.h>

const int P = 998244353;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::string a, b;
	std::cin >> a >> b;
	int n = a.size(), m = b.size();
	int ans = 0;
	std::vector<std::vector<int>> f(n, std::vector<int>(m)), g(f);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i > 0 && a[i - 1] != a[i]) {
				f[i][j] = (f[i][j] + f[i - 1][j]) % P;
			}
			if (i > 0 && b[j] != a[i]) {
				f[i][j] = (f[i][j] + g[i - 1][j]) % P;
			}
		}
	}
}