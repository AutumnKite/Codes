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
	static const int N = 200005, M = 1000005, INF = 0x3f3f3f3f;

	int n, S, T;
	int edge, to[M], cap[M], pr[M], hd[N];

	void init(int _n, int _S, int _T) {
		n = _n, S = _S, T = _T, edge = 0;
		for (int i = 0; i < n; ++i) {
			hd[i] = -1;
		}
	}

	void addEdge(int u, int v, int w) {
		to[edge] = v, cap[edge] = w, pr[edge] = hd[u], hd[u] = edge++;
		to[edge] = u, cap[edge] = 0, pr[edge] = hd[v], hd[v] = edge++;
	}

	int dep[N];

	bool bfs() {
		for (int i = 0; i < n; ++i) {
			dep[i] = INF;
		}
		std::vector<int> Q;
		Q.push_back(S), dep[S] = 0;
		for (int i = 0; i < (int)Q.size(); ++i) {
			int u = Q[i];
			for (int j = hd[u]; ~j; j = pr[j]) {
				int v = to[j], w = cap[j];
				if (w && dep[v] == INF) {
					dep[v] = dep[u] + 1;
					Q.push_back(v);
					if (v == T) {
						return true;
					}
				}
			}
		}
		return false;
	}

	int nhd[N];

	int dfs(int u, int flow) {
		if (u == T || !flow) {
			return flow;
		}
		int ans = 0, tmp;
		for (int &i = nhd[u]; ~i; i = pr[i]) {
			int v = to[i];
			if (dep[v] == dep[u] + 1 && (tmp = dfs(v, std::min(flow, cap[i])))) {
				cap[i] -= tmp, cap[i ^ 1] += tmp, flow -= tmp, ans += tmp;
				if (!flow) {
					break;
				}
			}
		}
		if (!ans) {
			dep[u] = INF;
		}
		return ans;
	}

	int dinic() {
		int ans = 0;
		while (bfs()) {
			for (int i = 0; i < n; ++i) {
				nhd[i] = hd[i];
			}
			ans += dfs(S, INF);
		}
		return ans;
	}
} G;

const int N = 100005;

int n, a[N], b[N], ca, ida[N], cb, idb[N];

int getCycle(int *p, int *id) {
	for (int i = 0; i < n; ++i) {
		id[i] = -1;
	}
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (id[i] == -1) {
			for (int j = i; id[j] == -1; j = p[j]) {
				id[j] = cnt;
			}
			++cnt;
		}
	}
	return cnt;
}

int main() {
	read(n);
	for (int i = 0; i < n; ++i) {
		read(a[i]);
	}
	for (int i = 0; i < n; ++i) {
		read(b[i]);
	}
	ca = getCycle(a, ida);
	cb = getCycle(b, idb);
	G.init(ca + cb + 2, ca + cb, ca + cb + 1);
	int ans = n;
	for (int i = 0; i < n; ++i) {
		if (a[i] == i && b[i] == i) {
			--ans;
		} else if (a[i] == i) {
			G.addEdge(ca + idb[i], G.T, 1);
		} else if (b[i] == i) {
			G.addEdge(G.S, ida[i], 1);
		} else if (a[i] != b[i]) {
			G.addEdge(ca + idb[i], ida[i], 1);
		} else {
			G.addEdge(ida[i], ca + idb[i], 1);
			G.addEdge(ca + idb[i], ida[i], 1);
		}
	}
	print(ans - G.dinic());
}
