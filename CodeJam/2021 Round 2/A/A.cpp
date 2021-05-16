#include <bits/stdc++.h>

void solve(int n) {
	for (int i = 0; i < n - 1; ++i) {
		std::cout << "M " << i + 1 << " " << n << std::endl;
		int p;
		std::cin >> p;
		--p;
		if (p != i) {
			std::cout << "S " << i + 1 << " " << p + 1 << std::endl;
			int t;
			std::cin >> t;
		}
	}
	std::cout << "D" << std::endl;
	int ans;
	std::cin >> ans;
	assert(ans == 1);
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int T, n;
	std::cin >> T >> n;
	for (int test = 1; test <= T; ++test) {
		solve(n);
	}
}