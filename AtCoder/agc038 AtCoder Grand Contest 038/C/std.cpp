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

const int N = 1000005, P = 998244353, I2 = (P + 1) >> 1;

int n, m, c[N];
int cnt, prime[N], vis[N], mu[N];
int inv[N], sum[N];

int main() {
	read(n), m = 0;
	for (int i = 1; i <= n; ++i) {
		int x;
		read(x);
		m = std::max(m, x);
		++c[x];
	}
	inv[1] = 1;
	for (int i = 2; i <= m; ++i) {
		inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	}
	cnt = 0;
	mu[1] = 1;
	for (int i = 2; i <= m; ++i) {
		if (!vis[i]) {
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= cnt && i * prime[j] <= m; ++j) {
			vis[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 1; i <= m; ++i) {
		sum[i] = 0;
		for (int j = i; j <= m; j += i) {
			sum[i] = (sum[i] + 1ll * j * c[j]) % P;
		}
		sum[i] = 1ll * sum[i] * sum[i] % P;
	}
	int ans = 0;
	for (int d = 1; d <= m; ++d) {
		for (int k = 1; k <= m / d; ++k) {
			ans = (ans + 1ll * inv[d] * mu[k] * sum[d * k]) % P;
		}
	}
	for (int i = 1; i <= m; ++i) {
		ans = (ans - 1ll * c[i] * i) % P;
	}
	ans = 1ll * ans * I2 % P;
	print((ans + P) % P);
}
