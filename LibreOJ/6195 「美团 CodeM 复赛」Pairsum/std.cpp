#include <bits/stdc++.h>

bool check_prime(int n) {
	if (n < 2) {
		return false;
	}
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
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
	if (n <= 400) {
		std::vector<int> f(20);
		f[0] = 1, f[1] = 2;
		for (int i = 2; i < 20; ++i) {
			f[i] = f[i - 1] + f[i - 2];
		}
		while (!f.empty() && f.back() > n) {
			f.pop_back();
		}
		std::cout << f.size() << "\n";
		for (int x : f) {
			std::cout << x << " ";
		}
		std::cout << "\n";
		return 0;
	}
	int p = floor(sqrt(1.0 * n / 2)) + 1e-9;
	while (!check_prime(p)) {
		--p;
	}
	std::vector<int> ans;
	for (int i = 1; i <= p; ++i) {
		int v = i * p * 2 + i * i % p;
		if (1 <= v && v <= n) {
			ans.push_back(v);
		}
	}
	std::cout << ans.size() << "\n";
	for (int v : ans) {
		std::cout << v << " ";
	}
	std::cout << "\n";
}