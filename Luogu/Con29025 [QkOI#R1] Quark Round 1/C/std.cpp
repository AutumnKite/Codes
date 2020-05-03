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

const int N = 1000005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n, a[N], dep[N], sum[N];
std::vector<int> E[N];
long long ans[N], down[N];
long long Ans;

void dfs1(int u, int fa = 0) {
	sum[u] = a[u];
	for (int v : E[u]) {
		if (v != fa) {
			dep[v] = dep[u] + 1;
			dfs1(v, u);
			sum[u] += sum[v];
		}
	}
}

void dfs2(int u, int fa = 0) {
	long long mn = INF, cmn = INF, rmn = INF;
	for (int v : E[u]) {
		if (v != fa) {
			ans[v] = ans[u] - 2 * sum[v] + sum[1];
			dfs2(v, u);
			long long t = std::min(down[v], 0ll + sum[v]);
			if (t < mn) {
				cmn = mn, mn = t;
			} else if (t < cmn) {
				cmn = t;
			}
			rmn = std::min(rmn, down[v]);
		}
	}
	down[u] = std::min(mn + sum[u], INF);
	Ans = std::max(Ans, ans[u] - rmn);
	Ans = std::max(Ans, ans[u] - mn - cmn);
}

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	for (int i = 1, u, v; i < n; ++i) {
		read(u), read(v);
		E[u].push_back(v), E[v].push_back(u);
	}
	dfs1(1);
	for (int i = 2; i <= n; ++i) {
		ans[1] += sum[i];
	}
	Ans = -INF;
	dfs2(1);
	print(Ans);
}
