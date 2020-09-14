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

int n, a[N];
int sz[N], f[N][N][2];

void inc(int &a, int b) {
	a + b >= P ? a += b - P : a += b;
}

void dec(int &a, int b) {
	a < b ? a += P - b : a -= b;
}

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

int solve(int l, int r, int lst) {
	if (l > r) {
		f[0][0][1] = 1;
		return 0;
	}
	int u = std::min_element(a + l, a + r + 1) - a;
	int ls = solve(l, u - 1, a[u]), rs = solve(u + 1, r, a[u]);
	sz[u] = sz[ls] + sz[rs] + 1;
	for (int i = 0; i <= sz[ls]; ++i) {
		for (int j = 0; j <= sz[rs]; ++j) {
			int A = 1ll * f[ls][i][1] * f[rs][j][1] % P;
			int B = (1ll * f[ls][i][0] * f[rs][j][0] + 1ll * f[ls][i][1] * f[rs][j][0] + 1ll * f[ls][i][0] * f[rs][j][1]) % P;
			inc(f[u][i + j][1], A);
			inc(f[u][i + j][0], B);
			dec(f[u][i + j + 1][1], A);
			inc(f[u][i + j + 1][0], A);
		}
	}
	for (int i = 0; i <= sz[u]; ++i) {
		f[u][i][0] = 1ll * f[u][i][0] * qpow(qpow(2, sz[u] - i) - 1, a[u] - lst) % P;
		f[u][i][1] = 1ll * f[u][i][1] * qpow(qpow(2, sz[u] - i), a[u] - lst) % P;
	}
	return u;
}

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	int rt = solve(1, n, 0);
	int ans = 0;
	for (int i = 0; i <= n; ++i) {
		inc(ans, f[rt][i][0]);
		inc(ans, f[rt][i][1]);
	}
	print(ans);
}
