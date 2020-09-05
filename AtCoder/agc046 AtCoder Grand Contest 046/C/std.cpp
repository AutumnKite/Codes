#include <bits/stdc++.h>

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

const int N = 305, P = 998244353;

int n, k, m, f[N][N], s1[N][N], s2[N][N];
char s[N];

void solve() {
	n = readStr(s + 1), read(k);
	std::vector<int> a(1);
	int lst = 0;
	for (int i = 1; i <= n; ++i) {
		if (s[i] == '0') {
			a.push_back(i - lst - 1);
			lst = i;
		}
	}
	a.push_back(n - lst);
	int m = (int)a.size() - 1;
	std::vector<int> sum(m + 1);
	sum[0] = 0;
	for (int i = 1; i <= m; ++i) {
		sum[i] = sum[i - 1] + a[i];
	}
	f[0][0] = 1;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			s1[i][j] = s2[i][j] = f[i][j];
			if (i) {
				s1[i][j] = (s1[i][j] + s1[i - 1][j]) % P;
				if (j) {
					s2[i][j] = (s2[i][j] + s2[i - 1][j - 1]) % P;
				}
			}
		}
	}
	for (int k = 1; k <= m; ++k) {
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= n; ++j) {
				if (i < sum[k]) {
					f[i][j] = 0;
					continue;
				}
				f[i][j] = s1[i][j];
				if (i >= a[k]) {
					f[i][j] = (f[i][j] + P - s1[i - a[k]][j]) % P;
					f[i][j] = (f[i][j] + s2[i - a[k]][j]) % P;
				}
			}
		}
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= n; ++j) {
				s1[i][j] = s2[i][j] = f[i][j];
				if (i) {
					s1[i][j] = (s1[i][j] + s1[i - 1][j]) % P;
					if (j) {
						s2[i][j] = (s2[i][j] + s2[i - 1][j - 1]) % P;
					}
				}
			}
		}
	}
	int ans = 0;
	for (int j = 0; j <= n && j <= k; ++j) {
		ans = (ans + f[sum[m]][j]) % P;
	}
	print(ans);
}

int main() {
	int T = 1;
	// read(T);
	while (T--) {
		solve();
	}
}