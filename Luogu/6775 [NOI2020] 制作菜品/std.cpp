#include <bits/stdc++.h>

const int LIM = (500 - 1) * 5000;

void solve(std::vector<std::pair<int, int>> a, int k) {
	std::set<std::pair<int, int>> S;
	for (int i = 0; i < (int)a.size(); ++i) {
		S.insert(a[i]);
	}
	while (!S.empty()) {
		auto mn = *S.begin(), mx = *(--S.end());
		if (mn.first >= k) {
			std::cout << mn.second + 1 << " " << k << "\n";
			S.erase(S.begin());
			mn.first -= k;
			if (mn.first) {
				S.insert(mn);
			}
		} else {
			std::cout << mn.second + 1 << " " << mn.first << " ";
			std::cout << mx.second + 1 << " " << k - mn.first << "\n";
			S.erase(S.begin());
			S.erase(--S.end());
			mx.first -= k - mn.first;
			if (mx.first) {
				S.insert(mx);
			}
		}
	}
}

void solve() {
	int n, m, k;
	std::cin >> n >> m >> k;
	std::vector<int> d(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> d[i];
	}
	if (m == n - 2) {
		std::vector<std::bitset<LIM + 1>> f(n + 1);
		f[0][0] = 1;
		for (int i = 0; i < n; ++i) {
			f[i + 1] = f[i] << k | f[i] << d[i];
		}
		if (!f[n][(n - 1) * k]) {
			std::cout << -1 << "\n";
			return;
		}
		int now = (n - 1) * k;
		std::vector<std::pair<int, int>> a, b;
		for (int i = n - 1; i >= 0; --i) {
			if (now >= d[i] && f[i][now - d[i]]) {
				a.emplace_back(d[i], i);
				now -= d[i];
			} else {
				b.emplace_back(d[i], i);
				now -= k;
			}
		}
		solve(a, k);
		solve(b, k);
	} else {
		std::vector<std::pair<int, int>> a;
		for (int i = 0; i < n; ++i) {
			a.emplace_back(d[i], i);
		}
		solve(a, k);
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int T;
	std::cin >> T;
	while (T--) {
		solve();
	}
}
