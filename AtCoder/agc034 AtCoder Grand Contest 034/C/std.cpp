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

const int N = 100005;

int n, m;
long long goal;

struct Node {
	int b, l, r;
	long long v;

	bool operator < (const Node &rhs) const {
		return v > rhs.v;
	}
} a[N];

bool check(long long md) {
	int c = md / m, t = md % m;
	long long sum = 0;
	for (int i = 1; i <= c; ++i) {
		sum += a[i].v;
	}
	for (int i = c + 1; i <= n; ++i) {
		int t1 = std::min(t, a[i].b);
		long long now = sum + 1ll * a[i].l * t1 + 1ll * a[i].r * (t - t1);
		if (now >= goal) {
			return true;
		}
	}
	if (c < n) {
		sum += a[c + 1].v;
		for (int i = 1; i <= c; ++i) {
			int t1 = std::min(t, a[i].b);
			long long now = sum - a[i].v + 1ll * a[i].l * t1 + 1ll * a[i].r * (t - t1);
			if (now >= goal) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	read(n), read(m);
	for (int i = 1; i <= n; ++i) {
		read(a[i].b), read(a[i].l), read(a[i].r);
		a[i].v = 1ll * a[i].b * a[i].l + 1ll * (m - a[i].b) * a[i].r;
		goal += 1ll * a[i].b * a[i].l;
	}
	std::sort(a + 1, a + 1 + n);
	long long L = 0, R = 1ll * n * m, ans = R;
	while (L <= R) {
		long long md = (L + R) >> 1;
		if (check(md)) {
			R = md - 1;
			ans = md;
		} else {
			L = md + 1;
		}
	}
	print(ans);
}
