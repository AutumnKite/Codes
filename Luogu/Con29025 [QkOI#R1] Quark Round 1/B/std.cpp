#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>

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

const int N = 205, K = 5005, INF = 0x3f3f3f3f;

int n, m, k;
int dis[N][N];

struct Pig {
	int t, v;
	
	bool operator < (const Pig &rhs) const {
		return t < rhs.t;
	}
} a[K];

int f[K];

int main() {
	read(n), read(m), read(k);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			dis[i][j] = INF;
		}
		dis[i][i] = 0;
	}
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		read(u), read(v), read(w);
		dis[u][v] = dis[v][u] = std::min(dis[u][v], w);
	}
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
	}
	for (int i = 1; i <= k; ++i) {
		read(a[i].t), read(a[i].v);
	}
	std::sort(a + 1, a + 1 + k);
	a[0] = {0, 1}, f[0] = 0;
	int ans = 0;
	for (int i = 1; i <= k; ++i) {
		f[i] = 0;
		for (int j = 0; j < i; ++j) {
			if (a[j].t + dis[a[j].v][a[i].v] <= a[i].t) {
				f[i] = std::max(f[i], f[j] + 1);
			}
		}
		ans = std::max(ans, f[i]);
	}
	print(ans);
}
