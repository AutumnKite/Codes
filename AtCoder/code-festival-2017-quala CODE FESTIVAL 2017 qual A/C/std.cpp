#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(26);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char c;
			std::cin >> c;
			++a[c - 'a'];
		}
	}
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < 26; ++i) {
		a[i] %= 4;
		cnt1 += a[i] & 1;
		cnt2 += a[i] >> 1;
	}
	if (n & 1 && m & 1) {
		if (cnt2 <= n / 2 + m / 2 && cnt1 == 1) {
			std::cout << "Yes\n";
		} else {
			std::cout << "No\n";
		}
	} else {
		if (cnt1) {
			std::cout << "No\n";
			return 0;
		}
		int lim;
		if (n & 1) {
			lim = m / 2;
		} else if (m & 1) {
			lim = n / 2;
		} else {
			lim = 0;
		}
		if (cnt2 <= lim) {
			std::cout << "Yes\n";
		} else {
			std::cout << "No\n";
		}
	}
}