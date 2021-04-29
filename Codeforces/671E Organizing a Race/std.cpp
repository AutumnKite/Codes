#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	std::vector<long long> w(n);
	for (int i = 0; i < n - 1; ++i) {
		int v;
		std::cin >> v;
		w[i + 1] = w[i] + v;
	}
	std::vector<long long> g(n + 1);
	for (int i = 0; i < n; ++i) {
		int v;
		std::cin >> v;
		g[i + 1] = g[i] + v;
	}

	std::vector<long long> a(n), b(n);
	for (int i = 0; i < n; ++i) {
		a[i] = w[i] - g[i];
		b[i] = g[i + 1] - w[i];
	}
	int ans = 1;
	for (int l = 0; l < n; ++l) {
		long long mx = a[l], mxv = b[l];
		for (int r = l + 1; r < n; ++r) {
			mx = std::max(mx, a[r]);
			mxv = std::max(mxv, b[r - 1] + mx - a[l]);
			if (mx - a[l] <= m && mxv <= b[r] + m) {
				ans = std::max(ans, r - l + 1);
			}
		}
	}
	std::cout << ans << "\n";
}