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

const int N = 105;

int n, m, a[N][N], b[N][N];
std::vector<int> E[N][N];

int mat[N], vis[N];

bool dfs(int u, int tag) {
	if (vis[u] == tag) {
		return false;
	}
	vis[u] = tag;
	for (int v = 0; v < n; ++v) {
		if (!E[u][v].empty() && (mat[v] == -1 || dfs(mat[v], tag))) {
			mat[v] = u;
			return true;
		}
	}
	return false;
}

int main() {
	read(n), read(m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			read(a[i][j]);
			--a[i][j];
			E[i][a[i][j] / m].push_back(a[i][j]);
		}
	}
	for (int j = 0; j < m; ++j) {
		for (int i = 0; i < n; ++i) {
			mat[i] = vis[i] = -1;
		}
		for (int i = 0; i < n; ++i) {
			dfs(i, i);
		}
		for (int i = 0; i < n; ++i) {
			b[mat[i]][j] = E[mat[i]][i].back();
			E[mat[i]][i].pop_back();
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			print(b[i][j] + 1, ' ');
		}
		putchar('\n');
	}
	for (int j = 0; j < m; ++j) {
		std::vector<int> res(n);
		for (int i = 0; i < n; ++i) {
			res[i] = b[i][j];
		}
		std::sort(res.begin(), res.end());
		for (int i = 0; i < n; ++i) {
			b[i][j] = res[i];
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			print(b[i][j] + 1, ' ');
		}
		putchar('\n');
	}
}
