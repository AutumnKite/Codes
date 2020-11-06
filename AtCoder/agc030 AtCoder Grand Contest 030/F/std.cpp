#include <bits/stdc++.h>

const int N = 305, M = N << 1, P = 1000000007;

int n, m, a[M], del[M], vis[M];
int v[M], f[M][N][N];

void inc(int &a, int b) {
	(a += b) >= P ? a -= P : 0;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	std::cin >> n;
	n <<= 1;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}

	int c1 = 0, c2 = 0;
	for (int i = 1; i <= n; i += 2) {
		if (a[i] == -1 && a[i + 1] == -1) {
			++c1;
		} else if (a[i] != -1 && a[i + 1] != -1) {
			del[a[i]] = del[a[i + 1]] = 1;
		} else {
			++c2;
			if (a[i] != -1) {
				vis[a[i]] = 1;
			} else {
				vis[a[i + 1]] = 1;
			}
		}
	}

	m = 0;
	for (int i = n; i; --i) {
		if (!del[i]) {
			v[++m] = i;
		}
	}

	f[0][0][0] = 1;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j <= c1 + c2; ++j) {
			for (int k = 0; k <= c2; ++k) {
				if (f[i][j][k]) {
					if (!vis[v[i + 1]]) {
						inc(f[i + 1][j + 1][k], f[i][j][k]);
						if (j) {
							inc(f[i + 1][j - 1][k], f[i][j][k]);
						}
						if (k) {
							inc(f[i + 1][j][k - 1], 1ll * f[i][j][k] * k % P);
						}
					} else {
						inc(f[i + 1][j][k + 1], f[i][j][k]);
						if (j) {
							inc(f[i + 1][j - 1][k], f[i][j][k]);
						}
					}
				}
			}
		}
	}
	
	int ans = f[m][0][0];
	for (int i = 1; i <= c1; ++i) {
		ans = 1ll * ans * i % P;
	}
	std::cout << ans << std::endl;
}
