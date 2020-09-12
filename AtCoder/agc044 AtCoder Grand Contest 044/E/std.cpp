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

const int N = 200005, INF = 0x3f3f3f3f;

int n;
long long A[N], B[N], C[N];

int top, sta[N];

bool cmp(int i, int j, int k) {
	return (A[i] - A[j]) * (j - k) < (A[j] - A[k]) * (i - j);
}

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(A[i]);
	}
	for (int i = 1; i <= n; ++i) {
		read(B[i]);
	}
	int max_pos = std::max_element(A + 1, A + 1 + n) - A;
	std::rotate(A + 1, A + max_pos, A + 1 + n);
	std::rotate(B + 1, B + max_pos, B + 1 + n);
	A[++n] = A[1], B[n] = B[1];
	C[1] = C[2] = 0;
	for (int i = 2; i < n; ++i) {
		C[i + 1] = 2 * (B[i] + C[i]) - C[i - 1];
	}
	for (int i = 1; i <= n; ++i) {
		A[i] -= C[i];
	}
	top = 1, sta[1] = 1;
	for (int i = 2; i <= n; ++i) {
		while (top > 1 && !cmp(i, sta[top], sta[top - 1])) {
			--top;
		}
		sta[++top] = i;
	}
	long long ans = 0;
	for (int i = 1; i < top; ++i) {
		ans += (A[sta[i + 1]] + A[sta[i]]) * (sta[i + 1] - sta[i] + 1);
		ans -= A[sta[i + 1]] * 2;
	}
	for (int i = 1; i < n; ++i) {
		ans += C[i] * 2;
	}
	printf("%.15lf\n", 1.0 * ans / 2 / (n - 1));
}
