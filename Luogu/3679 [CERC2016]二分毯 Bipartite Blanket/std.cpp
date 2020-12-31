#include <bits/stdc++.h>

const int N = 20;

int n, m, T;
int a[N], b[N];
int f[N], g[N];

std::vector<int> get(int n, int *val, int *a) {
	static bool f[1 << N];
	std::vector<int> res;
	for (int S = 0; S < (1 << n); ++S) {
		f[S] = true;
		int mask = 0;
		for (int i = 0; i < n; ++i) {
			if (S >> i & 1) {
				f[S] &= f[S ^ (1 << i)];
				mask |= a[i];
			}
		}
		f[S] &= __builtin_popcount(S) <= __builtin_popcount(mask);
		if (f[S]) {
			int sum = 0;
			for (int i = 0; i < n; ++i) {
				if (S >> i & 1) {
					sum += val[i];
				}
			}
			res.push_back(sum);
		}
	}
	std::sort(res.begin(), res.end());
	return res;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			char c;
			std::cin >> c;
			f[i] |= (c ^ '0') << j;
			g[j] |= (c ^ '0') << i;
		}
	}
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	for (int i = 0; i < m; ++i) {
		std::cin >> b[i];
	}
	std::cin >> T;

	std::vector<int> ra = get(n, a, f), rb = get(m, b, g);
	long long ans = 0;
	for (int v : ra) {
		int p = std::lower_bound(rb.begin(), rb.end(), T - v) - rb.begin();
		ans += rb.size() - p;
	}
	std::cout << ans << "\n";
}