#include <bits/stdc++.h>

int main() {
	freopen("code2.in", "w", stdout);
	
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	int n = 5000, q = 10000;
	std::cout << n << " " << q << "\n";
	for (int i = 2; i <= 1000; ++i) {
		std::cout << 1 << " " << 1 << " " << i << "\n";
	}
	for (int i = 1001; i <= n; ++i) {
		std::cout << 1 << " " << i - 1 << " " << i << "\n";
	}
	for (int i = 1; i <= q - (n - 1); ++i) {
		std::cout << 2 << " " << 1 << " " << n << "\n";
	}
}

