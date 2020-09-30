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

const int N = 200005;

int n, m, a[N], nx[N], pos[N];
long long k;
bool vis[N];

int main() {
	read(n), read(k);
	for (int i = 0; i < n; ++i) {
		read(a[i]), --a[i];
		m = std::max(m, a[i] + 1);
	}
	for (int i = 0; i < m; ++i) {
		pos[i] = n;
	}
	for (int i = n - 1; ~i; --i) {
		nx[i] = pos[a[i]];
		pos[a[i]] = i;
	}
	for (int i = 0; i < n; ++i) {
		if (nx[i] == n) {
			nx[i] = pos[a[i]];
		}
	}
	int p = 0, len = 0;
	do {
		int w = (nx[p] <= p) + (nx[p] == n - 1);
		len += w;
		p = (nx[p] + 1) % n;
	} while (p != 0);
	if (k % len == 0) {
		return 0;
	}
	k %= len;
	while (k > 1) {
		int w = (nx[p] <= p) + (nx[p] == n - 1);
		k -= w;
		p = (nx[p] + 1) % n;
	}
	std::vector<int> s;
	for (int i = p; i < n; ++i) {
		if (vis[a[i]]) {
			while (vis[a[i]]) {
				vis[s.back()] = 0;
				s.pop_back();
			}
		} else {
			s.push_back(a[i]);
			vis[a[i]] = 1;
		}
	}
	for (int v : s) {
		print(v + 1, ' ');
	}
	putchar('\n');
}
