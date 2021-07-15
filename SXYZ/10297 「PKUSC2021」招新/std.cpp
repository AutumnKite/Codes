#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m, k, P;
	std::cin >> n >> m >> k >> P;

	auto qpow = [&](int a, int b) {
		int s = 1;
		for (; b; b >>= 1) {
			if (b & 1) {
				s = 1ll * s * a % P;
			}
			a = 1ll * a * a % P;
		}
		return s;
	};

	if (n <= 2) {
		std::cout << 1 << "\n";
		return 0;
	}

	if ((n - 1) / 2 * k > m) {
		std::cout << 0 << "\n";
		return 0;
	}

	auto inc = [&](int &a, int b) {
		a + b >= P ? a += b - P : a += b;
	};
	auto dec = [&](int &a, int b) {
		a < b ? a += P - b : a -= b;
	};

	std::vector<std::vector<std::vector<std::vector<int>>>> f(m, 
	  std::vector<std::vector<std::vector<int>>>(k + 2, 
	    std::vector<std::vector<int>>(n, std::vector<int>(n))));
	for (int x = 0; x < m; ++x) {
		for (int d = 0; d <= k + 1 && x + d < m; ++d) {
			f[x][d][0][1] = 1;
			if (d > 0) {
				f[x][d][1][0] = f[x][d][0][1];
			}
		}
	}
	for (int l = 2; l < n; ++l) {
		std::vector<std::vector<std::vector<std::vector<int>>>> g(m, 
		  std::vector<std::vector<std::vector<int>>>(k + 2, 
			std::vector<std::vector<int>>(n, std::vector<int>(n))));
		for (int x = 0; x < m; ++x) {
			for (int d = 0; d <= k + 1; ++d) {
				int y = x + d;
				if (y < m) {
					for (int i = 0; i < l; ++i) {
						for (int j = 0; j < l; ++j) {
							int v = f[x][d][i][j];
							if (v) {
								inc(g[y][k + 1 - d][j][j + 1], v);
								inc(g[y][k + 1 - d][j + 1][0], v);
								dec(g[y][k + 1 - d][j + 1][j + 1], v);
								if (d <= k && y + 1 < m) {
									dec(g[y + 1][k + 1 - d][j][j + 1], v);
									dec(g[y + 1][k + 1 - d][j + 1][0], v);
									inc(g[y + 1][k + 1 - d][j + 1][j + 1], v);
								}
							}
						}
					}
				}
			}
		}
		for (int x = 1; x < m; ++x) {
			for (int d = 0; d <= k + 1; ++d) {
				for (int i = 0; i <= l; ++i) {
					for (int j = 0; j <= l; ++j) {
						inc(g[x][d][i][j], g[x - 1][d][i][j]);
					}
				}
			}
		}
		for (int x = 0; x < m; ++x) {
			for (int d = 1; d <= k + 1; ++d) {
				for (int i = 0; i <= l; ++i) {
					for (int j = 0; j <= l; ++j) {
						inc(g[x][d][i][j], g[x][d - 1][i][j]);
					}
				}
			}
		}
		for (int x = 0; x < m; ++x) {
			for (int d = 0; d <= k; ++d) {
				int y = x + d;
				if (y + k - d < m) {
					for (int i = 0; i < l; ++i) {
						for (int j = 0; j < l; ++j) {
							int v = f[x][d][i][j];
							if (v) {
								inc(g[y][k - d][j][std::max(i, j) + 1], v);
								if (i < j) {
									inc(g[y][k - d][j + 1][i + 1], v);
									dec(g[y][k - d][j + 1][j + 1], v);
								}
							}
						}
					}
				}
			}
		}
		for (int x = 0; x < m; ++x) {
			for (int d = 0; d <= k + 1; ++d) {
				for (int i = 0; i <= l; ++i) {
					for (int j = 1; j <= l; ++j) {
						inc(g[x][d][i][j], g[x][d][i][j - 1]);
					}
				}
			}
		}
		for (int x = 0; x < m; ++x) {
			for (int d = 0; d <= k + 1; ++d) {
				for (int i = 0; i <= l; ++i) {
					for (int j = 0; j <= l; ++j) {
						if (i == j || (d == 0 && j < i) || x + d >= m) {
							g[x][d][i][j] = 0;
						}
					}
				}
			}
		}
		f.swap(g);
	}
	int ans = 0;
	for (int x = 0; x < m; ++x) {
		for (int d = 0; d <= k + 1; ++d) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					int v = f[x][d][i][j];
					if (v) {
						if (d == k + 1) {
							v = 1ll * v * (m - x - d) % P;
						}
						inc(ans, v);
					}
				}
			}
		}
	}
	std::cout << 1ll * ans * qpow(m, P - 1 - n) % P << "\n";
}
