#include <bits/stdc++.h>

int main() {
	freopen("code5.in", "w", stdout);
	
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	int n = 100000;
	std::cout << n << "\n";
	for (int i = 1; i <= 9; ++i) {
		std::cout << i * 10 << " " << 9990 + i << "\n";
	}
	std::cout << "99 19999\n";
	std::cout << "100 20000\n";
	for (int i = 0; i < n - 11; ++i) {
		std::cout << 20000 + i * 5000 << " " << 35000 + i * 5000 << "\n";
	}
}
