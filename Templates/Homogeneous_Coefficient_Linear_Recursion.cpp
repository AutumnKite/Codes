#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>

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

const int P = 998244353, G = 3;

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

namespace Poly {
	const int MAX_LEN = 1 << 18;

	typedef std::vector<int> poly;

	int omega[MAX_LEN], inv[MAX_LEN];

	void Init() {
		for (int m = 1; m < MAX_LEN; m <<= 1) {
			int w = qpow(G, (P - 1) / (m << 1));
			omega[m] = 1;
			for (int i = 1; i < m; ++i) {
				omega[m + i] = mul(omega[m + i - 1], w);
			}
		}
		inv[1] = 1;
		for (int i = 2; i < MAX_LEN; ++i) {
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

	poly Pow2(poly a) {
		int _n = 2 * (int)a.size() - 1;
		int n = get(_n);
		init(n), DFT(a, n);
		for (int i = 0; i < n; ++i) {
			a[i] = mul(a[i], a[i]);
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

	poly Mod(const poly &a, const poly &b, const poly &ib, int m, int l) {
		int n = a.size();
		poly A(a);
		if (n < m) {
			A.resize(m - 1);
			return A;
		}
		std::reverse(A.begin(), A.end()), A.resize(n - m + 1);
		init(l), DFT(A, l);
		for (int i = 0; i < l; ++i) {
			A[i] = 1ll * A[i] * ib[i] % P;
		}
		IDFT(A, l);
		A.resize(n - m + 1), std::reverse(A.begin(), A.end());
		DFT(A, l);
		for (int i = 0; i < l; ++i) {
			A[i] = 1ll * A[i] * b[i] % P;
		}
		IDFT(A, l);
		A = Minus(a, A);
		A.resize(m - 1);
		return A;
	}

	poly Pow(poly a, int n, poly b) {
		int m = b.size(), len = get(2 * m);
		poly ib(b);
		std::reverse(ib.begin(), ib.end());
		ib = Inv(ib, m);
		init(len);
		DFT(b, len);
		DFT(ib, len);
		poly s(1, 1);
		for (; n; n >>= 1) {
			if (n & 1) {
				s = Mod(Mul(s, a), b, ib, m, len);
			}
			a = Mod(Pow2(a), b, ib, m, len);
		}
		return s;
	}
}

int n, k;

int main() {
	Poly::Init();
	read(n), read(k);
	Poly::poly g(k + 1);
	for (int i = 1; i <= k; ++i) {
		read(g[k - i]);
		g[k - i] = (P - g[k - i] % P) % P;
	}
	g[k] = 1;
	g = Poly::Pow({0, 1}, n, g);
	int ans = 0;
	for (int i = 0; i < k; ++i) {
		int x;
		read(x), x = (x % P + P) % P;
		ans = (ans + 1ll * x * g[i]) % P;
	}
	print(ans);
}
