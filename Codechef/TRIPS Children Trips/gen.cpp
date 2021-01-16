#include <bits/stdc++.h>

std::mt19937 gen(time(0));

int rnd(int l, int r) {
	return gen() % (r - l) + l;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n = 100000, q = 100000;
	std::cout << n << "\n";
	for (int i = 2; i <= n; ++i) {
		std::cout << rnd(std::max(1, i - 10), i) << " " << i << " " << rnd(0, 2) + 1 << "\n";
	}
	std::cout << q << "\n";
	for (int i = 1; i <= q; ++i) {
		std::cout << rnd(0, n) + 1 << " " << rnd(0, n) + 1 << " " << rnd(1, 20000) + 1 << "\n";
	}
}