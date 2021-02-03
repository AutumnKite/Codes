#include <bits/stdc++.h>

struct Complex {
	double x, y;

	Complex operator + (const Complex &rhs) const {
		return {x + rhs.x, y + rhs.y};
	}

	Complex operator - (const Complex &rhs) const {
		return {x - rhs.x, y - rhs.y};
	}

	Complex operator * (const Complex & rhs) const {
		return {x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x};
	}
};

namespace po {
	const int MAX_LEN = 1 << 20;
	const double pi = acos(-1);

	typedef std::vector<int> poly;

	Complex omega[MAX_LEN];

	void init_omega() {
		for (int m = 1; m < MAX_LEN; m <<= 1) {
			for (int i = 0; i < m; ++i) {
				omega[m + i] = {cos(pi / m * i), sin(pi / m * i)};
			}
		}
	}

	int enlarge_to_pow2(int _n) {
		int n = 1;
		while (n < _n) {
			n <<= 1;
		}
		return n;
	}

	std::vector<int> rev;

	void init_rev(int n) {
		int k = 0;
		while ((1 << k) < n) {
			++k;
		}
		rev.resize(n), rev[0] = 0, --k;
		for (int i = 1; i < n; ++i) {
			rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k);
		}
	}

	void DFT(std::vector<Complex> &f, int n) {
		f.resize(n);
		static Complex F[MAX_LEN];
		for (int i = 0; i < n; ++i) {
			F[rev[i]] = f[i];
		}
		for (int m = 1; m < n; m <<= 1) {
			for (int p = 0; p < n; p += m << 1) {
				Complex *W = omega + m;
				Complex *F0 = F + p, *F1 = F0 + m;
				for (int i = 0; i < m; ++i, ++W, ++F0, ++F1) {
					Complex t = (*F1) * (*W);
					*F1 = *F0 - t, *F0 = *F0 + t;
				}
			}
		}
		for (int i = 0; i < n; ++i) {
			f[i] = F[i];
		}
	}

	void IDFT(std::vector<Complex> &f, int n) {
		DFT(f, n), std::reverse(f.begin() + 1, f.end());
		for (int i = 0; i < n; ++i) {
			f[i] = f[i] * (Complex){1.0 / n, 0};
		}
	}

	poly Mul(const poly &f, const poly &g, int P) {
		int fn = f.size(), gn = g.size(), _n = fn + gn - 1;
		std::vector<Complex> fa(fn), fb(fn), ga(gn), gb(gn);
		for (int i = 0; i < fn; ++i) {
			fa[i].x = f[i] >> 15, fa[i].y = 0;
			fb[i].x = f[i] & 32767, fb[i].y = 0;
		}
		for (int i = 0; i < gn; ++i) {
			ga[i].x = g[i] >> 15, ga[i].y = 0;
			gb[i].x = g[i] & 32767, gb[i].y = 0;
		}
		int n = enlarge_to_pow2(_n);
		init_rev(n);
		DFT(fa, n), DFT(fb, n), DFT(ga, n), DFT(gb, n);
		std::vector<Complex> a(n), b(n), c(n);
		for (int i = 0; i < n; ++i) {
			a[i] = fa[i] * ga[i];
			b[i] = fa[i] * gb[i] + fb[i] * ga[i];
			c[i] = fb[i] * gb[i];
		}
		IDFT(a, n), IDFT(b, n), IDFT(c, n);
		poly ans(_n);
		for (int i = 0; i < _n; ++i) {
			long long A = a[i].x + 0.5, B = b[i].x + 0.5, C = c[i].x + 0.5;
			A %= P, B %= P, C %= P;
			ans[i] = ((1 << 30) * A + (1 << 15) * B + C) % P;
			ans[i] = (P + ans[i]) % P;
		}
		return ans;
	}
}

const int N = 200005, P = 1000000007;

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

int fac[N * 2], inv[N * 2];

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

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	init(2 * n + 1);
	po::init_omega();
	po::poly f(2 * n + 2), g(2 * n + 2);
	for (int i = 0; i <= 2 * n + 1; ++i) {
		f[i] = i & 1 ? P - C(2 * n + 1, i) : C(2 * n + 1, i);
		g[i] = 1ll * qpow(i, 2 * n) * inv[2 * n] % P;
	}

	f = po::Mul(f, g, P);
	int e = qpow(2 * n + 1, P - 2);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans = (ans + 1ll * (1ll * e * i % P + n - i) * f[i]) % P;
	}
	for (int i = n + 1; i <= 2 * n; ++i) {
		ans = (ans + 1ll * (i - n + P - 1ll * e * i % P) * f[i]) % P;
	}
	std::cout << 2 * ans % P << "\n";
}