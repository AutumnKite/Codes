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

const int N = 100005, P = 998244353, V = 716070898;

int n, m, pw[N];

struct Graph {
	std::vector<int> E[N];

	void addEdge(int u, int v) {
		if (u > v) {
			std::swap(u, v);
		}
		E[u].push_back(v);
	}

	int vis[N], sg[N], mx, sum[N];

	void getSG() {
		for (int i = 0; i <= n; ++i) {
			vis[i] = 0, sum[i] = 0;
		}
		for (int u = n; u; --u) {
			for (int v : E[u]) {
				vis[sg[v]] = u;
			}
			sg[u] = 0;
			while (vis[sg[u]] == u) {
				++sg[u];
			}
			sum[sg[u]] = (sum[sg[u]] + pw[u]) % P;
		}
		mx = n;
		while (mx >= 0 && !sum[mx]) {
			--mx;
		}
	}
} G[3];

void solve() {
	read(n);
	pw[0] = 1;
	for (int i = 1; i <= n; ++i) {
		pw[i] = 1ll * pw[i - 1] * V % P;
	}
	for (int k = 0; k < 3; ++k) {
		read(m);
		for (int i = 0; i < m; ++i) {
			int u, v;
			read(u), read(v);
			G[k].addEdge(u, v);
		}
		G[k].getSG();
	}
	int ans = 0;
	for (int x = 0; x <= G[0].mx; ++x) {
		for (int y = 0; y <= G[1].mx; ++y) {
			int z = x ^ y;
			if (z <= G[2].mx) {
				ans = (ans + 1ll * G[0].sum[x] * G[1].sum[y] % P * G[2].sum[z]) % P;
			}
		}
	}
	print(ans);
}

int main() {
	int T = 1;
	// read(T);
	while (T--) {
		solve();
	}
}
