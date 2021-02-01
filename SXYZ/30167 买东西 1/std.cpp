#include <bits/stdc++.h>

const int P = 998244353, Inv6 = 166374059;

int n;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	
	if (!(n & 1)) {
		std::cout << 0 << "\n";
		return 0;
	}

	n = (n - 1) / 2;
	std::cout << 1ll * (n + 1) * (n + 2) % P * (n + 3) % P * Inv6 % P << "\n";
}
