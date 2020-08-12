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

const int N = 100005, B = 1000;

int n, m, q;

struct Edge {
	int u, v, w, id;

	bool operator < (const Edge &rhs) const {
		return w > rhs.w;
	}
} E[N];

int pos[N];

void initEdge() {
	std::sort(E + 1, E + 1 + m);
	for (int i = 1; i <= m; ++i) {
		pos[E[i].id] = i;
	}
}

struct DSU {
	int fa[N], sz[N];
	int tp, sta[N];

	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			fa[i] = i, sz[i] = 1;
		}
		tp = 0;
	}

	int find(int x) {
		return fa[x] == x ? x : find(fa[x]);
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) {
			return false;
		}
		if (sz[x] < sz[y]) {
			std::swap(x, y);
		}
		fa[y] = x, sz[x] += sz[y];
		sta[++tp] = y;
		return true;
	}

	void undo() {
		int y = sta[tp], x = fa[y];
		sz[x] -= sz[y], fa[y] = y;
		--tp;
	}

	int getsz(int u) {
		return sz[find(u)];
	}
} D;

struct Query {
	int t, u, w;

	bool operator < (const Query &rhs) const {
		return w > rhs.w;
	}
};

std::vector<std::pair<int, int>> mo[N];

int ans[N];

int main() {
	read(n), read(m);
	for (int i = 1; i <= m; ++i) {
		read(E[i].u), read(E[i].v), read(E[i].w), E[i].id = i;
	}
	initEdge();
	read(q);
	std::vector<Query> qu;
	for (int k = 1; k <= q; ++k) {
		int op, u, w;
		read(op), read(u), read(w);
		if (op == 1) {
			mo[pos[u]].push_back({k, w});
		} else {
			qu.push_back({k, u, w});
		}
		if (k % B == 0 || k == q) {
			std::vector<int> id;
			for (int i = 1; i <= m; ++i) {
				if (!mo[i].empty()) {
					id.push_back(i);
				}
			}
			std::sort(qu.begin(), qu.end());
			D.init(n);
			int p = 1;
			for (auto x : qu) {
				while (p <= m && E[p].w >= x.w) {
					if (mo[p].empty()) {
						D.merge(E[p].u, E[p].v);
					}
					++p;
				}
				int cnt = 0;
				for (auto e : id) {
					int u = E[e].u, v = E[e].v, w = E[e].w;
					auto it = std::lower_bound(mo[e].begin(), mo[e].end(), std::make_pair(x.t, 0));
					if (it != mo[e].begin()) {
						--it, w = it->second;
					}
					if (w >= x.w) {
						cnt += D.merge(u, v);
					}
				}
				ans[x.t] = D.getsz(x.u);
				while (cnt--) {
					D.undo();
				}
			}
			for (int e : id) {
				E[e].w = mo[e].back().second;
				mo[e].clear();
			}
			qu.clear();
			initEdge();
		}
	}
	for (int i = 1; i <= q; ++i) {
		if (ans[i]) {
			print(ans[i]);
		}
	}
}
