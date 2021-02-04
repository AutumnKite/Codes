#include <bits/stdc++.h>

const int N = 5000005, P = 1000000007;

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

int cnt, prime[N * 2];
bool vis[N * 2];
int f[N * 2];
int fac[N * 2], inv[N * 2];
int g[N * 2], gi[N * 2];

void init(int n, int k) {
	cnt = 0;
	vis[1] = true;
	f[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			prime[++cnt] = i;
			f[i] = qpow(i, k);
		}
		for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
			vis[i * prime[j]] = true;
			f[i * prime[j]] = 1ll * f[i] * f[prime[j]] % P;
			if (i % prime[j] == 0) {
				break;
			}
		}
	}
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

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	init(2 * n + 1, 2 * n);
	for (int i = 0; i <= 2 * n + 1; ++i) {
		f[i] = 1ll * f[i] * inv[2 * n] % P;
		g[i] = i & 1 ? P - C(2 * n + 1, i) : C(2 * n + 1, i);
	}
	gi[0] = 0;
	for (int i = 1; i <= 2 * n + 1; ++i) {
		gi[i] = (gi[i - 1] + 1ll * g[i] * i) % P;
		g[i] = (g[i - 1] + g[i]) % P;
	}

	int e = (P + 1 - qpow(2 * n + 1, P - 2)) % P;
	int ans = 0;
	for (int i = 0; i <= 2 * n; ++i) {
		int sg = g[2 * n - i], sgi = gi[2 * n - i];
		if (i <= n) {
			ans = (ans + (1ll * f[i] * i % P * g[n - i] + 1ll * f[i] * gi[n - i]) % P * (P - e) + 1ll * f[i] * g[n - i] % P * n) % P;
			sg = (sg + P - g[n - i]) % P;
			sgi = (sgi + P - gi[n - i]) % P;
		}
		ans = (ans + (1ll * f[i] * i % P * sg + 1ll * f[i] * sgi) % P * e + 1ll * f[i] * sg % P * (P - n)) % P;
	}
	std::cout << 2 * ans % P << "\n";
}
