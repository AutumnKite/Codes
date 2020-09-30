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

const int N = 10005;

int n, a[N], vis[N];

int myabs(int a) {
	return a > 0 ? a : -a;
}

bool check(int p) {
	if (a[0] % p) {
		return false;
	}
	static int b[N];
	for (int i = 0; i < p - 1; ++i) {
		b[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		(b[i % (p - 1)] += a[i]) %= p;
	}
	for (int i = 0; i < p - 1; ++i) {
		if (b[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	read(n), ++n;
	int g = 0;
	for (int i = n - 1; ~i; --i) {
		read(a[i]);
		g = std::__gcd(g, myabs(a[i]));
	}
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			if (check(i)) {
				print(i);
			}
			for (int j = i + i; j <= n; j += i) {
				vis[j] = 1;
			}
		}
	}
	for (int i = 2; i * i <= g; ++i) {
		if (g % i == 0) {
			if (i > n) {
				print(i);
			}
			while (g % i == 0) {
				g /= i;
			}
		}
	}
	if (g > n) {
		print(g);
	}
}
