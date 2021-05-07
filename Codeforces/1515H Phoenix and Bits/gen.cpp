#include <bits/stdc++.h>

std::mt19937 rnd(std::chrono::system_clock::now().time_since_epoch().count());

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n = rnd() % 2 + 1, m = rnd() % 5 + 1, lim = 16;
	std::cout << n << " " << m << "\n";
	for (int i = 0; i < n; ++i) {
		std::cout << rnd() % lim << " \n"[i == n - 1];
	}
	while (m--) {
		int op = rnd() % 4 + 1;
		int l = rnd() % lim, r = rnd() % lim;
		if (l > r) {
			std::swap(l, r);
		}
		std::cout << op << " " << l << " " << r;
		if (op <= 3) {
			std::cout << " " << rnd() % lim;
		}
		std::cout << "\n";
	}
}
