#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m, q;
	std::cin >> n >> m >> q;
	std::vector<std::vector<int>> s0(n + 1, std::vector<int>(m + 1)), s1(s0);
	for (int i = 0; i < n; ++i) {
		std::string tmp;
		std::cin >> tmp;
		for (int j = 0; j < m; ++j) {
			s0[i + 1][j + 1] = s0[i][j + 1] + s0[i + 1][j] - s0[i][j] + (tmp[j] == '1');
			s1[i + 1][j + 1] = s1[i][j + 1] + s1[i + 1][j] - s1[i][j] + (tmp[j] == '0');
		}
	}

	auto solve = [&](int x, int y) -> long long {
		int cx = x / n, cy = y / m;
		
	};

	while (q--) {
		int sx, sy, tx, ty;
		std::cin >> sx >> sy >> tx >> ty;
		--sx, --sy;
		std::cout << solve(tx, ty) - solve(sx, ty) - solve(tx, sy) + solve(sx, sy) << "\n";
	}
}