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

const int N = 22;
const int P = 998244353;

int n, m;

struct Edge {
	int u, v;
} e[N * N];

int pw[N * N], inv[N + 1];
int bitcnt[1 << N];
int F[N + 1][1 << N], f[N + 1], g[N + 1];

void inc(int &a, int b) {
	(a += b) >= P ? a -= P : 0;
}

void dec(int &a, int b) {
	a < b ? a += P - b : a -= b;
}

int main() {
	read(n), read(m);
	inv[1] = 1;
	for (int i = 2; i <= n; ++i) {
		inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	}
	for (int i = 0; i < m; ++i) {
		read(e[i].u), read(e[i].v);
		--e[i].u, --e[i].v;
	}
	pw[0] = 1;
	for (int i = 1; i <= m; ++i) {
		pw[i] = 1ll * pw[i - 1] * 2 % P;
	}
	for (register int S = 0; S < (1 << n); ++S) {
		bitcnt[S] = bitcnt[S >> 1] + (S & 1);
		int v = 0;
		for (register int i = 0; i < m; ++i) {
			if ((S >> e[i].u & 1) && (S >> e[i].v & 1)) {
				++v;
			}
		}
		F[bitcnt[S]][S] = pw[v];
	}
	for (int k = 0; k <= n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (register int S = 0; S < (1 << n); ++S) {
				if (S >> i & 1) {
					inc(F[k][S], F[k][S ^ (1 << i)]);
				}
			}
		}
	}
	int ans = 0;
	for (register int S = 0; S < (1 << n); ++S) {
		f[0] = F[0][S];
		g[0] = 0;
		for (int i = 1; i <= n; ++i) {
			f[i] = F[i][S];
			g[i] = 0;
			for (int j = 1; j < i; ++j) {
				g[i] = (g[i] + 1ll * g[j] * f[i - j]) % P;
			}
			g[i] = (P - g[i] + 1ll * f[i] * i) % P;
		}
		g[0] = 1;
		f[0] = 1;
		for (int i = 1; i <= n; ++i) {
			g[i] = 1ll * g[i] * inv[i] % P;
			f[i] = 0;
			for (int j = 0; j < i; ++j) {
				f[i] = (f[i] + 1ll * f[j] * g[i - j]) % P;
			}
		}
		if ((n - bitcnt[S]) & 1) {
			dec(ans, f[n]);
		} else {
			inc(ans, f[n]);
		}
	}
	print(ans);
}
