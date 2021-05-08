#include <bits/stdc++.h>

std::mt19937 rnd(time(0));

int main() {
	freopen("C.in", "w", stdout);
	
	int n = 100000, m = 100000;
	std::cout << n << " " << m << "\n";
	for (int i = 0; i < n - 1; ++i) {
		int u = i - rnd() % std::min(i + 1, 10), v = i + 1;
		std::cout << u + 1 << " " << v + 1 << " " << rnd() % 1000000000 + 1 << "\n";
	}
	for (int i = 0; i < m; ++i) {
		std::cout << rnd() % n + 1 << " \n"[i == m - 1];
	}
}
