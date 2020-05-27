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

typedef std::vector<std::vector<int>> matrix;

const int N = 55, P = 1000000007;

int n, ex_len;
char ex[10005];

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

std::vector<int> recursion(const std::vector<int> &p) {
	std::vector<int> a = {0, 1}, s = {1};
	int m = (int)p.size() - 1;
	a.resize(m), s.resize(m);
	for (int b = 0; b < ex_len; ++b) {
		if (ex[b] == '1') {
			s = mul(s, a, p);
		}
		a = mul(a, a, p);
	}
	return s;
}

matrix operator * (const matrix &a, const matrix &b) {
	matrix res(n, std::vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < n; ++k) {
			for (int j = 0; j < n; ++j) {
				res[i][j] = (res[i][j] + 1ll * a[i][k] * b[k][j]) % P;
			}
		}
	}
	return res;
}

int main() {
	srnd(time(0));
	ex_len = readStr(ex), read(n);
	std::reverse(ex, ex + ex_len);
	matrix A(n, std::vector<int>(n, 0));
	matrix pw(2 * n, std::vector<int>(n, 0));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			read(A[i][j]);
		}
	}
	for (int i = 0; i < n; ++i) {
		pw[0][i] = rnd() % P;
	}
	for (int k = 1; k < 2 * n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				pw[k][i] = (pw[k][i] + 1ll * A[i][j] * pw[k - 1][j]) % P;
			}
		}
	}
	std::vector<int> u(n);
	for (int i = 0; i < n; ++i) {
		u[i] = rnd() % P;
	}
	std::vector<int> f(2 * n, 0);
	for (int k = 0; k < 2 * n; ++k) {
		for (int i = 0; i < n; ++i) {
			f[k] = (f[k] + 1ll * u[i] * pw[k][i]) % P;
		}
	}
	f = BM(f);
	for (int i = 0; i < (int)f.size(); ++i) {
		f[i] = (P - f[i]) % P;
	}
	std::vector<int> g = recursion(f);
	matrix M(n, std::vector<int>(n, 0)), ans(M);
	for (int i = 0; i < n; ++i) {
		M[i][i] = 1;
	}
	for (int k = 0; k < (int)f.size(); ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				ans[i][j] = (ans[i][j] + 1ll * M[i][j] * g[k]) % P;
			}
		}
		M = M * A;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			print(ans[i][j], ' ');
		}
		putchar('\n');
	}
}
