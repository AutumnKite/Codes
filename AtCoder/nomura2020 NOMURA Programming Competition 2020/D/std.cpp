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

const int N = 5005, P = 1000000007;

int n, p[N];

int fa[N], cyc[N], sz[N];

int find(int x) {
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

bool merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) {
		cyc[x] = 1;
		return false;
	}
	fa[y] = x, cyc[x] |= cyc[y], sz[x] += sz[y];
	return true;
}

int fac[N], pw[N], f[N];

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		fa[i] = i, cyc[i] = 0, sz[i] = 1;
	}
	int k = 0;
	for (int i = 1; i <= n; ++i) {
		read(p[i]);
		if (~p[i]) {
			merge(i, p[i]);
		} else {
			++k;
		}
	}
	pw[0] = 1, fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		pw[i] = 1ll * pw[i - 1] * (n - 1) % P;
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	int ans = 0;
	int now = 0;
	f[0] = 1;
	for (int i = 1; i <= n; ++i) {
		if (find(i) == i) {
			if (cyc[i]) {
				ans = (ans + pw[k]) % P;
			} else {
				ans = (ans + 1ll * pw[k - 1] * (sz[i] - 1)) % P;
				++now;
				for (int j = now; j; --j) {
					f[j] = (f[j] + 1ll * f[j - 1] * sz[i]) % P;
				}
			}
		}
	}
	for (int i = 2; i <= now; ++i) {
		ans = (ans + 1ll * fac[i - 1] * f[i] % P * pw[k - i]) % P;
	}
	ans = (1ll * n * pw[k] + P - ans) % P;
	print(ans);
}