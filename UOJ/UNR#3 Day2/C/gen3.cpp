#include <bits/stdc++.h>

const int LIM = 2017011328;

int main() {
	freopen("code3.in", "w", stdout);
	
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	int n = 100000;
	std::cout << n << "\n";
	for (int i = 2; i <= 11; ++i) {
		std::cout << 1 << " " << i << " " << -LIM << "\n";
	}
	std::cout << 1 << " " << 12 << " " << 0 << "\n";
	for (int i = 13; i < n; ++i) {
		std::cout << i - 1 << " " << i << " " << 0 << "\n";
	}
	std::cout << n - 1 << " " << n << " " << -LIM + 2 << "\n";
	for (int i = 2; i <= 11; ++i) {
		std::cout << 1 << " " << i << " " << -LIM << "\n";
	}
	std::cout << 1 << " " << 12 << " " << 0 << "\n";
	for (int i = 13; i < n; ++i) {
		std::cout << i - 1 << " " << i << " " << 0 << "\n";
	}
	std::cout << n - 1 << " " << n << " " << -LIM + 1 << "\n";
}

