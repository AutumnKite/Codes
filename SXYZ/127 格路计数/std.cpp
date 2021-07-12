#include <bits/stdc++.h>

const int P = 998244353;

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

std::vector<int> fac, inv;

void init(int n) {
	fac.resize(n + 1), inv.resize(n + 1);
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	inv[n] = qpow(fac[n], P - 2);
	for (int i = n; i >= 1; --i) {
		inv[i - 1] = 1ll * inv[i] * i % P;
	}
}

int C(int n, int m) {
	if (m < 0 || m > n) {
		return 0;
	}
	return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}

int det(std::vector<std::vector<int>> a) {
	int n = a.size();
	int ans = 1;
	for (int i = 0; i < n; ++i) {
		int k = -1;
		for (int j = i; j < n; ++j) {
			if (a[j][i]) {
				k = j;
				break;
			}
		}
		if (k == -1) {
			return 0;
		}
		if (k != i) {
			a[i].swap(a[k]);
			ans = (P - ans) % P;
		}
		int t = qpow(a[i][i], P - 2);
		for (int j = i + 1; j < n; ++j) {
			int p = 1ll * (P - a[j][i]) * t % P;
			for (int k = i; k < n; ++k) {
				a[j][k] = (a[j][k] + 1ll * a[i][k] * p) % P;
			}
		}
		ans = 1ll * ans * a[i][i] % P;
	}
	return ans;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m, L;
	std::cin >> n >> m >> L;
	L -= n + m - 2;
	if (L <= 0) {
		std::cout << 0 << "\n";
		return 0;
	}
	init(n + m);
	std::vector<std::vector<int>> A(L - 1, std::vector<int>(L - 1));
	for (int i = 0; i < L - 1; ++i) {
		for (int j = 0; j < L - 1; ++j) {
			A[i][j] = C(n + m, n + j - i);
		}
	}
	std::cout << det(A) << "\n";
}