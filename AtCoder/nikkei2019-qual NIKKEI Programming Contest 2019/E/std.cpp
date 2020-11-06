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

const int N = 100005;

int n, m, a[N];

struct Edge {
	int u, v, w;

	bool operator < (const Edge &rhs) const {
		return w < rhs.w;
	}
} E[N];

struct DSU {
	int fa[N], sz[N];
	long long sum[N];

	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			fa[i] = i, sz[i] = 1, sum[i] = a[i];
		}
	}

	int find(int x) {
		return fa[x] == x ? x : find(fa[x]);
	}

	int merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) {
			return x;
		}
		if (sz[x] < sz[y]) {
			std::swap(x, y);
		}
		sz[x] += sz[y], sum[x] += sum[y], fa[y] = x;
		return y;
	}

	void undo(int y) {
		int x = fa[y];
		if (x == y) {
			return;
		}
		sz[x] -= sz[y], sum[x] -= sum[y], fa[y] = y;
	}
} D;

int id[N];

int main() {
	read(n), read(m);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	for (int i = 1; i <= m; ++i) {
		read(E[i].u), read(E[i].v), read(E[i].w);
	}
	std::sort(E + 1, E + 1 + m);
	D.init(n);
	for (int i = 1; i <= m; ++i) {
		id[i] = D.merge(E[i].u, E[i].v);
	}
	int ans = 0;
	for (int i = m; i; --i) {
		if (E[i].w > D.sum[D.find(E[i].u)]) {
			D.undo(id[i]);
			++ans;
		}
	}
	print(ans);
}
