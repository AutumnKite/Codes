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

const int N = 200005;

int H, W, n, r, c;
char a[N], b[N];
int r1, c1, r2, c2;

int main() {
	read(H), read(W), read(n);
	read(r), read(c), --r, --c;
	readStr(a), readStr(b);
	r1 = 0, c1 = 0, r2 = H, c2 = W;
	for (int i = n - 1; ~i; --i) {
		if (b[i] == 'R') {
			c1 = std::max(c1 - 1, 0);
		} else if (b[i] == 'L') {
			c2 = std::min(c2 + 1, W);
		} else if (b[i] == 'D') {
			r1 = std::max(r1 - 1, 0);
		} else if (b[i] == 'U') {
			r2 = std::min(r2 + 1, H);
		}
		if (a[i] == 'R') {
			c2 = std::max(c2 - 1, c1);
		} else if (a[i] == 'L') {
			c1 = std::min(c1 + 1, c2);
		} else if (a[i] == 'D') {
			r2 = std::max(r2 - 1, r1);
		} else if (a[i] == 'U') {
			r1 = std::min(r1 + 1, r2);
		}
		if (r1 == r2 || c1 == c2) {
			printStr("NO");
			return 0;
		}
	}
	if (r1 <= r && r < r2 && c1 <= c && c < c2) {
		printStr("YES");
	} else {
		printStr("NO");
	}
}
