#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, X, Y;
	std::cin >> n >> X >> Y;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::vector<int> b(n);
	int rem = Y;
	for (int i = 0; i < n; ++i) {
		b[i] = 1ll * a[i] * Y / X;
		rem -= b[i];
	}
	
	std::vector<std::pair<long long, int>> c(n);
	for (int i = 0; i < n; ++i) {
		c[i].first = 2ll * a[i] * Y - 1ll * b[i] * X - 1ll * (b[i] + 1) * X;
		c[i].second = i;
	}
	std::sort(c.begin(), c.end());
	while (rem) {
		++b[c.back().second];
		c.pop_back();
		--rem;
	}
	for (int i = 0; i < n; ++i) {
		std::cout << b[i] << " \n"[i == n - 1];
	}
}
