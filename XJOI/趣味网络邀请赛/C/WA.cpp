#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

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
		std::vector<int> num;
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		for (; x; x /= 10) {
			num.push_back(x % 10);
		}
		while (!num.empty()) {
			putchar(num.back() ^ '0');
			num.pop_back();
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

const int N = 2005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n, m, a[N], p[N];
long long w[N], f[N][N];

struct Node {
	int v, w;
} b[N];

void solve() {
	read(n), read(m);
	a[0] = 0;
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		for (int j = a[i - 1] + 1; j <= a[i]; ++j) {
			p[j] = a[i - 1] + 1;
		}
	}
	for (int i = 1; i <= m; ++i) {
		read(b[i].v), read(b[i].w);
	}
	for (int i = 0; i <= a[n]; ++i) {
		w[i] = INF;
	}
	w[0] = 0;
	for (int i = 1; i <= m; ++i) {
		for (int j = b[i].w; j <= a[n]; ++j) {
			w[j] = std::min(w[j], w[j - b[i].w] + b[i].v);
		}
	}
	for (int i = 1; i <= a[1]; ++i) {
		for (int j = 1; j <= i; ++j) {
			f[i][j] = 0;
		}
	}
	for (int i = a[1] + 1; i <= a[n]; ++i) {
		for (int j = p[i]; j <= i; ++j) {
			f[i][j] = INF;
			for (int k = 1; k < j; ++k) {
				int mn = std::max(j - k, p[i - k]);
				f[i][j] = std::min(f[i][j], f[i - k][mn] + w[k]);
			}
		}
	}
	long long ans = 0;
	for (int i = 1; i <= a[n]; ++i) {
		if (f[i][p[i]] == INF) {
			print(-1);
			return;
		}
		ans += f[i][p[i]];
	}
	print(ans);
}

int main() {
	int T = 1;
	read(T);
	while (T--) {
		solve();
	}
}
/*
1
4 3
1 3 4 6
4 2
1 3
4 1
*/