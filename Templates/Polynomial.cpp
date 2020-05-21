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

	std::pair<poly, poly> Div(const poly &a, const poly &b) {
		int n = a.size(), m = b.size();
		poly Q, R;
		if (n < m) {
			R = a, R.resize(m - 1);
			return {Q, R};
		}
		poly A(a), B(b);
		std::reverse(A.begin(), A.end()), A.resize(n - m + 1);
		std::reverse(B.begin(), B.end()), B.resize(n - m + 1);
		Q = Mul(A, Inv(B, n - m + 1));
		Q.resize(n - m + 1), std::reverse(Q.begin(), Q.end());
		R = Minus(a, Mul(b, Q)), R.resize(m - 1);
		return {Q, R};
	}

	poly Der(poly f) {
		int n = (int)f.size();
		for (int i = 1; i < n; ++i) {
			f[i - 1] = mul(f[i], i);
		}
		f.pop_back();
		return f;
	}

	poly Int(poly f) {
		f.push_back(0);
		int n = f.size();
		for (int i = n - 1; i; --i) {
			f[i] = mul(f[i - 1], inv[i]);
		}
		f[0] = 0;
		return f;
	}

	poly Ln(const poly &a, int n) {
		poly res = Int(Mul(Der(a), Inv(a, n)));
		return res.resize(n), res;
	}

	poly ExpNewton(poly f, int _n) {
		int n = get(_n);
		f.resize(n);
		poly g(1);
		g[0] = 1;
		for (int m = 2; m <= n; m <<= 1) {
			int l = m << 1;
			poly tmp = Ln(g, m);
			for (int i = 0; i < m; ++i) {
				tmp[i] = minus(f[i], tmp[i]);
			}
			inc(tmp[0], 1);
			init(l), DFT(tmp, l), DFT(g, l);
			for (int i = 0; i < l; ++i) {
				g[i] = mul(g[i], tmp[i]);
			}
			IDFT(g, l), g.resize(m);
		}
		return g.resize(_n), g;
	}

	void ExpSolve(const poly &f, poly &g, int l, int r) {
		if (l + 1 == r) {
			if (l) {
				g[l] = mul(g[l], inv[l]);
			} else {
				g[l] = 1;
			}
			return;
		}
		int md = (l + r + 1) >> 1;
		ExpSolve(f, g, l, md);
		poly tmp(Mul(poly(g.begin() + l, g.begin() + md), 
		  poly(f.begin(), f.begin() + r - l - 1), r - l - 1));
		for (int i = md; i < r; ++i) {
			inc(g[i], tmp[i - l - 1]);
		}
		ExpSolve(f, g, md, r);
	}

	poly Exp(poly f, int _n) {
		f.resize(_n), f = Der(f);
		poly g(_n);
		ExpSolve(f, g, 0, _n);
		return g;
	}

	poly Pow(poly a, int k, int n) {
		a.resize(n);
		int t = n;
		for (int i = 0; i < n; ++i) {
			if (a[i]) {
				t = i;
				break;
			}
		}
		if (t == n) {
			if (!k) {
				a[0] = 1;
			}
			return a;
		}
		int vi = qpow(a[t], P - 2), vk = qpow(a[t], k);
		for (int i = 0; i < n - t; ++i) {
			a[i] = mul(a[i + t], vi);
		}
		a.resize(n - t);
		t = std::min(1ll * t * k, 1ll * n);
		if (t == n) {
			a.resize(n);
			for (int i = 0; i < n; ++i) {
				a[i] = 0;
			}
			return a;
		}
		a = Ln(a, n - t);
		for (int i = 0; i < n - t; ++i) {
			a[i] = mul(a[i], k);
		}
		a = Exp(a, n - t), a.resize(n);
		for (int i = n - t - 1; ~i; --i) {
			a[i + t] = mul(a[i], vk);
		}
		for (int i = 0; i < t; ++i) {
			a[i] = 0;
		}
		return a;
	}
}

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

namespace MTTPoly {
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

	poly Mul(const poly &f, const poly &g, int P) {
		int fn = f.size(), gn = g.size(), _n = fn + gn - 1;
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
