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

const int N = 55;

int n, m, k, A, O, a[N];
long long C[N][N];

bool subset(int A, int B) {
	return (A & B) == A;
}

int main() {
	read(n), read(k), read(A), read(O);
	if (!subset(A, O)) {
		print(0);
		return 0;
	}
	m = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		read(x);
		if (subset(A, x) && subset(x, O)) {
			a[m++] = x;
		}
	}
	n = m;
	for (int i = 0; i <= n; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
		}
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 1; j <= k; ++j) {
			C[i][j] += C[i][j - 1];
		}
	}
	long long ans = 0;
	for (int p = 0; p < (1 << 18); ++p) {
		bool flag = 1;
		for (int i = 0; i < 18; ++i) {
			if ((p >> i & 1) && (A >> i & 1) == (O >> i & 1)) {
				flag = 0;
				break;
			}
		}
		if (!flag) {
			continue;
		}
		std::map<int, int> mp;
		for (int i = 0; i < n; ++i) {
			++mp[a[i] & p];
		}
		long long sum = 0;
		for (auto v : mp) {
			sum += C[v.second][k] - 1;
		}
		for (int i = 0; i < 18; ++i) {
			if (p >> i & 1) {
				sum = -sum;
			}
		}
		ans += sum;
	}
	print(ans);
}