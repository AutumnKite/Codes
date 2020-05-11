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

const int N = 200005;

int n, na, nb, m;
int pa[N], pb[N];
char s[N];

struct SuffixAutomaton {
	static const int N = 400005, C = 26;

	int cnt, cur;
	int trans[N][C], link[N], len[N];
	int id[N];

	int newNode(int Len) {
		int u = cnt++;
		link[u] = -1, len[u] = Len;
		memset(trans[u], -1, sizeof trans[u]);
		return u;
	}

	void init() {
		cnt = 0, cur = newNode(0), id[0] = cur;
	}

	void insert(int c) {
		int p = cur;
		cur = newNode(len[p] + 1);
		id[len[cur]] = cur;
		while (p != -1 && trans[p][c] == -1) {
			trans[p][c] = cur;
			p = link[p];
		}
		if (p == -1) {
			link[cur] = 0;
			return;
		}
		int q = trans[p][c];
		if (len[q] == len[p] + 1) {
			link[cur] = q;
			return;
		}
		int t = newNode(len[p] + 1);
		link[t] = link[q];
		memcpy(trans[t], trans[q], sizeof trans[t]);
		while (p != -1 && trans[p][c] == q) {
			trans[p][c] = t;
			p = link[p];
		}
		link[q] = link[cur] = t;
	}

	static const int LG = 19;

	std::vector<int> E[N];
	int fa[N][LG];

	void dfs(int u) {
		fa[u][0] = link[u];
		for (int i = 1; i < LG; ++i) {
			if (fa[u][i - 1] == -1) {
				fa[u][i] = -1;
			} else {
				fa[u][i] = fa[fa[u][i - 1]][i - 1];
			}
		}
		for (int v : E[u]) {
			dfs(v);
		}
	}

	void buildTree() {
		for (int i = 0; i < cnt; ++i) {
			E[i].clear();
		}
		for (int i = 1; i < cnt; ++i) {
			E[link[i]].push_back(i);
		}
		dfs(0);
	}

	int get(int l, int r) {
		int u = id[r];
		for (int i = LG - 1; ~i; --i) {
			if (fa[u][i] != -1 && len[fa[u][i]] >= r - l) {
				u = fa[u][i];
			}
		}
		return u;
	}
} A;

int get(int l, int r) {
	l = n - l + 1, r = n - r;
	std::swap(l, r);
	return A.get(l, r);
}

struct Graph {
	static const int N = 600005;

	int n, w[N], d[N];
	std::vector<int> E[N];
	long long f[N];

	void init(int _n) {
		n = _n;
		for (int i = 0; i < n; ++i) {
			d[i] = 0, w[i] = 0;
			E[i].clear();
		}
	}

	void addEdge(int u, int v) {
		E[u].push_back(v), ++d[v];
		debug("%d %d\n", u, v);
	}

	long long toposort() {
		std::vector<int> Q;
		for (int i = 0; i < n; ++i) {
			if (!d[i]) {
				Q.push_back(i);
			}
			f[i] = w[i];
		}
		long long ans = 0;
		for (int i = 0; i < (int)Q.size(); ++i) {
			int u = Q[i];
			ans = std::max(ans, f[u]);
			for (int v : E[u]) {
				f[v] = std::max(f[v], f[u] + w[v]);
				--d[v];
				if (!d[v]) {
					Q.push_back(v);
				}
			}
		}
		return (int)Q.size() == n ? ans : -1;
	}
} G;

void solve() {
	n = readStr(s);
	std::reverse(s, s + n);
	A.init();
	for (int i = 0; i < n; ++i) {
		A.insert(s[i] - 'a');
	}
	A.buildTree();
	debug("%d\n", A.cnt);
	for (int i = 0; i < A.cnt; ++i) {
		for (int j = 0; j < A.C; ++j) {
			if (A.trans[i][j] != -1) {
				debug("%d %d %c\n", i, A.trans[i][j], j + 'a');
			}
		}
	}
	read(na);
	G.init(A.cnt + na);
	for (int u = 0; u < A.cnt; ++u) {
		for (int v : A.E[u]) {
			G.addEdge(u, v);
		}
	}
	for (int i = 0; i < na; ++i) {
		int l, r;
		read(l), read(r);
		pa[i] = get(l, r);
		G.w[A.cnt + i] = r - l + 1;
		G.addEdge(pa[i], A.cnt + i);
	}
	read(nb);
	for (int i = 0; i < nb; ++i) {
		int l, r;
		read(l), read(r);
		pb[i] = get(l, r);
	}
	read(m);
	for (int i = 0; i < m; ++i) {
		int u, v;
		read(u), read(v), --u, --v;
		G.addEdge(A.cnt + u, pb[v]);
	}
	print(G.toposort());
}

int main() {
	freopen("test.out", "w", stderr);
	int T = 1;
	read(T);
	while (T--) {
		solve();
	}
}

/*
1
abbaabbaab
4
1 5
4 7
6 9
8 10
3
1 6
10 10
4 6
5
1 2
1 3
2 1
3 3
4 1
*/