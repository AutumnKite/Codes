#pragma GCC optimize("O3")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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

const int N = 10005, P = 998244353;

int n, m;

void inc(int &a, int b) {
	(a += b) >= P ? a -= P : 0;
}

int qpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = 1ll * s * a % P;
		}
		a = 1ll * a * a % P;
	}
	return s;
}

std::vector<int> BM(const std::vector<int> &x) {
	std::vector<int> cur(1), lst(1);
	cur[0] = lst[0] = 1;
	int lp = 0, lt = 0;
	for (int i = 0; i < (int)x.size(); ++i) {
		int t = 0;
		for (int j = 0; j < (int)cur.size(); ++j) {
			t = (t + 1ll * x[i - j] * cur[j]) % P;
		}
		if (t == 0) {
			continue;
		}
		if ((int)cur.size() == 1) {
			cur.resize(i + 2);
			lp = i, lt = t;
			continue;
		}
		int tmp = 1ll * (P - t) * qpow(lt, P - 2) % P;
		std::vector<int> c(i - lp);
		for (int v : lst) {
			c.push_back(1ll * tmp * v % P);
		}
		if (c.size() < cur.size()) {
			c.resize(cur.size());
		} else {
			lst = cur, lp = i, lt = t;
		}
		for (int j = 0; j < (int)cur.size(); ++j) {
			inc(c[j], cur[j]);
		}
		cur = c;
	}
	return cur;
}

std::vector<int> mul(const std::vector<int> &a, const std::vector<int> &b, 
  const std::vector<int> &p) {
	int m = (int)p.size() - 1;
	std::vector<int> res(2 * m - 1);
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			res[i + j] = (res[i + j] + 1ll * a[i] * b[j]) % P;
		}
	}
	for (int i = 2 * m - 2; i >= m; --i) {
		if (res[i]) {
			for (int j = m; ~j; --j) {
				res[i - j] = (res[i - j] + 1ll * p[j] * res[i]) % P;
			}
		}
	}
	res.resize(m);
	return res;
}

std::vector<int> recursion(const std::vector<int> &p, int b) {
	std::vector<int> a = {0, 1}, s = {1};
	int m = (int)p.size() - 1;
	a.resize(m), s.resize(m);
	for (; b; b >>= 1) {
		if (b & 1) {
			s = mul(s, a, p);
		}
		a = mul(a, a, p);
	}
	return s;
}

int main() {
	read(n), read(m);
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		read(a[i]);
	}
	std::vector<int> f = BM(a);
	for (int i = 0; i < (int)f.size(); ++i) {
		f[i] = (P - f[i]) % P;
	}
	for (int i = 1; i < (int)f.size(); ++i) {
		print(f[i], ' ');
	}
	putchar('\n');
	std::vector<int> g = recursion(f, m);
	int ans = 0;
	for (int i = 0; i < (int)g.size(); ++i) {
		ans = (ans + 1ll * a[i] * g[i]) % P;
	}
	print(ans);
}