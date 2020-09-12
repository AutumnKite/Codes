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

int A, X, B, Y, C, G, D;

void exgcd(int a, int b, int &x, int &y) {
	if (!b) {
		x = 1, y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

int inv(int a, int p) {
	int x, y;
	exgcd(a, p, x, y);
	return (x % p + p) % p;
}

int gety(int x) {
	if (x == 0) {
		return C;
	}
	return (C - 1ll * D * x % C) % C;
}

void solve() {
	read(A), read(X), read(B), read(Y), read(C);
	G = std::__gcd(A, B), A /= G, B /= G, C /= std::__gcd(C, G);
	G = std::__gcd(A, C), A /= G, C /= G, Y /= G;
	G = std::__gcd(B, C), B /= G, C /= G, X /= G;
	A %= C, B %= C;
	if (C == 1) {
		print(X + Y);
		return;
	}
	D = 1ll * A * inv(B, C) % C;

	std::vector<int> pos, cnt;
	int W = C, H = D, now = 0, invD = inv(D, C);
	while (W) {
		H = (H - 1) % W + 1;
		int t = W / H;
		pos.push_back(1ll * now * invD % C);
		cnt.push_back(t);
		now += t * H;
		W -= t * H;
	}
	pos.push_back(C);

	long long ans = 0;
	for (int i = 0; i < (int)cnt.size(); ++i) {
		int lx = pos[i], ly = gety(lx);
		int rx = pos[i + 1], ry = gety(rx);
		int dx = (rx - lx) / cnt[i];
		int dy = (ly - ry) / cnt[i];

		long long l = 0, r = X + Y, s = 0;
		while (l <= r) {
			long long md = (l + r) >> 1;
			long long p = X - lx * md, q = Y - ry * md;
			if (p >= 0 && q >= 0 && p / dx + q / dy >= cnt[i] * md) {
				s = md, l = md + 1;
			} else {
				r = md - 1;
			}
		}
		ans = std::max(ans, s);
	}
	print(ans);
}

int main() {
	int T = 1;
	read(T);
	while (T--) {
		solve();
	}
}