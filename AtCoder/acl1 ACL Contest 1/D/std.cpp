#include <bits/stdc++.h>
#include <atcoder/all>

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

const int N = 200005;

int n, k, a[N], ls[N][18], nx[N][18];
long long sls[N][18], snx[N][18];

int main() {
	read(n), read(k);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	ls[0][0] = 0;
	int p = 1;
	for (int i = 1; i <= n; ++i) {
		while (a[i] - a[p] >= k) {
			++p;
		}
		ls[i][0] = p - 1;
		sls[i][0] = i;
	}
	nx[n + 1][0] = n + 1;
	p = n;
	for (int i = n; i; --i) {
		while (a[p] - a[i] >= k) {
			--p;
		}
		nx[i][0] = p + 1;
		snx[i][0] = i - 1;
	}
	for (int j = 1; j < 18; ++j) {
		ls[0][j] = 0, nx[n + 1][j] = n + 1;
		for (int i = 1; i <= n; ++i) {
			ls[i][j] = ls[ls[i][j - 1]][j - 1];
			nx[i][j] = nx[nx[i][j - 1]][j - 1];
			sls[i][j] = sls[i][j - 1] + sls[ls[i][j - 1]][j - 1];
			snx[i][j] = snx[i][j - 1] + snx[nx[i][j - 1]][j - 1];
		}
	}
	int q;
	read(q);
	while (q--) {
		int l, r;
		read(l), read(r);
		long long sum = 0;
		int u = l;
		for (int i = 17; ~i; --i) {
			if (nx[u][i] <= r) {
				sum -= snx[u][i];
				u = nx[u][i];
			}
		}
		sum -= snx[u][0];
		u = r;
		for (int i = 17; ~i; --i) {
			if (ls[u][i] >= l) {
				sum += sls[u][i];
				u = ls[u][i];
			}
		}
		sum += sls[u][0];
		print(sum);
	}
}
