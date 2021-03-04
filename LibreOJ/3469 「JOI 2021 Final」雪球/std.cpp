#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, q;
	std::cin >> n >> q;
	std::vector<long long> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	std::vector<long long> d(q);
	std::vector<long long> s(q + 1), mx(q + 1), mn(q + 1);
	for (int i = 0; i < q; ++i) {
		std::cin >> d[i];
		s[i + 1] = s[i] + d[i];
		mx[i + 1] = std::max(mx[i], s[i + 1]);
		mn[i + 1] = std::min(mn[i], s[i + 1]);
	}

	std::vector<long long> l(q + 1);
	for (int i = 0; i <= q; ++i) {
		l[i] = mx[i] - mn[i];
	}

	std::vector<long long> ans(n);
	for (int i = 0; i < n - 1; ++i) {
		int p = std::upper_bound(l.begin(), l.end(), a[i + 1] - a[i]) - l.begin() - 1;
		ans[i] += mx[p];
		ans[i + 1] -= mn[p];
		long long rem = a[i + 1] - a[i] - l[p];
		if (p < q) {
			if (d[p] > 0) {
				ans[i] += rem;
			} else {
				ans[i + 1] += rem;
			}
		}
	}
	ans[0] -= mn[q];
	ans[n - 1] += mx[q];

	for (int i = 0; i < n; ++i) {
		std::cout << ans[i] << "\n";
	}
}