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

const int N = 100005, NN = 200005;

int n, m;
std::vector<int> G[N];

int idx, dfn[N], low[N];
int top, sta[N];
std::vector<std::vector<int>> dcc;

void tarjan(int rt, int u) {
	dfn[u] = low[u] = idx++;
	if (rt == u && G[u].empty()) {
		dcc.push_back({u});
		return;
	}
	sta[top++] = u;
	for (int v : G[u]) {
		if (dfn[v] == -1) {
			tarjan(rt, v);
			low[u] = std::min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				dcc.push_back({});
				do {
					dcc.back().push_back(sta[--top]);
				} while (dcc.back().back() != v);
				dcc.back().push_back(u);
			}
		} else {
			low[u] = std::min(low[u], dfn[v]);
		}
	}
}

int nn, w[NN], sz[NN], vis[NN];
std::vector<int> E[NN];
long long ans;

void getsz(int u, int fa = -1) {
	vis[u] = 1, sz[u] = (u < n);
	for (int v : E[u]) {
		if (v != fa) {
			getsz(v, u);
			sz[u] += sz[v];
		}
	}
}

void getans(int rt, int u, int fa = -1) {
	for (int v : E[u]) {
		if (v != fa) {
			getans(rt, v, u);
		}
	}
	long long s = 1ll * sz[rt] * sz[rt];
	s -= 1ll * (sz[rt] - sz[u]) * (sz[rt] - sz[u]);
	for (int v : E[u]) {
		if (v != fa) {
			s -= 1ll * sz[v] * sz[v];
		}
	}
	s -= (u < n);
	ans += s * w[u];
}

int main() {
	read(n), read(m);
	for (int i = 0; i < m; ++i) {
		int u, v;
		read(u), read(v), --u, --v;
		G[u].push_back(v), G[v].push_back(u);
	}
	for (int i = 0; i < n; ++i) {
		dfn[i] = -1;
	}
	for (int i = 0; i < n; ++i) {
		if (dfn[i] == -1) {
			tarjan(i, i);
		}
	}
	for (int i = 0; i < n; ++i) {
		w[i] = -1;
	}
	for (int i = 0; i < (int)dcc.size(); ++i) {
		w[n + i] = dcc[i].size();
		for (int v : dcc[i]) {
			E[n + i].push_back(v);
			E[v].push_back(n + i);
		}
	}
	nn = n + (int)dcc.size();
	for (int i = 0; i < nn; ++i) {
		vis[i] = 0;
	}
	for (int i = 0; i < nn; ++i) {
		if (!vis[i]) {
			getsz(i);
			getans(i, i);
		}
	}
	print(ans);
}
