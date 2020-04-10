#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

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

int a[5][5], p[15], vis[5][5];

bool rook(int x1, int y1, int x2, int y2) {
	return x1 == x2 || y1 == y2;
}

bool queen(int x1, int y1, int x2, int y2) {
	return x1 == x2 || y1 == y2 || x1 + y1 == x2 + y2 || x1 - y1 == x2 - y2;
}

template<typename T>
int work(T check) {
	int x = 0, y = 0;
	for (int i = 1; i <= 3; ++i) {
		for (int j = 1; j <= 3; ++j) {
			if (a[i][j] == 1) {
				x = i, y = j;
			}
			vis[i][j] = 0;
		}
	}
	vis[x][y] = 1;
	int res = 0;
	while (1) {
		int nx = 0, ny = 0, mn = 10, type = 2;
		for (int i = 1; i <= 3; ++i) {
			for (int j = 1; j <= 3; ++j) {
				if (!vis[i][j]) {
					int tp = !check(x, y, i, j);
					if (tp < type || (tp == type && a[i][j] < mn)) {
						nx = i, ny = j, mn = a[i][j], type = tp;
					}
				}
			}
		}
		if (type == 2) {
			break;
		}
		res += type, x = nx, y = ny, vis[x][y] = 1;
	}
	return res;
}

int main() {
	freopen("bf.out", "w", stdout);
	for (int i = 1; i <= 9; ++i) {
		p[i] = i;
	}
	while (1) {
		for (int i = 1; i <= 3; ++i) {
			for (int j = 1; j <= 3; ++j) {
				a[i][j] = p[(i - 1) * 3 + j];
			}
		}
		if (work(rook) < work(queen)) {
			for (int i = 1; i <= 9; ++i) {
				print(p[i], ' ');
				if (i % 3 == 0) {
					putchar('\n');
				}
			}
			return 0;
		}
		if (!std::next_permutation(p + 1, p + 1 + 9)) {
			break;
		}
	}
}