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

struct Graph {
	const static int N = 2505, M = 50005;
	const static int INF = 0x3f3f3f3f;
	const static long long INFll = 0x3f3f3f3f3f3f3f3fll;

	int n, S, T;
	int edge, to[M], pr[M], cap[M], hd[N];
	long long cost[M];

	void init(int _n, int _S, int _T) {
		n = _n, S = _S, T = _T, edge = 0;
		for (int i = 0; i < n; ++i) {
			hd[i] = -1;
		}
	}

	void addEdge(int u, int v, int w, long long c) {
		to[edge] = v, cap[edge] = w, cost[edge] = c, pr[edge] = hd[u], hd[u] = edge++;
		to[edge] = u, cap[edge] = 0, cost[edge] = -c, pr[edge] = hd[v], hd[v] = edge++;
	}

	int pre[N];
	int mn[N];
	long long dis[N];

	bool SPFA() {
		static bool vis[N];
		for (int i = 0; i < n; ++i) {
			vis[i] = 0, dis[i] = INFll;
		}
		std::vector<int> Q;
		Q.push_back(S), vis[S] = 1, dis[S] = 0, mn[S] = INF;
		for (int k = 0; k < (int)Q.size(); ++k) {
			int u = Q[k];
			vis[u] = 0;
			for (int i = hd[u]; ~i; i = pr[i]) {
				int v = to[i];
				if (cap[i] && dis[v] > dis[u] + cost[i]) {
					dis[v] = dis[u] + cost[i];
					mn[v] = std::min(mn[u], cap[i]);
					pre[v] = i;
					if (!vis[v]) {
						Q.push_back(v);
						vis[v] = 1;
					}
				}
			}
		}
		return dis[T] < INFll;
	}

	long long MCMF() {
		long long res = 0;
		while (SPFA()) {
			for (int u = T; u != S; u = to[pre[u] ^ 1]) {
				cap[pre[u]] -= mn[T], cap[pre[u] ^ 1] += mn[T];
			}
			res += dis[T] * mn[T];
		}
		return res;
	}
} G;

const int N = 1005;
const int d[2] = {-1, 1};

int n;

struct Node {
	int x, y, c;
} a[N], b[N];

int main() {
	read(n);
	for (int i = 0; i < n; ++i) {
		read(a[i].x), read(a[i].y), read(a[i].c);
	}
	for (int i = 0; i < n; ++i) {
		read(b[i].x), read(b[i].y), read(b[i].c);
	}
	G.init(2 * n + 6, 2 * n + 4, 2 * n + 5);
	for (int i = 0; i < n; ++i) {
		G.addEdge(G.S, i, a[i].c, 0);
		for (int x = 0; x < 2; ++x) {
			for (int y = 0; y < 2; ++y) {
				G.addEdge(i, 2 * n + (x << 1 | y), G.INF, d[x] * a[i].x + d[y] * a[i].y);
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		G.addEdge(n + i, G.T, b[i].c, 0);
		for (int x = 0; x < 2; ++x) {
			for (int y = 0; y < 2; ++y) {
				G.addEdge(2 * n + (x << 1 | y), n + i, G.INF, -d[x] * b[i].x - d[y] * b[i].y);
			}
		}
	}
	print(-G.MCMF());
}
