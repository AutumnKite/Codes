#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>

#define debug(...) fprintf(stderr, __VA_ARGS__)

#ifndef AT_HOME
#define getchar() IO::myGetchar()
#define putchar(x) IO::myPutchar(x)
#endif

namespace IO {
	static const int IN_BUF = 1 << 23, OUT_BUF = 1 << 23;

	inline char myGetchar() {
		static char buf[IN_BUF], *ps = buf, *pt = buf;
		if (ps == pt) {
			ps = buf, pt = buf + fread(buf, 1, IN_BUF, stdin);
		}
		return ps == pt ? EOF : *ps++;
	}

	template<typename T>
	inline bool read(T &x) {
		bool op = 0;
		char ch = getchar();
		x = 0;
		for (; !isdigit(ch) && ch != EOF; ch = getchar()) {
			op ^= (ch == '-');
		}
		if (ch == EOF) {
			return false;
		}
		for (; isdigit(ch); ch = getchar()) {
			x = x * 10 + (ch ^ '0');
		}
		if (op) {
			x = -x;
		}
		return true;
	}

	inline int readStr(char *s) {
		int n = 0;
		char ch = getchar();
		for (; isspace(ch) && ch != EOF; ch = getchar())
			;
		for (; !isspace(ch) && ch != EOF; ch = getchar()) {
			s[n++] = ch;
		}
		s[n] = '\0';
		return n;
	}

	inline void myPutchar(char x) {
		static char pbuf[OUT_BUF], *pp = pbuf;
		struct _flusher {
			~_flusher() {
				fwrite(pbuf, 1, pp - pbuf, stdout);
			}
		};
		static _flusher outputFlusher;
		if (pp == pbuf + OUT_BUF) {
			fwrite(pbuf, 1, OUT_BUF, stdout);
			pp = pbuf;
		}
		*pp++ = x;
	}

	template<typename T>
	inline void print_(T x) {
		if (x == 0) {
			putchar('0');
			return;
		}
		std::vector<int> num;
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		for (; x; x /= 10) {
			num.push_back(x % 10);
		}
		while (!num.empty()) {
			putchar(num.back() ^ '0');
			num.pop_back();
		}
	}

	template<typename T>
	inline void print(T x, char ch = '\n') {
		print_(x);
		putchar(ch);
	}

	inline void printStr_(const char *s, int n = -1) {
		if (n == -1) {
			n = strlen(s);
		}
		for (int i = 0; i < n; ++i) {
			putchar(s[i]);
		}
	}

	inline void printStr(const char *s, int n = -1, char ch = '\n') {
		printStr_(s, n);
		putchar(ch);
	}
}
using namespace IO;

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
	const int MAX_LEN = 1 << 18;
	const double pi = acos(-1);

	typedef std::vector<int> poly;

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

	poly Mul(const poly &f, const poly &g, int P, int _n = -1) {
		int fn = f.size(), gn = g.size();
		if (_n == -1) {
			_n = fn + gn - 1;
		}
		std::vector<Complex> fa(fn), fb(fn), ga(gn), gb(gn);
		for (int i = 0; i < fn; ++i) {
			fa[i] = {f[i] >> 15, 0};
			fb[i] = {f[i] & 32767, 0};
		}
		for (int i = 0; i < gn; ++i) {
			ga[i] = {g[i] >> 15, 0};
			gb[i] = {g[i] & 32767, 0};
		}
		int n = get(_n);
		init(n), DFT(fa, n), DFT(fb, n), DFT(ga, n), DFT(gb, n);
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

int n, k, L, x, y, P, g;
std::vector<int> pf;

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

std::vector<int> getPrimeFactors(int n) {
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

bool check(int g) {
	for (int v : pf) {
		if (qpow(g, (P - 1) / v) == 1) {
			return false;
		}
	}
	return true;
}

typedef std::vector<std::vector<int>> matrix;

matrix operator * (const matrix &a, const matrix &b) {
	matrix res(n, std::vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < n; ++k) {
			for (int j = 0; j < n; ++j) {
				res[i][j] = (res[i][j] + 1ll * a[i][k] * b[k][j]) % P;
			}
		}
	}
	return res;
}

matrix qpow(matrix a, int b) {
	matrix s(n, std::vector<int>(n));
	for (int i = 0; i < n; ++i) {
		s[i][i] = 1;
	}
	for (; b; b >>= 1) {
		if (b & 1) {
			s = s * a;
		}
		a = a * a;
	}
	return s;
}

int main() {
	Poly::Init();
	read(n), read(k), read(L), read(x), read(y), read(P);
	--x, --y;
	pf = getPrimeFactors(P - 1);
	g = 1;
	while (!check(g)) {
		++g;
	}
	g = qpow(g, (P - 1) / k);
	matrix A(n, std::vector<int>(n));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			read(A[i][j]);
		}
	}
	Poly::poly a(k), b(2 * k - 1);
	for (int i = 0; i < k; ++i) {
		int pw = qpow(g, i);
		matrix B(n, std::vector<int>(n));
		for (int p = 0; p < n; ++p) {
			for (int j = 0; j < n; ++j) {
				B[p][j] = 1ll * A[p][j] * pw % P;
			}
			B[p][p] = (B[p][p] + 1) % P;
		}
		int t = (1ll * i * (i - 1) / 2) % (P - 1);
		a[i] = 1ll * qpow(B, L)[x][y] * qpow(g, P - 1 - t) % P;
	}
	std::reverse(a.begin(), a.end());
	for (int i = 0; i < 2 * k - 1; ++i) {
		b[i] = qpow(g, (1ll * i * (i - 1) / 2) % (P - 1));
	}
	a = Poly::Mul(a, b, P, 2 * k);
	b = Poly::poly(a.begin() + k - 1, a.begin() + 2 * k - 1);
	for (int i = 0; i < k; ++i) {
		int t = (1ll * i * (i - 1) / 2) % (P - 1);
		b[i] = 1ll * b[i] * qpow(g, P - 1 - t) % P;
	}
	std::reverse(b.begin() + 1, b.end());
	int inv = qpow(k, P - 2);
	for (int i = 0; i < k; ++i) {
		b[i] = 1ll * b[i] * inv % P;
		print(b[i]);
	}
}