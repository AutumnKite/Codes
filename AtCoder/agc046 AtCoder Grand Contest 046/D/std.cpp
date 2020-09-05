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

const int N = 305, P = 998244353, INF = 0x3f3f3f3f;

int n;
char s[N];

int f[N][N][N], g[N][N][N], h[N][N][N];

void inc(int &a, int b) {
	a + b >= P ? a += b - P : a += b;
}

void upd(int &a, int b) {
	a = std::max(a, b);
}

void solve() {
	n = readStr(s + 1);
	f[n][0][0] = 1;
	for (int i = n; i; --i) {
		for (int j = 0; j < i; ++j) {
			for (int k = 0; j + k < i; ++k) {
				inc(f[i - 1][j][k], f[i][j][k]);
				if (s[i] == '0') {
					inc(f[i][j][k + 1], f[i][j][k]);
				} else {
					inc(f[i][j + 1][k], f[i][j][k]);
				}
			}
		}
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			for (int k = 0; k <= n; ++k) {
				g[i][j][k] = -INF;
			}
		}
	}
	g[0][0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			for (int k = 0; j + k < i; ++k) {
				if (g[i - 1][j][k] >= 0) {
					if (s[i] == '0') {
						upd(g[i][j + 1][k], g[i - 1][j][k] - 1);
					} else {
						upd(g[i][j][k + 1], g[i - 1][j][k] - 1);
					}
					if (i < n) {
						upd(g[i + 1][j][k], g[i - 1][j][k] + 1);
						if (s[i] == '0' || s[i + 1] == '0') {
							upd(g[i + 1][j + 1][k], g[i - 1][j][k]);
						}
						if (s[i] == '1' || s[i + 1] == '1') {
							upd(g[i + 1][j][k + 1], g[i - 1][j][k]);
						}
					}
				}
			}
		}
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = n; ~j; --j) {
			for (int k = n; ~k; --k) {
				h[i][j][k] = g[i][j][k] >= 0;
				if (i) {
					h[i][j][k] |= h[i - 1][j][k];
				}
				if (j < n) {
					h[i][j][k] |= h[i][j + 1][k];
				}
				if (k < n) {
					h[i][j][k] |= h[i][j][k + 1];
				}
			}
		}
	}
	int ans = P - 1;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= i; ++j) {
			for (int k = 0; j + k <= i; ++k) {
				if (h[i][j][k]) {
					inc(ans, f[i][j][k]);
				}
			}
		}
	}
	print(ans);
}

int main() {
	int T = 1;
	// read(T);
	while (T--) {
		solve();
	}
}