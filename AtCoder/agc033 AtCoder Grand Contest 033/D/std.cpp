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

const int N = 200;

int n, m;
char a[N][N];
int f[2][N][N][N], g[2][N][N][N];

int main() {
	read(n), read(m);
	for (int i = 1; i <= n; ++i) {
		readStr(a[i] + 1);
	}
	for (int u = 0; u < 2; ++u) {
		for (int i = 1; i <= n; ++i) {
			for (int k = i; k <= n; ++k) {
				f[u][i][m + 1][k] = m;
			}
		}
		for (int j = 1; j <= m; ++j) {
			for (int k = j; k <= m; ++k) {
				g[u][n + 1][j][k] = n;
			}
		}
	}
	int u = 0;
	for (int i = n; i; --i) {
		for (int j = m; j; --j) {
			bool flag = 1;
			for (int k = i; k <= n; ++k) {
				flag &= a[i][j] == a[k][j];
				if (flag) {
					if (j < m && a[i][j] == a[i][j + 1]) {
						f[u][i][j][k] = f[u][i][j + 1][k];
					} else {
						f[u][i][j][k] = j;
					}
				} else {
					f[u][i][j][k] = j - 1;
				}
			}
			flag = 1;
			for (int k = j; k <= m; ++k) {
				flag &= a[i][j] == a[i][k];
				if (flag) {
					if (i < n && a[i][j] == a[i + 1][j]) {
						g[u][i][j][k] = g[u][i + 1][j][k];
					} else {
						g[u][i][j][k] = i;
					}
				} else {
					g[u][i][j][k] = i - 1;
				}
			}
		}
	}
	for (int c = 1; ; ++c) {
		// debug("%d %d %d\n", c - 1, f[u][1][1][n], g[u][1][1][1]);
		if (f[u][1][1][n] == m) {
			print(c - 1);
			return 0;
		}
		u ^= 1;
		for (int i = n; i; --i) {
			for (int j = m; j; --j) {
				int p = m;
				for (int k = i; k <= n; ++k) {
					while (p >= j && g[u ^ 1][g[u ^ 1][i][j][p] + 1][j][p] < k) {
						--p;
					}
					f[u][i][j][k] = std::max(f[u ^ 1][i][f[u ^ 1][i][j][k] + 1][k], p);
				}
				p = n;
				for (int k = j; k <= m; ++k) {
					while (p >= i && f[u ^ 1][i][f[u ^ 1][i][j][p] + 1][p] < k) {
						--p;
					}
					g[u][i][j][k] = std::max(g[u ^ 1][g[u ^ 1][i][j][k] + 1][j][k], p);
				}
			}
		}
	}
}
