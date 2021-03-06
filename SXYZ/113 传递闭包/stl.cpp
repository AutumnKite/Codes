#include <bits/stdc++.h>

const int N = 8000, B = 8;

int n;
char tmp[(N - 1) / 4 + 3];
unsigned long long w[(N - 1) / 64 + 1];

std::bitset<N> f[N], st[1 << B];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		f[i].set(i);
	}
	for (int i = 1; i < n; ++i) {
		std::cin >> tmp;
		int len = (i - 1) / 4 + 1;
		for (int j = 0; j < len; ++j) {
			int v = isdigit(tmp[j]) ? tmp[j] - '0' : tmp[j] - 'A' + 10;
			for (int k = 0; k < 4 && j * 4 + k < i; ++k) {
				if (v >> k & 1) {
					f[i].set(j * 4 + k);
				}
			}
		}
	}
	int len = (n - 1) / 64 + 1;
	for (int i = 0; i < len; ++i) {
		std::cin >> w[i];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = i / B * B; j < i; ++j) {
			if (f[i][j]) {
				f[i] |= f[j];
			}
		}
		if (i + 1 < n && (i + 1) % B == 0) {
			int s = i - B + 1;
			for (int j = 0; j < B; ++j) {
				st[1 << j] = f[s + j];
			}
			for (int S = 1; S < (1 << B); ++S) {
				if (S & (S - 1)) {
					st[S] = st[S & -S] | st[S & (S - 1)];
				}
			}
			for (int j = i + 1; j < n; ++j) {
				int mask = 0;
				for (int k = 0; k < B; ++k) {
					if (f[j][s + k]) {
						mask |= 1 << k;
					}
				}
				f[j] |= st[mask];
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		unsigned long long ans = 0;
		for (int j = 0; j <= i; ++j) {
			if (f[i][j]) {
				ans += w[j >> 6] << (j & 63);
			}
		}
		std::cout << ans << "\n";
	}
}
