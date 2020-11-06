#include <bits/stdc++.h>

const int N = 505;

int n, m;
int a[N][N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	std::cin >> m;
	n = (m + 3) / 4 * 2;
	if (m > 1) {
		int t = 3 - (m - 1) % 4;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				a[j][(i + j) % n] = i < n - t ? (i << 1 | (j & 1)) : m - (n - i);
			}
		}
	}

	std::cout << n << "\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << a[i][j] + 1 << " ";
		}
		std::cout << "\n";
	}
}
