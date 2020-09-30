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

const int N = 155;

int n, m, P;

void inc(int &a, int b) {
	a + b >= P ? a += b - P : a += b;
}

namespace Even {
	int f[N];
	
	int solve(int n) {
		f[0] = 1;
		for (int i = 1; i <= n + 1; ++i) {
			f[i] = 0;
			for (int j = 0; j <= m / 2 && j < i; ++j) {
				inc(f[i], f[i - j - 1]);
			}
		}
		return f[n + 1];
	}
}

int f[N][N][N];

int main() {
	read(n), read(m), read(P);
	if (!(m & 1)) {
		print(1ll * Even::solve((n + 1) / 2) * Even::solve(n / 2) % P);
		return 0;
	}
	f[0][0][0] = 1;
	int t1 = (m - 1) / 2, t2 = (n + 1) / 2;
	for (int i = 1; i <= t1 + t2; ++i) {
		for (int j = 0; j < m + 2; ++j) {
			for (int k = 0; k < i; ++k) {
				inc(f[i][0][0], f[i - 1][j][k]);
				if (2 * i <= n) {
					inc(f[i][0][k + 1], f[i - 1][j][k]);
				}
				if (i > t1 && j + 1 < m + 2) {
					if (j > 0) {
						inc(f[i][j + 1][0], f[i - 1][j][k]);
					} else {
						inc(f[i][0][0], f[i - 1][j][k]);
					}
				}
				if (i > t1 && 2 * i <= n && std::max(j + 1, k + 2) < m + 2) {
					inc(f[i][std::max(j + 1, k + 2)][k + 1], f[i - 1][j][k]);
				}
			}
		}
	}
	int ans = 0;
	for (int j = 0; j < m + 2; ++j) {
		for (int k = 0; k <= t1 + t2; ++k) {
			inc(ans, f[t1 + t2][j][k]);
		}
	}
	print(ans);
}
