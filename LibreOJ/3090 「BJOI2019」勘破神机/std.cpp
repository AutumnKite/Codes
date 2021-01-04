#include <bits/stdc++.h>

const int N = 505, P = 998244353;

int T, m;
int S[N][N], C[N][N];

long long l, r;
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

template <int W>
struct Complex {
	typedef Complex<W> _Comp;
	int a, b;

	Complex() { a = 0, b = 0; }
	Complex(int _a) : a(_a) { b = 0; }
	Complex(int _a, int _b) : a(_a), b(_b) {}

	_Comp conj() const {
		return _Comp(a, -b);
	}

	_Comp operator + (const _Comp &rhs) const {
		return _Comp((a + rhs.a) % P, (b + rhs.b) % P);
	}

	_Comp operator - (const _Comp &rhs) const {
		return _Comp((a - rhs.a) % P, (b - rhs.b) % P);
	}

	_Comp operator * (const int &rhs) const {
		return _Comp(1ll * a * rhs % P, 1ll * b * rhs % P);
	}

	_Comp operator * (const _Comp &rhs) const {
		return _Comp((1ll * a * rhs.a + 1ll * b * rhs.b * W) % P, (1ll * a * rhs.b + 1ll * rhs.a * b) % P);
	}

	_Comp operator / (const int &rhs) const {
		return *this * qpow(rhs, P - 2);
	}

	_Comp operator / (const _Comp &rhs) const {
		return *this * rhs.conj() * qpow((1ll * rhs.a * rhs.a - 1ll * rhs.b * rhs.b * W) % P, P - 2);
	}

	void debug() {
		std::cerr << a << " " << b << "\n";
	}
};

template <class Tp>
Tp qpow(Tp a, long long b) {
	Tp s(1);
	for (; b; b >>= 1) {
		if (b & 1) {
			s = s * a;
		}
		a = a * a;
	}
	return s;
}

template <class Tp>
Tp calc(Tp a, long long l, long long r) {
	if ((a.a + P) % P != 1) {
		return (qpow(a, r + 1) - qpow(a, l)) / (a - 1);
	} else {
		return (r - l + 1) % P;
	}
}

template <class Tp>
Tp solve(Tp a, Tp x, Tp b, Tp y) {
	Tp ans(0);
	for (int i = 0; i <= n; ++i) {
		Tp sum(0);
		for (int j = 0; j <= i; ++j) {
			sum = sum + qpow(a, j) * qpow(b, i - j) * calc(qpow(x, j) * qpow(y, i - j), l, r) * C[i][j];
		}
		ans = ans + sum * S[n][i];
	}
	int fac = 1;
	for (int i = 1; i <= n; ++i) {
		fac = 1ll * fac * i % P;
	}
	ans = ans * qpow(fac, P - 2);
	return ans;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	S[0][0] = 1;
	C[0][0] = 1;
	for (int i = 1; i <= 501; ++i) {
		S[i][0] = 0;
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			S[i][j] = (S[i - 1][j - 1] - 1ll * (i - 1) * S[i - 1][j]) % P;
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
	}

	std::cin >> T >> m;
	while (T--) {
		std::cin >> l >> r >> n;
		if (m == 2) {
			Complex<5> a = Complex<5>(0, 1) / 5;
			Complex<5> x = Complex<5>(1, 1) / 2;
			int inv = qpow((int)((r - l + 1) % P), P - 2);
			++l, ++r;
			std::cout << 1ll * (P + solve(a, x, a.conj(), x.conj()).a) * inv % P << "\n";
		} else {
			Complex<3> a = Complex<3>(3, 1) / 6;
			Complex<3> x = Complex<3>(2, 1);
			int inv = qpow((int)((r - l + 1) % P), P - 2);
			l = (l + 1) / 2, r = r / 2;
			std::cout << 1ll * (P + solve(a, x, a.conj(), x.conj()).a) * inv % P << "\n";
		}
	}
}