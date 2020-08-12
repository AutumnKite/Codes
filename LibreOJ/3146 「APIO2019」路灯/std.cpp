#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>

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

const int N = 300005;

int n, q, m;
char st[N];

struct Node {
	int t, l, r, op;

	bool operator < (const Node &rhs) const {
		return l < rhs.l || (l == rhs.l && op != 0 && rhs.op == 0);
	}
} a[N * 4];

struct Cmp {
	bool operator ()(int x, int y) {
		return a[x].l < a[y].l || (a[x].l == a[y].l && x < y);
	}
};

long long ans[N];

struct BIT {
	long long c[N];

	void add(int x, int v) {
		for (; x; x ^= x & -x) {
			c[x] += v;
		}
	}

	long long query(int x) {
		long long s = 0;
		for (; x <= n; x += x & -x) {
			s += c[x];
		}
		return s;
	}
} T, Ti;

void solve(int l, int r) {
	if (l == r) {
		return;
	}
	int md = (l + r) >> 1;
	static std::vector<Node> vec;
	vec.clear();
	for (int i = l; i <= md; ++i) {
		if (a[i].op) {
			vec.push_back(a[i]);
		}
	}
	for (int i = md + 1; i <= r; ++i) {
		if (!a[i].op) {
			vec.push_back(a[i]);
		}
	}
	std::sort(vec.begin(), vec.end());
	for (auto v : vec) {
		if (v.op) {
			T.add(v.r, v.op);
			Ti.add(v.r, v.op * v.t);
		} else {
			ans[v.t] += T.query(v.r) * v.t - Ti.query(v.r);
		}
	}
	for (auto v : vec) {
		if (v.op) {
			T.add(v.r, -v.op);
			Ti.add(v.r, -v.op * v.t);
		}
	}
	solve(l, md), solve(md + 1, r);
}

int main() {
	// freopen("test.in", "r", stdin);
	// freopen("test.out", "w", stdout);
	read(n), read(q);
	readStr(st + 1);
	m = 0;
	std::set<int, Cmp> S;
	for (int i = 1; i <= n; ++i) {
		if (st[i] == '1') {
			int j = i;
			while (j <= n && st[j] == '1') {
				++j;
			}
			--j;
			a[++m] = {0, i, j, 1};
			S.insert(m);
			i = j;
		}
	}
	a[1200003] = {0, -1, -1, 1}, S.insert(1200003);
	a[1200004] = {0, n + 2, n + 2, 1}, S.insert(1200004);
	for (int i = 1; i <= q; ++i) {
		readStr(st);
		if (*st == 't') {
			int x;
			read(x);
			a[1200005] = {i, x, x, 1};
			auto nx = S.upper_bound(1200005), it = nx;
			--it;
			int v1 = *it, v2 = *nx;
			if (x <= a[v1].r) {
				a[++m] = {i, a[v1].l, a[v1].r, -1};
				if (x > a[v1].l) {
					a[++m] = {i, a[v1].l, x - 1, 1};
					S.insert(m);
				}
				if (x < a[v1].r) {
					a[++m] = {i, x + 1, a[v1].r, 1};
					S.insert(m);
				}
				S.erase(v1);
			} else {
				Node tmp = {i, x, x, 1};
				if (a[v1].r == x - 1) {
					a[++m] = {i, a[v1].l, a[v1].r, -1};
					tmp.l = a[v1].l;
					S.erase(v1);
				}
				if (a[v2].l == x + 1) {
					a[++m] = {i, a[v2].l, a[v2].r, -1};
					tmp.r = a[v2].r;
					S.erase(v2);
				}
				a[++m] = tmp;
				S.insert(m);
			}
			ans[i] = -23333333;
		} else {
			int l, r;
			read(l), read(r), --r;
			a[++m] = {i, l, r, 0};
			ans[i] = 0;
		}
		// for (int v : S) {
		// 	debug("%d ", v);
		// }
		// debug("\n");
	}
	// for (int i = 1; i <= m; ++i) {
	// 	debug("%d %d %d %d\n", a[i].t, a[i].l, a[i].r, a[i].op);
	// }
	debug("%d\n", m);
	solve(1, m);
	debug("dfcmd\n");
	for (int i = 1; i <= q; ++i) {
		if (ans[i] != -23333333) {
			print(ans[i]);
		}
	}
}
/*
5 4
01101
toggle 2
toggle 2
toggle 4
query 2 6
*/
