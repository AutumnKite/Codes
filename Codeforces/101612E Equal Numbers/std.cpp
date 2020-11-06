#include <bits/stdc++.h>

int n, m;
int c[1000005];

int main() {
	freopen("equal.in", "r", stdin);
	freopen("equal.out", "w", stdout);

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x;
		std::cin >> x;
		++c[x];
		m = std::max(m, x);
	}

	std::vector<int> s0, s1;
	for (int i = 1; i <= m; ++i) {
		if (c[i]) {
			bool flag = 0;
			for (int j = 2 * i; j <= m; j += i) {
				if (c[j]) {
					flag = 1;
					break;
				}
			}
			if (flag) {
				s0.push_back(c[i]);
			}
			s1.push_back(c[i]);
		}
	}

	std::sort(s0.begin(), s0.end());
	std::sort(s1.begin(), s1.end());
	for (int i = 1; i < (int)s0.size(); ++i) {
		s0[i] += s0[i - 1];
	}
	for (int i = 1; i < (int)s1.size(); ++i) {
		s1[i] += s1[i - 1];
	}

	int tot = s1.size();
	int i = 0, j = 0;
	for (int k = 0; k <= n; ++k) {
		while (i < (int)s0.size() && s0[i] <= k) {
			++i;
		}
		while (j < (int)s1.size() && s1[j] <= k) {
			++j;
		}
		std::cout << std::min(tot - i, tot - j + 1) << " \n"[k == n];
	}
}