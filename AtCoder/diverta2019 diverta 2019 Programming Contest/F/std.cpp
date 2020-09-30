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

const int N = 20, M = N * (N - 1) / 2, P = 1000000007;

int n, m;

struct Edge {
	int u, v;
} E[M];

struct DSU {
	int fa[N];

	void init() {
		for (int i = 0; i < n; ++i) {
			fa[i] = i;
		}
	}

	int find(int x) {
		return fa[x] == x ? x : (fa[x] = find(fa[x]));
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) {
			return true;
		}
		fa[y] = x;
		return false;
	}
} D;

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

int fac[M + 1], inv[M + 1];

void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	inv[n] = qpow(fac[n], P - 2);
	for (int i = n; i; --i) {
		inv[i - 1] = 1ll * inv[i] * i % P;
	}
}

struct State {
	int n, b, c, s;
} f[1 << (N - 1)];

int main() {
	read(n), read(m);
	for (int i = 0; i < m; ++i) {
		read(E[i].u), read(E[i].v);
		--E[i].u, --E[i].v;
	}
	for (int S = 0; S < (1 << (n - 1)); ++S) {
		D.init();
		f[S].b = n - 1, f[S].n = m;
		for (int i = 0; i < n - 1; ++i) {
			if (S >> i & 1) {
				D.merge(E[i].u, E[i].v);
				--f[S].b, --f[S].n;
			}
		}
		for (int i = n - 1; i < m; ++i) {
			if (D.find(E[i].u) == D.find(E[i].v)) {
				--f[S].n;
			}
		}
	}
	init(m);
	int U = (1 << (n - 1)) - 1;
	f[U].c = 1, f[U].s = 0;
	for (int S = U - 1; ~S; --S) {
		for (int i = 0; i < n - 1; ++i) {
			if (!(S >> i & 1)) {
				int T = S | (1 << i);
				int k = f[S].n - f[T].n - 1;
				int c = 1ll * f[T].c * fac[f[T].n + k] % P * inv[f[T].n] % P;
				int s = 1ll * f[T].s * fac[f[T].n + k + 1] % P * inv[f[T].n + 1] % P;
				s = (s + 1ll * f[S].b * c) % P;
				f[S].c = (f[S].c + c) % P;
				f[S].s = (f[S].s + s) % P;
			}
		}
	}
	print(f[0].s);
}
