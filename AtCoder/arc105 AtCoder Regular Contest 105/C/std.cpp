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

const int N = 9, M = 100005, INF = 0x3f3f3f3f;

int n, m, w[N], sum[N], d[N];

struct Bridge {
	int l, v;

	bool operator < (const Bridge &rhs) const {
		return v < rhs.v;
	}
} b[M];

int main() {
	read(n), read(m);
	for (int i = 1; i <= n; ++i) {
		read(w[i]);
	}
	std::sort(w + 1, w + 1 + n);
	for (int i = 1; i <= m; ++i) {
		read(b[i].l), read(b[i].v);
	}
	std::sort(b + 1, b + 1 + m);
	b[0].l = b[0].v = 0;
	for (int i = 1; i <= m; ++i) {
		b[i].l = std::max(b[i - 1].l, b[i].l);
	}
	int ans = INF;
	do {
		for (int i = 1; i <= n; ++i) {
			sum[i] = sum[i - 1] + w[i];
			d[i] = 0;
		}
		d[1] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = i; j <= n; ++j) {
				int p = std::lower_bound(b + 1, b + 1 + m, (Bridge){0, sum[j] - sum[i - 1]}) - b - 1;
				if (j == i && b[p].l > 0) {
					d[i] = INF;
				}
				d[j] = std::max(d[j], d[i] + b[p].l);
			}
		}
		ans = std::min(ans, d[n]);
	} while (std::next_permutation(w + 1, w + n + 1));
	if (ans == INF) {
		print(-1);
	} else {
		print(ans);
	}
}
