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

const int N = 405, P = 998244353;

int n, a[N], b[N], sa, sb;
int fac[N], inv[N], pw[N][N];

void init() {
	fac[0] = 1;
	for (int i = 1; i < N; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	inv[1] = 1;
	for (int i = 2; i < N; ++i) {
		inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	}
}

int f[N][N];

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]), read(b[i]);
		sa += a[i], sb += b[i];
	}
	init();
	for (int i = 1; i <= n; ++i) {
		pw[i][0] = 1;
		for (int j = 1; j <= b[i]; ++j) {
			pw[i][j] = 1ll * pw[i][j - 1] * a[i] % P;
		}
	}
	f[0][0] = P - 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = sa; j >= a[i]; --j) {
			for (int k = sb; k >= 0; --k) {
				int s = 1;
				for (int l = 0; l < b[i] && l <= k; ++l) {
					f[j][k] = (f[j][k] + 1ll * (P - f[j - a[i]][k - l]) * s % P * pw[i][l]) % P;
					s = 1ll * s * inv[l + 1] % P;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= sa; ++i) {
		int s = 1;
		for (int j = 0; j <= sb; ++j) {
			s = 1ll * s * inv[i] % P;
			ans = (ans + 1ll * f[i][j] * fac[j] % P * s) % P;
		}
	}
	print(1ll * ans * sa % P);
}
