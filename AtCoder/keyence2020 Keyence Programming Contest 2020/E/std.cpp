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

const int N = 100005, M = 200005, INF = 1000000000;

int n, m, D[N], col[N], flag[N], p[N];
std::vector<std::pair<int, int>> E[N];
int ans[M];

void paint(int u) {
	if (~col[u]) {
		return;
	}
	for (auto p : E[u]) {
		int v = p.first, id = p.second;
		if (col[v] == -1 && D[u] == D[v]) {
			col[u] = 0, col[v] = 1;
			ans[id] = D[u];
			return;
		}
		if (~col[v]) {
			col[u] = col[v] ^ 1;
			ans[id] = D[u];
		}
	}
}

int main() {
	read(n), read(m);
	for (int i = 1; i <= n; ++i) {
		read(D[i]);
		col[i] = -1;
		flag[i] = 0;
		p[i] = i;
	}
	for (int i = 1; i <= m; ++i) {
		int u, v;
		read(u), read(v), ans[i] = INF;
		E[u].push_back({v, i}), E[v].push_back({u, i});
		if (D[v] <= D[u]) {
			flag[u] = 1;
		}
		if (D[u] <= D[v]) {
			flag[v] = 1;
		}
	}
	if (*std::min_element(flag + 1, flag + 1 + n) == 0) {
		print(-1);
		return 0;
	}
	std::sort(p + 1, p + 1 + n, [&](int x, int y) {
		return D[x] < D[y];
	});
	for (int i = 1; i <= n; ++i) {
		paint(p[i]);
	}
	for (int i = 1; i <= n; ++i) {
		if (col[i] == 0) {
			putchar('W');
		} else {
			putchar('B');
		}
	}
	putchar('\n');
	for (int i = 1; i <= m; ++i) {
		print(ans[i]);
	}
}
