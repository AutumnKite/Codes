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

const int N = 18, P = 1000000007;

int n, p[1 << N], dep[1 << N], fw[1 << N][N], w[1 << N], ans;

int main() {
	read(n);
	for (int i = 1 << (n - 1); i < (1 << n); ++i) {
		read(p[i]);
		--p[i];
		p[i] |= 1 << (n - 1);
	}
	for (int i = (1 << (n - 1)) - 1; i; --i) {
		dep[i] = dep[i << 1] + 1;
	}
	for (int i = 1; i < (1 << n); ++i) {
		fw[i][0] = i;
		for (int j = 1; j < n - dep[i]; ++j) {
			fw[i][j] = 1ll * fw[i][j - 1] * (i >> j) % P;
		}
	}
	for (int i = 1; i < (1 << (n - 1)); ++i) {
		int u = i << 1, v = i << 1 | 1;
		for (int k = 0; k < (1 << dep[u]); ++k) {
			int t = u << dep[u] | k;
			int s = fw[t][dep[i]];
			t = p[t];
			while (t) {
				s = 1ll * s * t % P;
				w[t] = (w[t] + s) % P;
				t >>= 1;
			}
		}
		for (int k = 0; k < (1 << dep[v]); ++k) {
			int t = v << dep[v] | k;
			int s = fw[t][dep[v]];
			t = p[t];
			while (t > 1) {
				s = 1ll * s * t % P;
				ans = (ans + 1ll * s * (t >> 1) % P * w[t ^ 1]) % P;
				t >>= 1;
			}
		}
		for (int k = 0; k < (1 << dep[u]); ++k) {
			int t = u << dep[u] | k;
			t = p[t];
			while (t) {
				w[t] = 0;
				t >>= 1;
			}
		}
	}
	print(ans);
}