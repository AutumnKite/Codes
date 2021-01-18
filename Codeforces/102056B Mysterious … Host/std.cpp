#include <bits/stdc++.h>

int P, G;

std::vector<int> prime_factors(int n) {
	std::vector<int> res;
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			res.push_back(i);
			while (n % i == 0) {
				n /= i;
			}
		}
	}
	if (n > 1) {
		res.push_back(n);
	}
	return res;
}

void inc(int &a, int b) {
	(a += b) >= P ? a -= P : 0;
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

int mul(int a, int b) {
	return 1ll * a * b % P;
}

int qpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = mul(s, a);
		}
		a = mul(a, a);
	}
	return s;
}

void getG() {
	std::vector<int> pf = prime_factors(P - 1);
	auto check = [&](int g) {
		for (int v : pf) {
			if (qpow(g, (P - 1) / v) == 1) {
				return false;
			}
		}
		return true;
	};
	G = 1;
	while (!check(G)) {
		++G;
	}
}

namespace Poly {
	const int MAX_LEN = 1 << 18;

	typedef std::vector<int> poly;

	int omega[MAX_LEN], inv[MAX_LEN];

	void Init(int n) {
		for (int m = 1; m < n; m <<= 1) {
			int w = qpow(G, (P - 1) / (m << 1));
			omega[m] = 1;
			for (int i = 1; i < m; ++i) {
				omega[m + i] = mul(omega[m + i - 1], w);
			}
		}
		inv[1] = 1;
		for (int i = 2; i < n; ++i) {
			inv[i] = mul(P - P / i, inv[P % i]);
		}
	}

	poly rev;

	int get(int _n) {
		int n = 1;
		while (n < _n) {
			n <<= 1;
		}
		return n;
	}

	void init(int n) {
		int k = 0;
		while ((1 << k) < n) {
			++k;
		}
		rev.resize(n), rev[0] = 0, --k;
		for (int i = 1; i < n; ++i) {
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k);
		}
	}

	void DFT(poly &f, int n) {
		f.resize(n);
		static unsigned long long F[MAX_LEN];
		for (int i = 0; i < n; ++i) {
			F[rev[i]] = f[i];
		}
		for (int m = 1; m < n; m <<= 1) {
			for (int p = 0, l = m << 1; p < n; p += l) {
				int *W = omega + m;
				unsigned long long *F0 = F + p, *F1 = F0 + m;
				for (int i = 0; i < m; ++i, ++F0, ++F1, ++W) {
					int t = (*F1) * (*W) % P;
					*F1 = *F0 + P - t, *F0 += t;
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			f[i] = (F[i] % P + P) % P;
		}
	}

	void IDFT(poly &f, int n) {
		DFT(f, n), std::reverse(f.begin() + 1, f.end());
		int t = qpow(n, P - 2);
		for (int i = 0; i < n; ++i) {
			f[i] = mul(f[i], t);
		}
	}

	poly Plus(poly a, poly b) {
		int n = std::max(a.size(), b.size());
		a.resize(n), b.resize(n);
		for (int i = 0; i < n; ++i) {
			inc(a[i], b[i]);
		}
		return a;
	}

	poly Minus(poly a, poly b) {
		int n = std::max(a.size(), b.size());
		a.resize(n), b.resize(n);
		for (int i = 0; i < n; ++i) {
			dec(a[i], b[i]);
		}
		return a;
	}

	poly Mul(poly a, poly b, int _n = -1) {
		int na = (int)a.size(), nb = (int)b.size(), n = _n;
		if (!na || !nb || !n) {
			return {};
		}
		if (n == -1) {
			n = na + nb - 1;
		}
		_n = n, n = get(n);
		init(n), DFT(a, n), DFT(b, n);
		for (int i = 0; i < n; ++i) {
			a[i] = mul(a[i], b[i]);
		}
		IDFT(a, n);
		a.resize(_n);
		return a;
	}

	poly Inv(poly f, int _n) {
		int n = get(_n);
		f.resize(n);
		poly g(1);
		g[0] = qpow(f[0], P - 2);
		for (int m = 2; m <= n; m <<= 1) {
			int l = m << 1;
			poly tmp(f.begin(), f.begin() + m);
			init(l), DFT(tmp, l), DFT(g, l);
			for (int i = 0; i < l; ++i) {
				g[i] = (2 + 1ll * (P - tmp[i]) * g[i]) % P * g[i] % P;
			}
			IDFT(g, l), g.resize(m);
		}
		g.resize(_n);
		return g;
	}
}

Poly::poly calc(int _n) {
	int n = Poly::get(_n);
	Poly::poly f(1);
	for (int m = 2; m <= n; m <<= 1) {
		int l = m << 1;
		Poly::init(l);
		Poly::DFT(f, l);
		Poly::poly a(l), b(l);
		for (int i = 0; i < m; ++i) {
			int f2 = 1ll * f[i] * f[i] % P;
			a[i] = (3ll * f2 * f2 + 2ll * f2 + P - Poly::omega[m + i]) % P;
			b[i] = (4ll * f2 * f[i] + 4ll * f[i] + P - Poly::omega[m + i] - 1) % P;
		}
		for (int i = m; i < l; ++i) {
			int f2 = 1ll * f[i] * f[i] % P;
			a[i] = (3ll * f2 * f2 + 2ll * f2 + Poly::omega[i]) % P;
			b[i] = (4ll * f2 * f[i] + 4ll * f[i] + Poly::omega[i] - 1) % P;
		}
		Poly::IDFT(a, l), Poly::IDFT(b, l);
		a.resize(m), b.resize(m);
		b = Poly::Inv(b, m);
		Poly::DFT(a, l), Poly::DFT(b, l);
		for (int i = 0; i < l; ++i) {
			f[i] = 1ll * a[i] * b[i] % P;
		}
		Poly::IDFT(f, l), f.resize(m);
	}
	f.resize(_n);
	return f;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n >> P;
	++n;
	getG();
	Poly::Init(Poly::get(2 * n));
	Poly::poly f(calc(n));
	for (int i = 1; i < n; ++i) {
		std::cout << f[i] << "\n";
	}
}
