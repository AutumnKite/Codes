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

const int N = 1 << 18, M = 100005;

int n, q, V[N], W[N], Log[1 << 9];
long long f[1 << 9][M];
long long sumw[1 << 9], sumv[1 << 9];

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(V[i]), read(W[i]);
	}
	Log[0] = -1;
	for (int i = 1; i <= n && i < 512; ++i) {
		Log[i] = Log[i >> 1] + 1;
		int fa = i >> 1;
		for (int j = 0; j < M; ++j) {
			f[i][j] = f[fa][j];
		}
		for (int j = W[i]; j < M; ++j) {
			f[i][j] = std::max(f[i][j], f[fa][j - W[i]] + V[i]);
		}
	}
	read(q);
	while (q--) {
		int v, L;
		read(v), read(L);
		std::vector<int> p;
		for (; v >= 512; v >>= 1) {
			p.push_back(v);
		}
		sumw[0] = sumv[0] = 0;
		for (int S = 1; S < (1 << p.size()); ++S) {
			sumw[S] = sumw[S & (S - 1)] + W[p[Log[S & -S]]];
			sumv[S] = sumv[S & (S - 1)] + V[p[Log[S & -S]]];
		}
		long long ans = 0;
		for (int S = 0; S < (1 << p.size()); ++S) {
			if (sumw[S] <= L) {
				ans = std::max(ans, sumv[S] + f[v][L - sumw[S]]);
			}
		}
		print(ans);
	}
}