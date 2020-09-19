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

const int N = 45;

int n;
char tmp[N];
int a[N][N];

long long f[N][N][N][N], g[N][N][N][N];

long long DPf(int l, int r, int L, int R);
long long DPg(int l, int r, int L, int R);

long long DPf(int l, int r, int L, int R) {
	if (l > r || L > R) {
		return l > r && L > R;
	}
	if (~f[l][r][L][R]) {
		return f[l][r][L][R];
	}
	long long ans = DPg(l, r, L, R);
	for (int i = l; i < r; ++i) {
		for (int j = L + 1; j <= R; ++j) {
			ans += DPf(l, i, j, R) * DPg(i + 1, r, L, j - 1);
		}
	}
	return f[l][r][L][R] = ans;
}

long long DPg(int l, int r, int L, int R) {
	if (l > r || L > R) {
		return 0;
	}
	if (~g[l][r][L][R]) {
		return g[l][r][L][R];
	}
	long long ans = 0;
	for (int i = l; i <= r; ++i) {
		for (int j = L; j <= R; ++j) {
			if (a[i][j]) {
				ans += DPf(l, i - 1, i + 1, r) * DPf(L, j - 1, j + 1, R);
			}
		}
	}
	return g[l][r][L][R] = ans;
}

int main() {
	read(n), n *= 2;
	for (int i = 1; i <= n; ++i) {
		readStr(tmp + 1);
		for (int j = 1; j <= n; ++j) {
			a[i][j] = tmp[j] ^ '0';
		}
	}
	memset(f, -1, sizeof f);
	memset(g, -1, sizeof g);
	long long ans = 0;
	for (int i = 2; i <= n; ++i) {
		if (a[1][i]) {
			ans += DPf(2, i - 1, i + 1, n);
		}
	}
	print(ans);
}
