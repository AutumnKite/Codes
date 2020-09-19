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

const int N = 200005, INF = 0x3f3f3f3f;

int n, a[N];

struct State {
	int v0, p0, p1, a;

	int operator [] (int k) {
		return k <= p0 ? v0 : (k <= p1 ? v0 - 1 : k <= a ? v0 - 2 : INF);
	}

	int calc(int na, int i, int j) {
		return (*this)[i] + (i - j > 0) + (i - j > a - na);
	}

	int get(int na, int i) {
		return std::min({calc(na, 0, i), calc(na, p0 + 1, i), calc(na, p1 + 1, i)});
	}

	State trans(int na) {
		State g;
		g.a = na, g.v0 = get(na, 0);
		int l, r;
		l = 0, r = na;
		while (l <= r) {
			int md = (l + r) >> 1;
			if (get(na, md) == g.v0) {
				g.p0 = md;
				l = md + 1;
			} else {
				r = md - 1;
			}
		}
		g.p1 = g.p0;
		l = g.p0 + 1, r = na;
		while (l <= r) {
			int md = (l + r) >> 1;
			if (get(na, md) == g.v0 - 1) {
				g.p1 = md;
				l = md + 1;
			} else {
				r = md - 1;
			}
		}
		return g;
	}
};

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	State f;
	f.v0 = 0, f.p0 = f.p1 = f.a = 0;
	for (int i = 1; i <= n; ++i) {
		f = f.trans(a[i]);
	}
	f = f.trans(0);
	print(f[0]);
}
