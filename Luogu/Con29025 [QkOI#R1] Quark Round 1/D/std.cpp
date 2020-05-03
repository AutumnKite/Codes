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

const int N = 100005;

int n, q;

struct Query {
	int op, l, r;
} Q[N];

int ans[N];

struct Node {
	int op, l, r, id;

	bool operator < (const Node &rhs) const {
		return l < rhs.l || (l == rhs.l && op < rhs.op);
	}
};

struct BIT {
	int c[N];

	void add(int x, int v) {
		for (; x; x ^= x & -x) {
			c[x] += v;
		}
	}

	int query(int x) {
		int s = 0;
		for (; x <= n; x += x & -x) {
			s += c[x];
		}
		return s;
	}
} T;

void solve(int l, int r) {
	if (l == r) {
		if (Q[l].op == 2) {
			print(ans[l]);
		}
		return;
	}
	int md = (l + r) >> 1;
	solve(l, md);
	std::vector<Node> vec;
	for (int i = l; i <= md; ++i) {
		if (Q[i].op == 1) {
			vec.push_back({Q[i].op, Q[i].l, Q[i].r, i});
		}
	}
	for (int i = md + 1; i <= r; ++i) {
		if (Q[i].op == 2) {
			vec.push_back({Q[i].op, Q[i].l, Q[i].r, i});
		}
	}
	std::sort(vec.begin(), vec.end());
	for (Node v : vec) {
		if (v.op == 1) {
			T.add(v.r, 1);
		} else {
			ans[v.id] += T.query(v.r);
		}
	}
	for (Node v : vec) {
		if (v.op == 1) {
			T.add(v.r, -1);
		}
	}
	solve(md + 1, r);
}

int main() {
	read(n), read(q);
	for (int i = 1; i <= q; ++i) {
		read(Q[i].op), read(Q[i].l), read(Q[i].r);
	}
	solve(1, q);
}
