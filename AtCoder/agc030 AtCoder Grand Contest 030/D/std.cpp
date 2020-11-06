#include <bits/stdc++.h>

const int N = 3005, P = 1000000007, Inv2 = (P + 1) >> 1;

int n, q, a[N];

struct Node {
	int x, y;
} Q[N];

int f[N][N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= q; ++i) {
		std::cin >> Q[i].x >> Q[i].y;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			f[i][j] = 1;
		}
	}
	int pw = 1;
	for (int k = q; k; --k) {
		int x = Q[k].x, y = Q[k].y;
		for (int i = 1; i <= n; ++i) {
			if (i != x && i != y) {
				f[x][i] = f[y][i] = 1ll * (f[x][i] + f[y][i]) * Inv2 % P;
				f[i][x] = f[i][y] = 1ll * (f[i][x] + f[i][y]) * Inv2 % P;
			}
		}
		f[x][y] = f[y][x] = 1ll * (f[x][y] + f[y][x]) * Inv2 % P;
		pw = 2ll * pw % P;
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (a[i] > a[j]) {
				ans = (ans + f[i][j]) % P;
			}
		}
	}
	std::cout << 1ll * pw * ans % P << std::endl;
}
