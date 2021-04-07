#include <bits/stdc++.h>

const int N = 1000;

int n, x, P, m;
int S[N + 1][N + 1];
int a[N + 1];
int b[N + 1];

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

	std::cin >> n >> x >> P >> m;
	for (int i = 0; i <= m; ++i) {
		std::cin >> a[i];
	}
	S[0][0] = 1;
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= i; ++j) {
			S[i][j] = (1ll * S[i - 1][j] * j + S[i - 1][j - 1]) % P;
		}
	}
	for (int i = 0; i <= m; ++i) {
		for (int j = 0; j <= i; ++j) {
			b[j] = (b[j] + 1ll * a[i] * S[i][j]) % P;
		}
	}
	int fac = 1;
	int ans = 0;
	for (int i = 0; i <= m; ++i) {
		ans = (ans + 1ll * b[i] * fac % P * qpow(x, i) % P * qpow(x + 1, n - i)) % P;
		fac = 1ll * fac * (n - i) % P;
	}
	std::cout << ans << "\n";
}
