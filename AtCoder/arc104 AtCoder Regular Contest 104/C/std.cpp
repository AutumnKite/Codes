#include <bits/stdc++.h>

const int N = 105;

int n, id[2 * N];
bool f[N];

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		int l, r;
		std::cin >> l >> r;
		if (~l) {
			if (id[l] != 0) {
				std::cout << "No\n";
				return 0;
			}
			id[l] = -i;
		}
		if (~r) {
			if (id[r] != 0) {
				std::cout << "No\n";
				return 0;
			}
			id[r] = i;
		}
	}
	f[0] = true;
	for (int i = 1; i <= n; ++i) {
		f[i] = false;
		for (int j = 1; j <= i; ++j) {
			bool flag = true;
			for (int k = 1; k <= j; ++k) {
				int x = id[2 * (i - j) + k], y = id[2 * (i - j) + j + k];
				if (x > 0 || y < 0 || (x != 0 && y != 0 && -x != y)) {
					flag = false;
					break;
				}
			}
			if (flag) {
				f[i] |= f[i - j];
			}
		}
	}
	if (f[n]) {
		std::cout << "Yes\n";
	} else {
		std::cout << "No\n";
	}
}