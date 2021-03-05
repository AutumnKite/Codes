#include <bits/stdc++.h>

const char col[] = "RGYB";

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m, d;
	std::cin >> n >> m >> d;

	if (d & 1) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				std::cout << col[(i + j) & 1];
			}
			std::cout << "\n";
		}
		return 0;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int x = (i + j) / d, y = (i + m - j) / d;
			std::cout << col[(x & 1) << 1 | (y & 1)];
		}
		std::cout << "\n";
	}
}