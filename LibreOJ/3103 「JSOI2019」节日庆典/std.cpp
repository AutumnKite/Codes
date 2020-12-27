#include <bits/stdc++.h>

const int N = 3000005;

int n;
char a[N];

int z[N];

void init_Z() {
	z[1] = n;
	int l = 1, r = 0;
	for (int i = 2; i <= n; ++i) {
		z[i] = std::max(0, std::min(r - i + 1, z[i - l + 1]));
		while (i + z[i] <= n && a[1 + z[i]] == a[i + z[i]]) {
			++z[i];
		}
		if (i + z[i] - 1 > r) {
			l = i, r = i + z[i] - 1;
		}
	}
}

int cmp(int p, int len) {
	return z[p] >= len ? 0 : (a[p + z[p]] < a[1 + z[p]] ? 1 : -1);
}

int cmp(int x, int y, int k) {
	int tmp = cmp(x + (k - y + 1), y - x);
	if (tmp) {
		return tmp;
	}
	tmp = cmp(y - x + 1, x - 1);
	if (tmp) {
		return -tmp;
	}
	return 0;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> (a + 1);
	n = strlen(a + 1);

	init_Z();

	std::vector<int> now;
	for (int k = 1; k <= n; ++k) {
		std::vector<int> tmp(1, k);
		for (int i : now) {
			while (!tmp.empty() && a[i + k - tmp.back()] < a[k]) {
				tmp.pop_back();
			}
			if (tmp.empty() || a[i + k - tmp.back()] == a[k]) {
				while (!tmp.empty() && k - tmp.back() >= tmp.back() - i) {
					tmp.pop_back();
				}
				tmp.push_back(i);
			}
		}
		now.swap(tmp);
		int ans = now[0];
		for (int i = 1; i < (int)now.size(); ++i) {
			if (cmp(now[i], ans, k) >= 0) {
				ans = now[i];
			}
		}
		std::cout << ans << " \n"[k == n];
	}
}