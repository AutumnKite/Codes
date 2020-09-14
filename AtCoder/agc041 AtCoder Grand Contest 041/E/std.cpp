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

const int N = 50005, M = 100005;

int n, m, T, x[M], y[M], ans[M];
std::bitset<N> S[N], B;
bool A[N];
int to[N], sz[N];

int main() {
	read(n), read(m), read(T);
	for (int i = 1; i <= m; ++i) {
		read(x[i]), read(y[i]);
	}
	if (T == 1) {
		for (int i = 1; i <= n; ++i) {
			S[i][i] = 1;
		}
		for (int i = m; i; --i) {
			S[x[i]] = S[y[i]] = S[x[i]] | S[y[i]];
		}
		B = S[1];
		for (int i = 2; i <= n; ++i) {
			B &= S[i];
		}
		if (B.count() == 0) {
			print(-1);
			return 0;
		}
		int u = B._Find_first();
		A[u] = 1;
		for (int i = m; i; --i) {
			ans[i] = A[y[i]];
			A[x[i]] = A[y[i]] = A[x[i]] | A[y[i]];
		}
		for (int i = 1; i <= m; ++i) {
			putchar(ans[i] ? 'v' : '^');
		}
		putchar('\n');
	} else {
		if (n <= 2 && m) {
			print(-1);
			return 0;
		}
		for (int i = 1; i <= n; ++i) {
			to[i] = i, sz[i] = 1;
		}
		for (int i = m; i; --i) {
			int u = x[i], v = y[i];
			ans[i] = 0;
			if (sz[to[u]] == n - 1) {
				ans[i] ^= 1;
				std::swap(u, v);
			}
			--sz[to[v]];
			to[v] = to[u];
			++sz[to[v]];
		}
		for (int i = 1; i <= m; ++i) {
			putchar(ans[i] ? 'v' : '^');
		}
		putchar('\n');
	}
}
