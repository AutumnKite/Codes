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

const int N = 18, P = 998244353;

int n, p[1 << N], f[1 << N];

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

void FWT(int n, int *f) {
	for (int i = 0; i < n; ++i) {
		for (int S = 0; S < (1 << n); ++S) {
			if (S >> i & 1) {
				int T = S ^ (1 << i);
				int t = (f[T] + P - f[S]) % P;
				f[T] = (f[T] + f[S]) % P, f[S] = t;
			}
		}
	}
}

void IFWT(int n, int *f) {
	FWT(n, f);
	int inv = qpow(1 << n, P - 2);
	for (int i = 0; i < (1 << n); ++i) {
		f[i] = 1ll * f[i] * inv % P;
	}
}

int main() {
	read(n);
	int sum = 0;
	for (int i = 0; i < (1 << n); ++i) {
		read(p[i]);
		sum += p[i];
	}
	sum = qpow(sum, P - 2);
	for (int i = 0; i < (1 << n); ++i) {
		p[i] = 1ll * p[i] * sum % P;
	}
	p[0] = (p[0] + P - 1) % P;
	f[0] = (1 << n) - 1;
	for (int i = 1; i < (1 << n); ++i) {
		f[i] = P - 1;
	}
	FWT(n, p), FWT(n, f);
	for (int i = 1; i < (1 << n); ++i) {
		f[i] = 1ll * f[i] * qpow(p[i], P - 2) % P;
	}
	IFWT(n, f);
	int delta = P - f[0];
	for (int i = 0; i < (1 << n); ++i) {
		print((f[i] + delta) % P);
	}
}
