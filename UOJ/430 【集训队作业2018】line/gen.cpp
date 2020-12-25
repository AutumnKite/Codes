#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

int main() {
	freopen("a.in", "w", stdout);

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n = 100000;
	std::cout << n << "\n";
	for (int i = 1; i <= n; ++i) {
		std::cout << (i == n ? 0 : i - 1) << " ";
		std::cout << rnd() % 1000000000 + 1 << " ";
		std::cout << rnd() % 1000000000 + 1 << "\n";
	}
}