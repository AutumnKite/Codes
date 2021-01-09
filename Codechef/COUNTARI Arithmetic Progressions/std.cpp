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

namespace Poly {
	const int MAX_LEN = 1 << 16;
	const double pi = acos(-1);

	typedef std::vector<long long> poly;

	Complex omega[MAX_LEN];

	void Init() {
		for (int m = 1; m < MAX_LEN; m <<= 1) {
			for (int i = 0; i < m; ++i) {
				omega[m + i] = {cos(pi / m * i), sin(pi / m * i)};
			}
		}
	}

	int get(int _n) {
		int n = 1;
		while (n < _n) {
			n <<= 1;
		}
		return n;
	}

	std::vector<int> rev;

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

	poly Mul(const poly &f, const poly &g) {
		int fn = f.size(), gn = g.size(), _n = fn + gn - 1;
		poly res(_n);
		int n = get(_n);
		std::vector<Complex> ft(n), gt(n);
		for (int i = 0; i < fn; ++i) {
			ft[i].x = f[i];
		}
		for (int i = 0; i < gn; ++i) {
			gt[i].x = g[i];
		}
		init(n), DFT(ft, n), DFT(gt, n);
		for (int i = 0; i < n; ++i) {
			ft[i] = ft[i] * gt[i];
		}
		IDFT(ft, n);
		for (int i = 0; i < _n; ++i) {
			res[i] = ft[i].x + 0.5;
		}
		return res;
	}
}

const int B = 1000, N = 100005, C = N / B + 5;

int n, m;
int a[N];

int tot, L[C], R[C], bel[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		m = std::max(m, a[i] + 1);
	}

	tot = (n - 1) / B + 1;
	for (int i = 1; i <= tot; ++i) {
		L[i] = (i - 1) * B + 1;
		R[i] = std::min(i * B, n);
		for (int j = L[i]; j <= R[i]; ++j) {
			bel[j] = i;
		}
	}

	Poly::Init();
	Poly::poly pre(m), suf(m);
	for (int i = 1; i <= n; ++i) {
		++suf[a[i]];
	}
	long long ans = 0;
	for (int i = 1; i <= tot; ++i) {
		for (int j = L[i]; j <= R[i]; ++j) {
			--suf[a[j]];
		}
		Poly::poly res = Poly::Mul(pre, suf);
		for (int j = L[i]; j <= R[i]; ++j) {
			ans += res[a[j] * 2];
			for (int k = j + 1; k <= R[i]; ++k) {
				int v = 2 * a[j] - a[k];
				if (0 <= v && v < m) {
					ans += pre[v];
				}
				v = 2 * a[k] - a[j];
				if (0 <= v && v < m) {
					ans += suf[v];
				}
			}
			++pre[a[j]];
		}
	}
	std::cout << ans << "\n";
}