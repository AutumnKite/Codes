#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		int x;
		std::cin >> x;
		--x;
		a[x] = i;
	}
	std::vector<std::vector<int>> S(n, std::vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			S[i][j] = S[i][j - 1] + (a[i] < a[j]);
		}
	}
	for (int i = n - 2; i >= 0; --i) {
		for (int j = 0; j < n; ++j) {
			S[i][j] += S[i + 1][j];
		}
	}
	std::vector<int> cnt(n);
	for (int i = 0; i < n; ++i) {
		cnt[i] = i + 1;
	}
	std::vector<int> f(n + 1);
	f[0] = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = a[i]; j < n; ++j) {
			--cnt[j];
		}
		int sum = 0;
		f[i + 1] = n * n;
		for (int j = i; j >= 0; --j) {
			sum += cnt[a[j]];
			f[i + 1] = std::min(f[i + 1], f[j] + S[j][i] + sum);
		}
	}
	std::cout << f[n] << "\n";
}