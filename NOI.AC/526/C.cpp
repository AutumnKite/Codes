#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cout.setf(std::ios::fixed);
	std::cout.precision(12);

	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		--a[i];
	}

	std::vector<int> f(n + 1);
	std::vector<int> sta(n + 1, n);
	f[0] = 0;
	sta[0] = -1;
	for (int i = 0; i < n; ++i) {
		int p = std::lower_bound(sta.begin(), sta.end(), a[i]) - sta.begin();
		f[i + 1] = p;
		sta[p] = a[i];
	}
	int mx = *std::max_element(f.begin(), f.end());
	std::cout << mx << "\n";

	std::vector<double> ln(n + 1000000);
	for (int i = 1; i < n + 1000000; ++i) {
		ln[i] = log(i);
	}

	std::vector<std::vector<int>> pos(n + 1);
	for (int i = 0; i <= n; ++i) {
		pos[f[i]].push_back(i);
	}
	std::vector<int> h(n + 1), t(n + 1);

	int K;
	std::vector<double> g(n + 1);

	auto calc = [&](int i, int j) -> double {
		if (j == 0) {
			return 0;
		} else {
			assert(j > 0 && a[j - 1] < a[i - 1] && j < i);
			return g[j] + ln[a[i - 1] - a[j - 1] + K];
		}
	};

	auto trans = [&](int x, int i) {
		while (h[x] < (int)pos[x].size() && pos[x][h[x]] && a[pos[x][h[x]] - 1] >= a[i - 1]) {
			++h[x];
		}
		while (t[x] < (int)pos[x].size() && pos[x][t[x]] < i) {
			++t[x];
		}
		assert(h[x] < t[x]);
		int l = h[x] + 1, r = t[x] - 1, ans = h[x];
		while (l <= r - 10) {
			int mid = (l + r) >> 1;
			if (calc(i, pos[x][mid]) > calc(i, pos[x][mid - 1])) {
				ans = mid;
				l = mid + 1;
			} else {
				r = mid - 1;
			}
		}
		for (int j = l; j <= r; ++j) {
			if (j < r && calc(i, pos[x][j - 1]) >= calc(i, pos[x][j]) && calc(i, pos[x][j]) < calc(i, pos[x][j + 1])) {
				std::cerr << i << "\n";
				for (int k = l - 1; k <= r; ++k) {
					std::cerr << pos[x][k] << " " << calc(i, pos[x][k]) << "\n";
				}
				assert(0);
			}
			if (calc(i, pos[x][j]) > calc(i, pos[x][ans])) {
				ans = j;
			}
		}
		return calc(i, pos[x][ans]);
	};

	auto solve = [&]() {
		for (int i = 0; i <= n; ++i) {
			h[i] = 0, t[i] = 0;
		}
		g[0] = 0;
		double ans = 0;
		for (int i = 1; i <= n; ++i) {
			g[i] = trans(f[i] - 1, i);
			if (f[i] == mx) {
				ans = std::max(ans, g[i]);
			}
		}
		return ans;
	};

	int q;
	std::cin >> q;
	while (q--) {
		std::cin >> K;
		std::cout << solve() << "\n";
	}
}
