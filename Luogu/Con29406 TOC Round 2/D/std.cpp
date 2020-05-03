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

const int N = 200005, LG = 18;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n, L, R, a[N];
std::vector<int> E[N];
int fa[N][LG];
long long mn[N][LG];

void dfs(int u) {
	for (int i = 1; i < LG; ++i) {
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
		mn[u][i] = std::min(mn[u][i - 1], mn[fa[u][i - 1]][i - 1]);
	}
	for (int v : E[u]) {
		if (v != fa[u][0]) {
			fa[v][0] = u, mn[v][0] = mn[u][0] + a[v];
			dfs(v);
		}
	}
}

long long get(int u) {
	long long tmp = mn[u][0], ans = INF;
	if (L) {
		for (int i = LG - 1; ~i; --i) {
			if ((L - 1) >> i & 1) {
				u = fa[u][i];
			}
		}
		if (u == 0) {
			return -INF;
		}
		u = fa[u][0];
	}
	for (int i = LG - 1; ~i; --i) {
		if ((R - L) >> i & 1) {
			ans = std::min(ans, mn[u][i]);
			u = fa[u][i];
		}
	}
	return tmp - ans;
}

int main() {
	read(n), read(L), read(R), ++R;
	if (n == 0) {
		print(0);
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	for (int i = 1, u, v; i < n; ++i) {
		read(u), read(v);
		E[u].push_back(v), E[v].push_back(u);
	}
	fa[1][0] = 0, mn[1][0] = a[1], dfs(1);
	long long ans = -INF;
	for (int i = 1; i <= n; ++i) {
		ans = std::max(ans, get(i));
	}
	if (ans == -INF) {
		printStr("Impossible");
	} else {
		print(ans);
	}
}
