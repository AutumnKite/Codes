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

const int N = 100005, P = 1000000007;

int n, q, a[N];

int getSum1(int x) {
	return (1ll * x * (x + 1) / 2) % P;
}

int getSum2(int x) {
	return (1ll * x * (x + 1) * (2 * x + 1) / 6) % P;
}

int plus(int a, int b) {
	return a + b >= P ? a + b - P : a + b;
}

int minus(int a, int b) {
	return a < b ? a + P - b : a - b;
}

struct Node {
	int s1, s2, si;
};

struct LazyNode {
	int x, y;

	void operator += (const LazyNode &rhs) {
		x = plus(x, rhs.x), y = plus(y, rhs.y);
	}
};

Node operator + (const Node &a, const Node &b) {
	return {plus(a.s1, b.s1), plus(a.s2, b.s2), plus(a.si, b.si)};
}

struct SegmentTree {
	Node val[N << 2];
	LazyNode lz[N << 2];

	void build(int u, int l, int r) {
		lz[u].x = lz[u].y = 0;
		if (l == r) {
			val[u].s1 = a[l];
			val[u].s2 = 1ll * a[l] * a[l] % P;
			val[u].si = 1ll * a[l] * l % P;
			return;
		}
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r);
		val[u] = val[u << 1] + val[u << 1 | 1];
	}

	void add(int u, int l, int r, LazyNode v) {
		--l;
		int si0 = r - l;
		int si1 = minus(getSum1(r), getSum1(l));
		int si2 = minus(getSum2(r), getSum2(l));
		val[u].s2 = (val[u].s2 + 1ll * v.x * v.x % P * si0
		  + 1ll * v.y * v.y % P * si2 + 2ll * val[u].s1 * v.x
		  + 2ll * val[u].si * v.y + 2ll * v.x * v.y % P * si1) % P;
		val[u].si = (val[u].si + 1ll * v.x * si1 + 1ll * v.y * si2) % P;
		val[u].s1 = (val[u].s1 + 1ll * v.x * si0 + 1ll * v.y * si1) % P;
		lz[u] += v;
	}

	void down(int u, int l, int md, int r) {
		add(u << 1, l, md, lz[u]);
		add(u << 1 | 1, md + 1, r, lz[u]);
		lz[u] = {0, 0};
	}

	void modify(int u, int l, int r, int L, int R, LazyNode v) {
		if (L <= l && r <= R) {
			add(u, l, r, v);
			return;
		}
		int md = (l + r) >> 1;
		down(u, l, md, r);
		if (L <= md) {
			modify(u << 1, l, md, L, R, v);
		}
		if (R > md) {
			modify(u << 1 | 1, md + 1, r, L, R, v);
		}
		val[u] = val[u << 1] + val[u << 1 | 1];
	}

	Node query(int u, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return val[u];
		}
		int md = (l + r) >> 1;
		down(u, l, md, r);
		if (R <= md) {
			return query(u << 1, l, md, L, R);
		} else if (L > md) {
			return query(u << 1 | 1, md + 1, r, L, R);
		} else {
			return query(u << 1, l, md, L, R)
			  + query(u << 1 | 1, md + 1, r, L, R);
		}
	}
} T;

int main() {
	read(n), read(q);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		a[i] = (a[i] + P) % P;
	}
	T.build(1, 1, n);
	while (q--) {
		int op, l, r;
		read(op), read(l), read(r);
		if (op == 0) {
			LazyNode v;
			read(v.x), read(v.y);
			v.y = (v.y + P) % P;
			v.x = (v.x + P + 1ll * (P - l) * v.y) % P;
			T.modify(1, 1, n, l, r, v);
		} else {
			Node ans = T.query(1, 1, n, l, r);
			print(ans.s2);
		}
	}
}

/*
5 2
0 0 0 0 0
0 1 5 1 1
1 1 5
*/
