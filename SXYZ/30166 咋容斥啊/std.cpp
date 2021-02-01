#include <bits/stdc++.h>

const int N = 20000005, P = 1000000007;

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

int fac[N], inv[N];

void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	inv[n] = qpow(fac[n], P - 2);
	for (int i = n; i; --i) {
		inv[i - 1] = 1ll * inv[i] * i % P;
	}
}

int C(int n, int m) {
	if (m < 0 || m > n) {
		return 0;
	}
	return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}

int n, L, S;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> L >> S;
	init(S);
	int ans = 0;
	for (int i = 0; i <= n && n + i * L <= S; ++i) {
		ans = (ans + 1ll * (i & 1 ? -1 : 1) * C(S - i * L - 1, n - 1) * C(n, i)) % P;
	}
	std::cout << (ans + P) % P << "\n";
}