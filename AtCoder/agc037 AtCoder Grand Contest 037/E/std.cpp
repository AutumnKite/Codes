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

const int N = 5005;

int n, k;
char a[N];
int len;
char b[N], ans[N];

void check(int l, int r) {
	int k = 0;
	for (int i = r + 1; i <= n && k < len; ++i) {
		b[++k] = a[i];
	}
	for (int i = r == n ? l - 1 : n; i && k < len; --i) {
		b[++k] = a[i];
	}
	if (std::lexicographical_compare(b + 1, b + 1 + k, ans + 1, ans + 1 + k)) {
		for (int i = 1; i <= k; ++i) {
			ans[i] = b[i];
		}
	}
}

int main() {
	read(n), read(k);
	readStr(a + 1);
	char c = *std::min_element(a + 1, a + 1 + n);
	int now = 0, mx = 0;
	for (int i = 1; i <= n; ++i) {
		++now;
		if (i == n || a[i] != a[i + 1]) {
			if (a[i] == c) {
				mx = std::max(mx, (i == n ? now : 0) + now);
			}
			now = 0;
		}
	}
	if (k > 30 || (1ll << (k - 1)) * mx >= n) {
		for (int i = 1; i <= n; ++i) {
			putchar(c);
		}
		putchar('\n');
		return 0;
	}
	len = n - mx * (1 << (k - 1));
	for (int i = 1; i <= len; ++i) {
		ans[i] = 'z' + 1;
	}
	now = 0;
	for (int i = 1; i <= n; ++i) {
		++now;
		if (a[i] != a[i + 1]) {
			if (a[i] == c && (i == n ? now : 0) + now == mx) {
				check(i - now + 1, i);
			}
			now = 0;
		}
	}
	for (int i = 1; i <= n - len; ++i) {
		putchar(c);
	}
	for (int i = 1; i <= len; ++i) {
		putchar(ans[i]);
	}
	putchar('\n');
}
