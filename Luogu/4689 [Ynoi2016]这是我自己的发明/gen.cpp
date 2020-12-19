#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n = 15, m = 30;
	std::cout << n << " " << m << "\n";
	for (int i = 1; i <= n; ++i) {
		std::cout << rnd() % 1000 << " \n"[i == n];
	}
	for (int i = 2; i <= n; ++i) {
		std::cout << rnd() % (i - 1) + 1 << " " << i << "\n";
	}
	for (int i = 1; i <= m; ++i) {
		int op = rnd() % 2 + 1;
		if (op == 1) {
			std::cout << 1 << " " << rnd() % n + 1 << "\n";
		} else {
			std::cout << 2 << " " << rnd() % n + 1 << " " << rnd() % n + 1 << "\n";
		}
	}
}