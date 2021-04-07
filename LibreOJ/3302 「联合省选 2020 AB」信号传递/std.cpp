#include <bits/stdc++.h>

const int N = 23, M = (N + 1) / 2;
const int INF = 0x3f3f3f3f;

int m, n, B, v;
int a[N][N];
int s1[N][1 << M], s2[N][1 << M];

int cnt[1 << N];
int f[1 << N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> m >> n >> v;
	int lst;
	std::cin >> lst;
	--lst;
	for (int i = 1; i < m; ++i) {
		int now;
		std::cin >> now;
		--now;
		++a[lst][now];
		lst = now;
	}

	B = (n + 1) / 2;
	for (int i = 0; i < n; ++i) {
		for (int S = 0; S < (1 << B); ++S) {
			s1[i][S] = 0;
			for (int j = 0; j < B; ++j) {
				if (i != j) {
					if (S >> j & 1) {
						s1[i][S] += a[j][i];
						s1[i][S] += v * a[i][j];
					} else {
						s1[i][S] -= a[i][j];
						s1[i][S] += v * a[j][i];
					}
				}
			}
		}
		for (int S = 0; S < (1 << (n - B)); ++S) {
			s2[i][S] = 0;
			for (int j = B; j < n; ++j) {
				if (i != j) {
					if (S >> (j - B) & 1) {
						s2[i][S] += a[j][i];
						s2[i][S] += v * a[i][j];
					} else {
						s2[i][S] -= a[i][j];
						s2[i][S] += v * a[j][i];
					}
				}
			}
		}
	}

	cnt[0] = 0;
	f[0] = 0;
	for (int S = 1; S < (1 << n); ++S) {
		cnt[S] = cnt[S >> 1] + (S & 1);
		f[S] = INF;
		for (int i = 0; i < n; ++i) {
			if (S >> i & 1) {
				int S1 = S & ((1 << B) - 1), S2 = S >> B;
				f[S] = std::min(f[S], f[S ^ (1 << i)] + cnt[S] * (s1[i][S1] + s2[i][S2]));
			}
		}
	}
	std::cout << f[(1 << n) - 1] << "\n";
}