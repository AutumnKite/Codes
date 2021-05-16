#include <bits/stdc++.h>

const int N = 1000000;

int f[N + 1], g[N + 1];

void solve() {
	int n;
	std::cin >> n;
	std::cout << g[n] << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	f[0] = 0;
	for (int i = 0; i <= N; ++i) {
		for (int j = 2 * (i + 1); j <= N; j += i + 1) {
			f[j] = std::max(f[j], f[i] + 1);
		}
	}

	for (int i = 0; i <= N; ++i) {
		for (int j = 3 * (i + 1); j <= N; j += i + 1) {
			g[j] = std::max(g[j], f[i] + 1);
		}
	}

	int T;
	std::cin >> T;
	for (int test = 1; test <= T; ++test) {
		std::cout << "Case #" << test << ": ";
		solve();
	}
}