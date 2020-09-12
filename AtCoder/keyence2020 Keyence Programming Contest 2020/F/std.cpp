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

const int N = 15, P = 998244353;

int n, m, r[N], c[N], C[N][N], iC[N][N];
char s[N];
int f[N][N][3], g[N][N][3];

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

int main() {
	read(n), read(m);
	for (int i = 0; i < n; ++i) {
		readStr(s);
		for (int j = 0; j < m; ++j) {
			r[i] |= (s[j] == '#') << j;
			c[j] |= (s[j] == '#') << i;
		}
	}
	for (int i = 0; i <= std::max(n, m); ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
		for (int j = 0; j <= i; ++j) {
			iC[i][j] = qpow(C[i][j], P - 2);
		}
	}
	for (int i = 1; i <= n; ++i) {
		f[i][m][2] = 1ll * C[n][i] * (1 << (n - i)) % P;
	}
	int ans = 1 << n;
	for (int i = n; i; --i) {
		for (int j = m; j; --j) {
			f[i][j][0] = (f[i][j][1] + f[i][j][2]) % P;
			for (int k = 1; k < j; ++k) {
				g[i][k][1] = (g[i][k][1] + (2ll * f[i][j][2] + f[i][j][1]) * C[j][k]) % P;
				g[i][k][2] = (g[i][k][2] + 1ll * f[i][j][2] * C[j][k] % P * ((1 << (j - k)) - 2)) % P;
			}
			ans = (ans + 1ll * f[i][j][2] * ((1 << j) - 2)) % P;
			g[i][j][0] = (g[i][j][1] + g[i][j][2]) % P;
			for (int k = 1; k < i; ++k) {
				f[k][j][1] = (f[k][j][1] + (2ll * g[i][j][2] + g[i][j][1]) * C[i][k]) % P;
				f[k][j][2] = (f[k][j][2] + 1ll * g[i][j][2] * C[i][k] % P * ((1 << (i - k)) - 2)) % P;
			}
			ans = (ans + 1ll * g[i][j][2] * ((1 << i) - 2)) % P;
		}
	}
	for (int i = 1; i < (1 << n); ++i) {
		for (int j = 1; j < (1 << m); ++j) {
			int ci = 0, cj = 0;
			bool flag = 1;
			for (int k = 0; k < n; ++k) {
				if (i >> k & 1) {
					++ci;
					int w = r[k] & j;
					if (w == 0 || w == j) {
						flag = 0;
						break;
					}
				}
			}
			for (int k = 0; k < m; ++k) {
				if (j >> k & 1) {
					++cj;
					int w = c[k] & i;
					if (w == 0 || w == i) {
						flag = 0;
						break;
					}
				}
			}
			if (flag) {
				ans = (ans + 1ll * (f[ci][cj][0] + g[ci][cj][0]) * iC[n][ci] % P * iC[m][cj]) % P;
			}
		}
	}
	print(ans);
}