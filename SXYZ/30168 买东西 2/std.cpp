#include <bits/stdc++.h>

const int P = 998244353, Inv2 = (P + 1) / 2;

int n;

int qpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = 1ll * s * a % P;
		}
		a = 1ll * a * a % P;
	}
	return s;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;

	if (!(n & 1)) {
		std::cout << 0 << "\n";
		return 0;
	}

	std::cout << 1ll * (qpow(2, 2 * n - 2) + qpow(2, n - 1)) * Inv2 % P << "\n";
}
