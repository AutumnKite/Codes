#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

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

const int N = 200005;

int n, f[20][10], g[20][10];

void work(int f[][10]) {
	for (int i = 2; i <= 18; ++i) {
		for (int j = 0; j <= 9; ++j) {
			if (j > 0) f[i][j] += f[i - 1][j - 1];
			f[i][j] += f[i - 1][j];
			if (j < 9) f[i][j] += f[i - 1][j + 1];
		}
	}
}

void solve(int n, int p, int lst) {
	if (!p) {
		return;
	}
	for (int i = lst - 1; i <= lst + 1; ++i) {
		if (i < 0 || i > 9) {
			continue;
		}
		if (n > f[p][i]) {
			n -= f[p][i];
		} else {
			putchar(i ^ '0');
			solve(n, p - 1, i);
			break;
		}
	}
}

int main() {
	read(n);
	for (int i = 0; i <= 9; ++i) {
		f[1][i] = 1;
		if (i > 0) g[1][i] = 1;
	}
	work(f), work(g);
	int p = 1;
	while (1) {
		int s = 0;
		for (int i = 0; i <= 9; ++i) {
			s += g[p][i];
		}
		if (n > s) {
			n -= s;
		} else {
			break;
		}
		++p;
	}
	for (int i = 1; i <= 9; ++i) {
		if (n > f[p][i]) {
			n -= f[p][i];
		} else {
			putchar(i ^ '0');
			solve(n, p - 1, i);
			break;
		}
	}
	putchar('\n');
}
