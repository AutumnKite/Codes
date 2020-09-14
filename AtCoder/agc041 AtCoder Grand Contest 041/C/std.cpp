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

const char c[10][10] = {"aa.", "..a", "..a"};

const char s[4][10][10] = {
	{"aabc", "ddbc", "bcaa", "bcdd"},
	{"aabba", "bcc.a", "b..cb", "a..cb", "abbaa"},
	{"aabc..", "ddbc..", "..aabc", "..ddbc", "bc..aa", "bc..dd"},
	{"aabbcc.", "dd.dd.a", "..d..da", "..d..db", "dd.dd.b", "..d..dc", "..d..dc"}
};

int n;
char a[1005][1005];

int main() {
	read(n);
	if (n == 2) {
		print(-1);
		return 0;
	}
	if (n == 3) {
		for (int i = 0; i < n; ++i) {
			printStr(c[i]);
		}
		return 0;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			a[i][j] = '.';
		}
	}
	for (int k = 0; k + 4 < n; k += 4) {
		for (int i = k; i < k + 4; ++i) {
			for (int j = k; j < k + 4; ++j) {
				a[i][j] = s[0][i - k][j - k];
			}
		}
	}
	int r = n % 4 + 4;
	for (int i = n - r; i < n; ++i) {
		for (int j = n - r; j < n; ++j) {
			a[i][j] = s[r - 4][i - n + r][j - n + r];
		}
	}
	for (int i = 0; i < n; ++i) {
		printStr(a[i], n);
	}
}
