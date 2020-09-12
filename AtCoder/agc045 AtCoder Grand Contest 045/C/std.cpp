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

int n, A, B;
int f[N][2], g[N][2];

int main() {
	read(n), read(A), read(B);
	if (A > B) {
		std::swap(A, B);
	}
	f[0][0] = f[0][1] = 1;
	for (int i = 1; i < B; ++i) {
		f[i][0] = f[i][1] = 0;
		for (int j = A; j <= i; ++j) {
			f[i][0] = (f[i][0] + f[i - j][1]) % P;
		}
		for (int j = 1; j <= i; ++j) {
			f[i][1] = (f[i][1] + f[i - j][0]) % P;
		}
	}
	int s = 0;
	for (int i = 1; i < n; ++i) {
		if (i < A) {
			g[i][0] = 1;
		}
		for (int j = 1; j < A && j < i; ++j) {
			g[i][0] = (g[i][0] + g[i - j][1]) % P;
		}
		if (i < B) {
			g[i][1] = f[i][1];
		}
		for (int j = 1; j < B && j < i; ++j) {
			g[i][1] = (g[i][1] + 1ll * g[i - j][0] * f[j - 1][1]) % P;
		}
		if (n - i < A) {
			s = (s + g[i][1]) % P;
		}
		if (n - i < B) {
			s = (s + 1ll * g[i][0] * f[n - i][1]) % P;
		}
	}
	int ans = 1;
	for (int i = 1; i <= n; ++i) {
		ans = 2ll * ans % P;
	}
	ans = (ans + P - s) % P;
	print(ans);
}
