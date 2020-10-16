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

const int N = 2005;

int n, m;
std::vector<int> E[N];
int fa[N][N], top[N][N];

void getfa(int rt, int u) {
	for (int v : E[u]) {
		if (v != fa[rt][u]) {
			fa[rt][v] = u;
			getfa(rt, v);
		}
	}
}

void dfs(std::vector<std::pair<int, int>> &tmp, int a, int b, int u) {
	if (b != u && top[a][u]) {
		tmp.emplace_back(b, u);
		return;
	}
	top[a][u] = b;
	for (int v : E[u]) {
		if (v != fa[a][u]) {
			dfs(tmp, a, b, v);
		}
	}
}

void add(int a, int b) {
	if (top[a][b] == b) {
		return;
	}
	if (top[a][b]) {
		add(top[a][b], b);
		return;
	}
	if (top[b][a]) {
		add(top[b][a], a);
		return;
	}
	top[a][b] = b, top[b][a] = a;
	std::vector<std::pair<int, int>> tmp;
	dfs(tmp, a, b, b), dfs(tmp, b, a, a);
	for (auto v : tmp) {
		add(v.first, v.second);
	}
}

int ans;

void getans(int rt, int u, int lst) {
	if (u != lst && top[lst][u]) {
		++ans;
		lst = u;
	}
	for (int v : E[u]) {
		if (v != fa[rt][u]) {
			getans(rt, v, lst);
		}
	}
}

int main() {
	read(n), read(m);
	for (int i = 1; i < n; ++i) {
		int u, v;
		read(u), read(v);
		E[u].push_back(v), E[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i) {
		fa[i][i] = 0;
		getfa(i, i);
	}
	for (int i = 1; i <= m; ++i) {
		int u, v;
		read(u), read(v);
		add(u, v);
	}
	for (int i = 1; i <= n; ++i) {
		getans(i, i, i);
	}
	print(ans >> 1);
}
