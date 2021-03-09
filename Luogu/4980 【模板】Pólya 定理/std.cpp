#include <bits/stdc++.h>

const int P = 1000000007;

int qpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = 1ll * s * a % P;
		}
		a = 1ll * a * a % P;
	}
	return s;
}

void solve() {
	int n;
	std::cin >> n;

	auto prime_fact = [&](int x) {
		std::vector<int> p;
		for (int i = 2; i * i <= x; ++i) {
			if (x % i == 0) {
				p.push_back(i);
				while (x % i == 0) {
					x /= i;
				}
			}
		}
		if (x > 1) {
			p.push_back(x);
		}
		return p;
	};

	std::vector<int> p = prime_fact(n);

	auto phi = [&](int x) {
		int res = x;
		for (int v : p) {
			if (x % v == 0) {
				res /= v;
				res *= v - 1;
			}
		}
		return res;
	};

	int ans = 0;
	for (int i = 1; i * i <= n; ++i) {
		if (n % i == 0) {
			ans = (ans + 1ll * qpow(n, i - 1) * phi(n / i)) % P;
			if (i * i < n) {
				ans = (ans + 1ll * qpow(n, n / i - 1) * phi(i)) % P;
			}
		}
	}
	std::cout << ans << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int T;
	std::cin >> T;
	while (T--) {
		solve();
	}
}