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

int n, T;
int a[N], b[N], p[N];

int f[35];

int main() {
	read(n), read(T);
	for (int i = 1; i <= n; ++i) {
		read(a[i]), read(b[i]);
		++a[i], b[i] += a[i];
		p[i] = i;
	}
	std::sort(p + 1, p + 1 + n, [&](int x, int y) {
		return 1ll * b[x] * (a[y] - 1) < 1ll * b[y] * (a[x] - 1);
	});
	int m = n;
	while (m && a[p[m]] == 1) {
		--m;
	}
	std::sort(p + 1 + m, p + 1 + n, [&](int x, int y) {
		return b[x] < b[y];
	});
	for (int i = 0; i <= 30; ++i) {
		f[i] = INF;
	}
	f[0] = 0;
	for (int i = 1; i <= m; ++i) {
		for (int j = 30; j; --j) {
			f[j] = std::min<long long>(f[j], 1ll * f[j - 1] * a[p[i]] + b[p[i]]);
		}
	}
	int ans = 0;
	for (int i = 0; i <= 30; ++i) {
		int now = f[i];
		int j = m + 1;
		while (j <= n && now + b[p[j]] <= T) {
			now += b[p[j]];
			++j;
		}
		if (now <= T) {
			ans = std::max(ans, i + j - m - 1);
		}
	}
	print(ans);
}
