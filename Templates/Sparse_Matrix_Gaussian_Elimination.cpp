#include <cstdio>
#include <cctype>
#include <cstring>
#include <ctime>
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

namespace randNumber {
	unsigned long long seed = 0x3C9FC1DA24BB75DFull;

	inline void srnd(unsigned long long _sd) {
		seed ^ _sd ? seed ^= _sd : 0;
	}

	inline unsigned long long rnd() {
		seed ^= seed << 13;
		seed ^= seed >> 7;
		seed ^= seed << 17;
		return seed + 0x764FF49E4F6C521Dull;
	}
}
using namespace randNumber;

const int N = 2505, P = 998244353;

int n;

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
	std::vector<int> lst(1), cur(1);
	lst[0] = cur[0] = 1;
	int lp = 0, lt = 0;
	for (int i = 0; i < (int)x.size(); ++i) {
		int t = 0;
		for (int j = 0; j < (int)cur.size(); ++j) {
			t = (t + 1ll * x[i - j] * cur[j]) % P;
		}
		if (!t) {
			continue;
		}
		if ((int)cur.size() == 1) {
			cur.resize(i + 2), lp = i, lt = t;
			continue;
		}
		int tmp = 1ll * (P - t) * qpow(lt, P - 2) % P;
		std::vector<int> c(i - lp, 0);
		for (int v : lst) {
			c.push_back(1ll * v * tmp % P);
		}
		if (c.size() < cur.size()) {
			c.resize(cur.size());
		} else {
			lst = cur, lp = i, lt = t;
		}
		for (int j = 0; j < (int)cur.size(); ++j) {
			c[j] = (c[j] + cur[j]) % P;
		}
		cur = c;
	}
	return cur;
}

int main() {
	read(n);
	std::vector<std::vector<int>> pw(2 * n, std::vector<int>(n, 0));
	std::vector<std::pair<std::pair<int, int>, int>> A;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int x;
			read(x);
			if (x) {
				A.push_back({{i, j}, x});
			}
		}
		read(pw[0][i]);
	}
	for (int k = 1; k < 2 * n; ++k) {
		for (auto p : A) {
			int i = p.first.first, j = p.first.second, w = p.second;
			pw[k][i] = (pw[k][i] + 1ll * w * pw[k - 1][j]) % P;
		}
	}
	srnd(time(0));
	std::vector<int> u(n);
	for (int i = 0; i < n; ++i) {
		u[i] = rnd() % P;
	}
	std::vector<int> r(2 * n, 0);
	for (int k = 0; k < 2 * n; ++k) {
		for (int i = 0; i < n; ++i) {
			r[k] = (r[k] + 1ll * u[i] * pw[k][i]) % P;
		}
	}
	r = BM(r);
	int m = (int)r.size() - 2;
	std::vector<int> ans(n);
	for (int i = 0; i <= m; ++i) {
		for (int j = 0; j < n; ++j) {
			ans[j] = (ans[j] + 1ll * pw[m - i][j] * r[i]) % P;
		}
	}
	int t = qpow(r.back(), P - 2);
	for (int i = 0; i < n; ++i) {
		ans[i] = 1ll * ans[i] * (P - t) % P;
		print(ans[i], ' ');
	}
}
