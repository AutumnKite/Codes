#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m, k;
	std::cin >> n >> m >> k;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			int s = i * (m - j) + j * (n - i);
			if (s == k) {
				std::cout << "Yes\n";
				return 0;
			}
		}
	}
	std::cout << "No\n";
}