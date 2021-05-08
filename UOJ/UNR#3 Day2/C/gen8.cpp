#include <bits/stdc++.h>

int main() {
	freopen("code8.in", "w", stdout);

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	int n = 100000, q = 1;
	std::cout << n << "\n";
	int t = 1000;
	std::cout << t << " " << t << "\n";
	std::cout << t - 2 << " " << t - 2 << "\n";
	for (int i = 100; i <= 700; ++i) {
		std::cout << t - i << " " << t - 1 << "\n";
	}
	for (int i = 100; i <= 700; ++i) {
		std::cout << t + i << " " << t - 1 << "\n";
	}
	for (int i = 100; i <= 700; ++i) {
		std::cout << t - 1 << " " << t - i << "\n";
	}
	for (int i = 100; i <= 700; ++i) {
		std::cout << t - 1 << " " << t + i << "\n";
	}
	for (int i = 601 * 4 + 3; i <= n; ++i) {
		std::cout << 100000 << " " << 100000 << "\n";
	}
	std::cout << q << "\n";
	std::cout << 1 << " " << 2 << "\n";
}
