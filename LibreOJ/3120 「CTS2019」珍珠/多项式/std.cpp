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
}

int D, K, n, m, fac[100005], inv[100005];

int main() {
	Poly::Init();
	read(D), read(n), read(m), K = n - 2 * m;
	if (K >= D) {
		print(qpow(D, n));
		return 0;
	}
	if (K < 0) {
		print(0);
		return 0;
	}
	fac[0] = 1;
	for (int i = 1; i <= D; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	inv[D] = qpow(fac[D], P - 2);
	for (int i = D; i; --i) {
		inv[i - 1] = 1ll * inv[i] * i % P;
	}
	Poly::poly f(D + 1), g(D + 1);
	for (int i = 0; i <= D; ++i) {
		if (i <= K) {
			f[i] = 1ll * inv[i] * inv[K - i] % P;
			if ((K - i) & 1) {
				f[i] = (P - f[i]) % P;
			}
		}
		if (i <= D - 1 - K) {
			g[i] = 1ll * inv[i] * inv[D - 1 - K - i] % P;
		}
	}
	f = Poly::Mul(f, g);
	int ans = 0;
	for (int i = 0; i < D; ++i) {
		ans = (ans + (1ll * fac[D] * Poly::inv[D - i] % P) * 
		  (1ll * qpow((2ll * i + P - D) % P, n) * f[i] % P)) % P;
	}
	int t = 0;
	for (int i = 0; i <= K; ++i) {
		t = (t + 1ll * fac[D] * inv[i] % P * inv[D - i]) % P;
	}
	ans = (ans + 1ll * t * qpow(D, n)) % P;
	ans = 1ll * ans * qpow((P + 1) >> 1, D) % P;
	print(ans);
}
