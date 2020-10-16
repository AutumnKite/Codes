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

const int N = 17, M = N * (N - 1) / 2, P = 998244353;

int n, m;

struct Edge {
	int u, v;
} E[M];

int pw[M + 1];
int cnt[1 << N], g[1 << N], f[1 << N];

int main() {
	read(n), read(m);
	for (int i = 0; i < m; ++i) {
		read(E[i].u), read(E[i].v);
		--E[i].u, --E[i].v;
	}
	pw[0] = 1;
	for (int i = 1; i <= m; ++i) {
		pw[i] = 2ll * pw[i - 1] % P;
	}
	for (int S = 0; S < (1 << n); ++S) {
		for (int i = 0; i < m; ++i) {
			if (S >> E[i].u & 1 && S >> E[i].v & 1) {
				++cnt[S];
			}
		}
	}
	for (int S = 1; S < (1 << n); ++S) {
		int hb = 1 << n;
		while (!(S & hb)) {
			hb >>= 1;
		}
		g[S] = 0;
		for (int T = S; T >= hb; T = (T - 1) & S) {
			g[S] = (g[S] + pw[cnt[S] - cnt[T] - cnt[S ^ T]]) % P;
		}
		f[S] = g[S];
		for (int T = S; T >= hb; T = (T - 1) & S) {
			f[S] = (f[S] + 2ll * (P - f[T]) * g[S ^ T]) % P;
		}
	}
	print(f[(1 << n) - 1]);
}
