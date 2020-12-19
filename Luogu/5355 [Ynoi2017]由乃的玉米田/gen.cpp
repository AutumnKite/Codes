#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n = 10, m = 10;
	std::cout << n << " " << m << "\n";
	for (int i = 1; i <= n; ++i) {
		std::cout << rnd() % 10 << " \n"[i == n];
	}
	for (int i = 1; i <= m; ++i) {
		int l = rnd() % n + 1, r = rnd() % n + 1;
		if (l > r) {
			std::swap(l, r);
		}
		std::cout << rnd() % 4 + 1 << " " << l << " " << r << " " << rnd() % 10 << "\n";
	}
}