#include <bits/stdc++.h>

const int P = 998244353;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::vector<int> sum(1 << n);
	for (int i = 0; i < n; ++i) {
		sum[1 << i] = a[i];
	}
	for (int S = 1; S < (1 << n); ++S) {
		sum[S] = sum[S & (S - 1)] + sum[S & -S];
	}

	std::vector<int> f(1 << n), g(1 << n);
	f[0] = g[0] = 1;
	for (int S = 1; S < (1 << n); ++S) {
		for (int i = 0; i < n; ++i) {
			if (S >> i & 1 && sum[S ^ (1 << i)] >= 0) {
				f[S] = (f[S] + f[S ^ (1 << i)]) % P;
			}
		}
		if (sum[S] < 0) {
			for (int i = 0; i < n; ++i) {
				if (S >> i & 1) {
					g[S] = (g[S] + g[S ^ (1 << i)]) % P;
				}
			}
		}
	}

	int U = (1 << n) - 1;
	int ans = 0;
	for (int S = 1; S < (1 << n); ++S) {
		ans = (ans + 1ll * f[S] * g[U ^ S] % P * sum[S]) % P;
	}
	std::cout << (ans + P) % P << "\n";
}
