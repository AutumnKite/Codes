#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	for (int i = 0; i < n - 1; ++i) {
		a[i] = a[i + 1] - a[i];
	}
	a.resize(n - 1);

	std::vector<long long> pre(n), suf(n);
	for (int i = 0; i < n - 1; ++i) {
		pre[i + 1] = pre[i] + std::max(1 - a[i], 0);
	}
	for (int i = n - 2; i >= 0; --i) {
		suf[i] = suf[i + 1] + std::max(a[i] + 1, 0);
	}

	long long ans = std::max(pre[0], suf[0]);
	for (int i = 1; i < n; ++i) {
		ans = std::min(ans, std::max(pre[i], suf[i]));
	}
	std::cout << ans << "\n";
}