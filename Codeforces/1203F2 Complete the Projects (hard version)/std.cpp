#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	std::vector<std::pair<int, int>> a, b;
	for (int i = 0; i < n; ++i) {
		int x, d;
		std::cin >> x >> d;
		if (d >= 0) {
			a.emplace_back(x, d);
		} else {
			b.emplace_back(x, -d);
		}
	}

	std::sort(a.begin(), a.end());
	int ans = 0;
	for (auto [x, d] : a) {
		if (m >= x) {
			m += d;
			++ans;
		}
	}

	std::sort(b.begin(), b.end());
	std::vector<std::vector<int>> f(b.size(), std::vector<int>(m + 1));
	for (int i = 0; i < (int)b.size(); ++i) {
		for (int j = b[i].first; j <= m; ++j) {
			std::priority_queue<int> Q;
			int sum = 0;
			for (int k = i - 1; k >= 0; --k) {
				if (j - sum - b[i].second >= 0) {
					f[i][j] = std::max(f[i][j], f[k][j - sum - b[i].second])
				}
				Q.push(b[i].second);
				sum += b[i].second;
				while (j - sum < b[i].first) {
					sum -= Q.top();
					Q.pop();
				}
			}
		}
	}
}
