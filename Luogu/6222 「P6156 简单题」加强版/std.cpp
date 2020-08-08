#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>

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

const int N = 20000005, PN = 2000005;

int T, n, k;
int cnt, prime[PN];
unsigned f[N], id[N];
std::bitset<N> vis;

unsigned qpow(unsigned a, int b) {
	unsigned s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s *= a;
		}
		a *= a;
	}
	return s;
}

void init(int n) {
	id[1] = 1, f[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			prime[++cnt] = i;
			id[i] = qpow(i, k);
			f[i] = i * id[i] - id[i];
		}
		for (int j = 1; j <= cnt && 1ll * i * prime[j] <= n; ++j) {
			int t = i * prime[j];
			vis[t] = 1;
			id[t] = id[i] * id[prime[j]];
			if (i % prime[j] == 0) {
				if ((i / prime[j]) % prime[j] == 0) {
					f[t] = 0;
				} else {
					f[t] = -f[i / prime[j]] * prime[j] * id[prime[j]] * id[prime[j]];
				}
				break;
			}
			f[t] = f[i] * f[prime[j]];
		}
	}
	f[0] = id[0] = 0;
	for (int i = 1; i <= n; ++i) {
		f[i] += f[i - 1];
		id[i] += id[i - 1];
	}
	for (int i = 1; i <= n; ++i) {
		id[i] += id[i - 1];
	}
}

unsigned calc(int n) {
	return id[2 * n] - 2 * id[n];
}

unsigned solve(int n) {
	unsigned ans = 0;
	for (int i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ans += (f[j] - f[i - 1]) * calc(n / i);
	}
	return ans;
}

int main() {
	read(T), read(n), read(k);
	init(n << 1);
	while (T--) {
		int n;
		read(n);
		print(solve(n));
	}
}

