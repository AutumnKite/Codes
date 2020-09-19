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

const int N = 105;

int n, m, K, P;
long long P2;
int C[N][N], pw[N][N * N];
long long f[N][N];

int main() {
	// freopen("dfc.md", "r", stdin);
	read(n), read(m), read(K), read(P), P2 = 1ll * P * P;
	// n = m = K = 100, P = 998244353;
	for (int i = 0; i <= std::max(n, m); ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
	}
	for (int i = 0; i <= K; ++i) {
		pw[i][0] = 1;
		for (int j = 1; j <= n * m; ++j) {
			pw[i][j] = 1ll * pw[i][j - 1] * i % P;
		}
	}
	f[0][0] = 1;
	for (int k = 1; k <= K; ++k) {
		for (int i = n; ~i; --i) {
			for (int j = m; ~j; --j) {
				f[i][j] %= P;
				for (int d = 1; d <= n - i; ++d) {
					f[i + d][j] += f[i][j] * C[n - i][d] % P * pw[k][d * (m - j)] % P * pw[K - k + 1][d * j];
					if (f[i + d][j] >= P2) {
						f[i + d][j] -= P2;
					}
				}
			}
		}
		for (int i = n; ~i; --i) {
			for (int j = m; ~j; --j) {
				f[i][j] %= P;
				for (int d = 1; d <= m - j; ++d) {
					f[i][j + d] += 1ll * f[i][j] * C[m - j][d] % P * pw[k][d * (n - i)] % P * pw[K - k + 1][d * i];
					if (f[i][j + d] >= P2) {
						f[i][j + d] -= P2;
					}
				}
			}
		}
		for (int i = n; ~i; --i) {
			for (int j = m; ~j; --j) {
				f[i][j] %= P;
				for (int d = 1; d <= n - i; ++d) {
					f[i + d][j] += 1ll * (d & 1 ? -1 : 1) * f[i][j] * C[n - i][d] % P * pw[k][d * (m - j)] % P * pw[K - k][d * j] + P2;
					while (f[i + d][j] >= P2) {
						f[i + d][j] -= P2;
					}
				}
			}
		}
		for (int i = n; ~i; --i) {
			for (int j = m; ~j; --j) {
				f[i][j] %= P;
				for (int d = 1; d <= m - j; ++d) {
					f[i][j + d] += 1ll * (d & 1 ? -1 : 1) * f[i][j] * C[m - j][d] % P * pw[k][d * (n - i)] % P * pw[K - k][d * i] + P2;
					while (f[i][j + d] >= P2) {
						f[i][j + d] -= P2;
					}
				}
			}
		}
	}
	print(f[n][m] % P);
	debug("%.3lf\n", 1.0 * clock() / CLOCKS_PER_SEC);
}
