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

const int N = 505;

int n, P, r[N], l[N], f[N];

int main() {
	read(n), read(P);
	std::vector<std::pair<int, int>> a;
	for (int i = 0; i < n; ++i) {
		r[i] = sqrt(4 * n * n - i * i) + 1e-9 + 1;
		r[i] = std::min(r[i], 2 * n);
		l[i] = sqrt(n * n - i * i - 1) + 1e-9 + 1;
		a.push_back({l[i], -i});
	}
	for (int i = n; i < 2 * n; ++i) {
		r[i] = sqrt(4 * n * n - i * i) + 1e-9 + 1;
		r[i] = std::min(r[i], 2 * n);
		a.push_back({r[i], -i});
	}
	std::sort(a.begin(), a.end());
	int dfcmd = 0;
	for (int k = 0; k <= n; ++k) {
		for (int i = 0; i <= n; ++i) {
			f[i] = 0;
		}
		f[0] = 1;
		int c0 = 0, c1 = 0;
		for (auto v : a) {
			int id = -v.second;
			if (id >= n) {
				for (int i = c0; ~i; --i) {
					f[i] = 1ll * f[i] * (r[id] - i - c1) % P;
				}
				++c1;
			} else {
				for (int i = c0 + 1; ~i; --i) {
					f[i] = 1ll * f[i] * (r[id] - k - n - (c0 - i)) % P;
					if (i) {
						f[i] = (f[i] + 1ll * f[i - 1] * (l[id] - (i - 1) - c1)) % P;
					}
				}
				++c0;
			}
		}
		dfcmd = (dfcmd + (k & 1 ? -1 : 1) * f[k]) % P;
	}
	print((dfcmd + P) % P);
}
