#include <bits/stdc++.h>

const int N = 30000, M = 15;

int n, m;
int a[N][M];
int p[N];

std::bitset<N> full, S[N], now;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> a[i][j];
		}
	}

	for (int i = 0; i < n; ++i) {
		full.set(i);
	}
	for (int i = 0; i < n; ++i) {
		S[i] = full;
	}
	for (int d = 0; d < m; ++d) {
		for (int i = 0; i < n; ++i) {
			p[i] = i;
		}
		std::sort(p, p + n, [&](int x, int y) {
			return a[x][d] < a[y][d];
		});
		now.reset();
		for (int i = 0, j = 0; i < n; i = j) {
			while (j < n && a[p[j]][d] == a[p[i]][d]) {
				S[p[j]] &= now;
				++j;
			}
			for (int k = i; k < j; ++k) {
				now.set(p[k]);
			}
		}
	}
	
	for (int i = 0; i < n; ++i) {
		std::cout << S[i].count() << "\n";
	}
}
