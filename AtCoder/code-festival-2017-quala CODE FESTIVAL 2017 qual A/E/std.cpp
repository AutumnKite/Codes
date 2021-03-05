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

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	std::string up, down, left, right;
	std::cin >> up;
	std::cin >> down;
	std::cin >> left;
	std::cin >> right;

	std::vector<int> a(n), b(m);
	bool flag = true;
	for (int i = 0; i < n; ++i) {
		a[i] = (down[i] - '0') << 1 | (up[i] - '0');
		flag &= !a[i];
	}
	for (int i = 0; i < m; ++i) {
		b[i] = (right[i] - '0') << 1 | (left[i] - '0');
		flag &= !b[i];
	}
	
	if (flag) {
		std::cout << 1 << "\n";
		return 0;
	}

	std::vector<int> fac, inv;
	
	auto init = [&](int n) {
		fac.resize(n + 1), inv.resize(n + 1);
		fac[0] = 1;
		for (int i = 1; i <= n; ++i) {
			fac[i] = 1ll * fac[i - 1] * i % P;
		}
		inv[n] = qpow(fac[n], P - 2);
		for (int i = n; i >= 1; --i) {
			inv[i - 1] = 1ll * inv[i] * i % P;
		}
	};

	init(2 * (n + m));

	auto C = [&](int n, int m) -> int {
		if (m < 0 || m > n) {
			return 0;
		}
		return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
	};

	auto calc = [&](int n1, int n2, int m) -> int {
		if (m == 0) {
			return n1 + n2 == 0;
		}
		return C(n1 + n2 + m - 1, n1 + n2);
	};

	auto work = [&](std::vector<int> a, std::vector<int> b) {
		int n = a.size(), m = b.size();
		int sm = 0;
		for (int i = 0; i < m; ++i) {
			sm += b[i] >> 1;
		}
		int sa = 0, sb = 0;
		std::vector<int> suf(n + 1);
		for (int i = n - 1; i >= 0; --i) {
			suf[i] = ((a[i] == 3 ? 2ll : 1ll) * suf[i + 1] + ((a[i] & 1) + (a[i] >> 1)) * calc(sa, sb, sm)) % P;
			sa += a[i] & 1, sb += a[i] >> 1;
		}
		sm = 0;
		for (int i = 0; i < m; ++i) {
			sm += b[i] & 1;
		}
		sa = sb = 0;
		int res = 0;
		for (int i = 0; i < n; ++i) {
			if (a[i]) {
				res = (res + 1ll * calc(sa, sb, sm) * suf[i]) % P;
			}
			sa += a[i] & 1, sb += a[i] >> 1;
		}
		return res;
	};

	std::cerr << work(b, a) << "\n";

	// std::cout << (work(a, b) + work(b, a)) % P << "\n";
}