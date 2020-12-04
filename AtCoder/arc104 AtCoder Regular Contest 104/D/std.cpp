#include <bits/stdc++.h>

const int N = 105, M = N * N * N;

int n, K, P;
int f[N][M], s[M];

int get(int x) {
	if (x < 0) {
		return 0;
	}
	return s[x];
}

int main() {
	std::cin >> n >> K >> P;
	int m = 0;
	f[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		m += i * K;
		for (int j = 0; j <= m; ++j) {
			s[j] = (get(j - i) + f[i - 1][j]) % P;
			f[i][j] = (s[j] + P - get(j - i * (K + 1))) % P;
		}
	}
	for (int i = 1; i <= n; ++i) {
		int ans = 0;
		for (int j = 0; j <= m; ++j) {
			ans = (ans + 1ll * f[i - 1][j] * f[n - i][j]) % P;
		}
		ans = 1ll * ans * (K + 1) % P;
		ans = (ans + P - 1) % P;
		std::cout << ans << "\n";
	}
}