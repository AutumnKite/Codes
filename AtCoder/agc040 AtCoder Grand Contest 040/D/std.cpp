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

int n;

struct Node {
	int a, b, v;

	bool operator < (const Node &rhs) const {
		return v > rhs.v;
	}
} A[N];

long long S, sum[N];

struct Frac {
	long long k, p, q;

	Frac() {
		k = 0, p = 0, q = 1;
	}

	Frac(long long _k, long long _p, long long _q) {
		k = _k, p = _p, q = _q;
	}
};

bool operator < (const Frac &a, const Frac &b) {
	return a.k < b.k || (a.k == b.k && a.p * b.q < b.p * a.q);
}

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(A[i].a), read(A[i].b);
		A[i].v = std::max(A[i].a, A[i].b);
		S += A[i].a;
	}
	std::sort(A + 1, A + 1 + n);
	for (int i = 1; i <= n; ++i) {
		sum[i] = sum[i - 1] + A[i].v;
	}
	Frac ans;
	for (int i = 1; i <= n; ++i) {
		int p = std::lower_bound(sum + 1, sum + i, S - A[i].b) - sum;
		Frac s;
		if (p == i) {
			p = std::lower_bound(sum + i, sum + n + 1, S - A[i].b + A[i].v) - sum;
			if (p == n + 1) {
				continue;
			}
			s = Frac(n - p, std::min(sum[p] + A[i].b - A[i].v - S, 1ll * A[i].b), A[i].b);
		} else {
			s = Frac(n - p - 1, std::min(sum[p] + A[i].b - S, 1ll * A[i].b), A[i].b);
		}
		ans = std::max(ans, s);
	}
	long long p = ans.k * ans.q + ans.p, q = ans.q * n;
	long long g = std::__gcd(p, q);
	print(p / g, ' '), print(q / g);
}
