#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

int main() {
	std::ios_base::sync_with_stdio(false);
	
	int n, k;
	std::cin >> n >> k;
	int x = 0, v = k;
	while (1) {
		x = rnd() % n;
		std::cout << "? " << x + 1 << std::endl;
		std::cin >> v;
		if (v != k) {
			break;
		}
	}
	if (v < k) {
		while (v != k) {
			x = (x + 1) % n;
			std::cout << "? " << x + 1 << std::endl;
			std::cin >> v;
		}
		std::cout << "! " << x + 1 << std::endl;
	} else {
		while (v != k) {
			x = (x + n - 1) % n;
			std::cout << "? " << x + 1 << std::endl;
			std::cin >> v;
		}
		std::cout << "! " << x + 1 << std::endl;
	}
}
