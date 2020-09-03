#include <bits/stdc++.h>

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
		static int num[40];
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		for (*num = 0; x; x /= 10) {
			num[++*num] = x % 10;
		}
		while (*num){
			putchar(num[*num] ^ '0');
			--*num;
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
	const int MAX_LEN = 1 << 19;
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
		std::vector<Complex> fa(fn), fb(fn), ga(gn), gb(gn);
		for (int i = 0; i < fn; ++i) {
			fa[i].x = f[i] >> 15, fa[i].y = 0;
			fb[i].x = f[i] & 32767, fb[i].y = 0;
		}
		for (int i = 0; i < gn; ++i) {
			ga[i].x = g[i] >> 15, ga[i].y = 0;
			gb[i].x = g[i] & 32767, gb[i].y = 0;
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
			ans[i] = (1 << 30) * A + (1 << 15) * B + C;
		}
		return ans;
	}
}

const int N = 200005, P = 200003, G = 2;

int n, pw[P], ord[P];

int main() {
	Poly::Init();
	read(n);
	pw[0] = 1;
	for (int i = 1; i < P - 1; ++i) {
		pw[i] = 1ll * pw[i - 1] * G % P;
	}
	for (int i = 0; i < P - 1; ++i) {
		ord[pw[i]] = i;
	}
	Poly::poly cnt(P - 1);
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		int x;
		read(x);
		ans -= 1ll * x * x % P;
		if (x) {
			++cnt[ord[x]];
		}
	}
	cnt = Poly::Mul(cnt, cnt);
	for (int i = 0; i < (int)cnt.size(); ++i) {
		ans += cnt[i] * pw[i % (P - 1)];
	}
	print(ans / 2);
}
