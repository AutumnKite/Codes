#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n = 1000, q = 1000;
	std::cout << n << " " << q << "\n";
	for (int i = 1; i <= n; ++i) {
		std::cout << rnd() % 1000000 + 1 << " \n"[i == n];
	}
	for (int i = 1; i <= q; ++i) {
		int l = rnd() % n + 1, r = rnd() % n + 1;
		if (l > r) {
			std::swap(l, r);
		}
		std::cout << l << " " << r << "\n";
	}
}