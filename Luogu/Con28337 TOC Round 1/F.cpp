#pragma GCC optimize("Ofast")
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

const int N = 50005, K = 11, P = 998244353;

int n, q, a[N];

typedef std::vector<int> poly;

poly operator * (const poly &A, const poly &B) {
	poly res;
	res.resize(K, 0);
	for (int i = 0; i < K; ++i) {
		for (int j = 0; j < K - i; ++j) {
			res[i + j] = (res[i + j] + 1ll * A[i] * B[j]) % P;
		}
	}
	return res;
}

struct SegmentTree {
	poly val[N << 2];
	int lz[N << 2];

	void build(int u, int l, int r) {
		lz[u] = 1;
		if (l == r) {
			val[u].resize(K, 0);
			val[u][0] = 1, val[u][1] = a[l];
			return;
		}
		int md = (l + r) >> 1;
		build(u << 1, l, md), build(u << 1 | 1, md + 1, r);
		val[u] = val[u << 1] * val[u << 1 | 1];
	}

	void mul(int u, int v) {
		int s = 1;
		for (int i = 0; i < K; ++i) {
			val[u][i] = 1ll * val[u][i] * s % P;
			s = 1ll * s * v % P;
		}
		lz[u] = 1ll * lz[u] * v % P;
	}

	void down(int u) {
		if (lz[u] != 1) {
			mul(u << 1, lz[u]);
			mul(u << 1 | 1, lz[u]);
			lz[u] = 1;
		}
	}

	void modify(int u, int l, int r, int L, int R, int v) {
		if (L <= l && r <= R) {
			mul(u, v);
			return;
		}
		int md = (l + r) >> 1;
		down(u);
		if (L <= md) {
			modify(u << 1, l, md, L, R, v);
		}
		if (R > md) {
			modify(u << 1 | 1, md + 1, r, L, R, v);
		}
		val[u] = val[u << 1] * val[u << 1 | 1];
	}

	poly query(int u, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return val[u];
		}
		int md = (l + r) >> 1;
		down(u);
		if (R <= md) {
			return query(u << 1, l, md, L, R);
		} else if (L > md) {
			return query(u << 1 | 1, md + 1, r, L, R);
		} else {
			return query(u << 1, l, md, L, R) * query(u << 1 | 1, md + 1, r, L, R);
		}
	}
}T;

int main() {
	read(n), read(q);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		a[i] %= P;
	}
	if (n >= 1) {
		T.build(1, 1, n);
	}
	while (q--) {
		int op, l, r, k;
		read(op), read(l), read(r), read(k);
		if (op == 1) {
			k %= P;
			T.modify(1, 1, n, l, r, k);
		} else {
			poly res = T.query(1, 1, n, l, r);
			print(res[k]);
		}
	}
}
