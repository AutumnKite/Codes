#include <bits/stdc++.h>

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		--a[i];
	}
	std::sort(a.begin(), a.end());

	std::vector<int> s;
	int ans = 0;
	for (int i = 1; i < n; ++i) {
		ans = std::max(ans, a[i] - a[i - 1] - 1);
		s.push_back((a[i] - a[i - 1]) / 2);
	}
	s.push_back(a[0]);
	s.push_back(m - a[n - 1] - 1);
	std::sort(s.begin(), s.end(), std::greater<int>());
	ans = std::max(ans, s[0] + s[1]);
	std::cout << 1.0 * ans / m << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cout.setf(std::ios::fixed);
	std::cout.precision(12);

	int T;
	std::cin >> T;
	for (int test = 1; test <= T; ++test) {
		std::cout << "Case #" << test << ": ";
		solve();
	}
}