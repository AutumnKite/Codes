#include <bits/stdc++.h>

const int P = 998244353;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	int sum = 0;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		sum += a[i];
	}
	
	std::vector<std::vector<int>> C(sum + 1, std::vector<int>(sum + 1));
	for (int i = 0; i <= sum; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
	}
	
	std::vector<int> inv(n + 1);
	inv[1] = 1;
	for (int i = 2; i <= n; ++i) {
		inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	}
	
	std::vector<std::vector<int>> f(n + 1, std::vector<int>(sum + 1, 0));
	
	auto add = [&](int v) {
		for (int i = n; i >= 1; --i) {
			for (int j = sum; j >= 0; --j) {
				for (int t = 0; t < v && t <= j; ++t) {
					f[i][j] = (f[i][j] + 1ll * C[j][t] * f[i - 1][j - t]) % P;
				}
			}
		}
	};
	
	auto del = [&](int v) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= sum; ++j) {
				for (int t = 0; t < v && t <= j; ++t) {
					f[i][j] = (f[i][j] + 1ll * (P - C[j][t]) * f[i - 1][j - t]) % P;
				}
			}
		}
	};
	
	f[0][0] = 1;
	for (int k = 0; k < n; ++k) {
		add(a[k]);
	}

	for (int x = 0; x < n; ++x) {
		auto g = f;
		del(a[x]);
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			int pw = 1;
			int s = 0;
			for (int j = 0; j <= sum; ++j) {
				pw = 1ll * pw * inv[i] % P;
				if (j >= a[x] - 1) {
					s = (s + 1ll * C[j][a[x] - 1] * f[i - 1][j - a[x] + 1] % P * pw) % P;
				}
			}
			ans = (ans + (i & 1 ? s : P - s)) % P;
		}
		std::cout << ans << " \n"[x == n - 1];
		f.swap(g);
	}
	std::cout << "\n";
}

