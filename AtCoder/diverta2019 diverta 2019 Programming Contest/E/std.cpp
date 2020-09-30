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

const int N = 500005, P = 1000000007;

int n, a[N], f[N];
int sum[N];
std::vector<int> p[1 << 20];

int solve(int x) {
	if (a[n] && a[n] != x) {
		return 0;
	}
	if (x == 0) {
		int ans = 1;
		for (int i = 1; i < (int)p[x].size(); ++i) {
			ans = 2ll * ans % P;
		}
		return ans;
	}
	int s = 0, si = 0;
	for (int i = 0; i < (int)p[x].size(); ++i) {
		f[i] = (1ll * s * sum[p[x][i]] + P - si + 1) % P;
		s = (s + f[i]) % P;
		si = (si + 1ll * f[i] * sum[p[x][i]]) % P;
	}
	return a[n] ? f[(int)p[x].size() - 1] : s;
}

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		a[i] ^= a[i - 1];
		sum[i] = sum[i - 1] + (a[i] == 0);
		p[a[i]].push_back(i);
	}
	int ans = 0;
	for (int i = 0; i < (1 << 20); ++i) {
		ans = (ans + solve(i)) % P;
	}
	print(ans);
}
