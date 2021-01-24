#include <bits/stdc++.h>

const int P = 998244353, G = 3;

void inc(int &a, int b) {
	a + b >= P ? a += b - P : a += b;
}

void dec(int &a, int b) {
	a < b ? a += P - b : a -= b;
}

int plus(int a, int b) {
	return a + b >= P ? a + b - P : a + b;
}

int minus(int a, int b) {
	return a < b ? a + P - b : a - b;
}

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

namespace po {
	const int MAX_LEN = 1 << 18;
	const int EXP_BLOCKS = 16;

	typedef std::vector<int> poly;

	int omega[MAX_LEN], inv[MAX_LEN];

	void init_omega(int n = MAX_LEN) {
		for (int m = 1; m < n; m <<= 1) {
			int w = qpow(G, (P - 1) / (m << 1));
			omega[m] = 1;
			for (int i = 1; i < m; ++i) {
				omega[m + i] = 1ll * omega[m + i - 1] * w % P;
			}
		}
	}

	void init_inv(int n = MAX_LEN) {
		inv[1] = 1;
		for (int i = 2; i < n; ++i) {
			inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
		}
	}

	poly rev;

	int enlarge_to_pow2(int _n) {
		int n = 1;
		while (n < _n) {
			n <<= 1;
		}
		return n;
	}

	void init_rev(int n) {
		if (n == (int)rev.size()) {
			return;
		}
		int k = 0;
		while ((1 << k) < n) {
			++k;
		}
		rev.resize(n);
		rev[0] = 0;
		for (int i = 1; i < n; ++i) {
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
		}
	}

	void DFT(poly &f, int n) {
		f.resize(n);
		static unsigned long long F[MAX_LEN];
		for (int i = 0; i < n; ++i) {
			F[rev[i]] = f[i];
		}
		for (int m = 1; m < n; m <<= 1) {
			if (m & (1 << 15)) {
				for (int i = 0; i < n; ++i) {
					F[i] %= P;
				}
			}
			for (int p = 0; p < n; p += m << 1) {
				int *W = omega + m;
				unsigned long long *F0 = F + p, *F1 = F + p + m;
				for (int i = 0; i < m; ++i, ++W, ++F0, ++F1) {
					int t = *F1 * *W % P;
					*F1 = *F0 + P - t, *F0 += t;
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			f[i] = F[i] % P;
		}
	}

	void IDFT(poly &f, int n) {
		DFT(f, n);
		std::reverse(f.begin() + 1, f.end());
		int t = 1ll * (P - P / n) * inv[P % n] % P;
		for (int i = 0; i < n; ++i) {
			f[i] = 1ll * f[i] * t % P;
		}
	}

	poly Plus(poly a, poly b) {
		if (a.size() < b.size()) {
			a.swap(b);
		}
		for (int i = 0; i < (int)b.size(); ++i) {
			inc(a[i], b[i]);
		}
		return a;
	}

	poly Minus(poly a, poly b) {
		a.resize(std::max(a.size(), b.size()));
		for (int i = 0; i < (int)b.size(); ++i) {
			dec(a[i], b[i]);
		}
		return a;
	}

	poly Mul(poly a, poly b, int _n = -1) {
		if (a.empty() || b.empty() || !_n) {
			return poly();
		}
		if (_n == -1) {
			_n = a.size() + b.size() - 1;
		}
		int n = enlarge_to_pow2(_n);
		init_rev(n);
		DFT(a, n), DFT(b, n);
		for (int i = 0; i < n; ++i) {
			a[i] = 1ll * a[i] * b[i] % P;
		}
		IDFT(a, n);
		a.resize(_n);
		return a;
	}

	poly Inv(poly f, int _n) {
		int n = enlarge_to_pow2(_n);
		f.resize(n);
		poly g(1, qpow(f[0], P - 2));
		for (int m = 2; m <= n; m <<= 1) {
			int l = m << 1;
			poly tmp(f.begin(), f.begin() + m);
			init_rev(l);
			DFT(tmp, l), DFT(g, l);
			for (int i = 0; i < l; ++i) {
				g[i] = (2 + 1ll * g[i] * (P - tmp[i])) % P * g[i] % P;
			}
			IDFT(g, l);
			g.resize(m);
		}
		g.resize(_n);
		return g;
	}
}

const int N = 100005;

int n;

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

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	po::init_omega(), po::init_inv();

	std::cin >> n;
	init(n);
	po::poly f(n + 1);
	for (int i = 0; i <= n; ++i) {
		f[i] = 1ll * qpow(2, 1ll * i * (i - 1) / 2 % (P - 1)) * inv[i] % P;
	}
	f = po::Minus(po::poly(1, 1), po::Inv(f, n + 1));
	for (int i = 0; i <= n; ++i) {
		f[i] = 1ll * f[i] * fac[i] % P;
	}

	for (int i = 1; i <= n; ++i) {
		if (i == 1) {
			std::cout << 1 << "\n";
		} else if (i == 2) {
			std::cout << -1 << "\n";
		} else {
			std::cout << 1ll * fac[i - 1] * qpow(2, (1ll * i * (i - 1) / 2 - i) % (P - 1)) % P * qpow(f[i], P - 2) % P << "\n";
		}
	}
}
