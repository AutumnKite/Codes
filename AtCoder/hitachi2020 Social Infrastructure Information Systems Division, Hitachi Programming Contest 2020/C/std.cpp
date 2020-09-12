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

int n;
std::vector<int> E[N];

int lim[3];
std::vector<int> p[3];
int ans[N];

void dfs(int u, int d, int fa = 0) {
	p[d].push_back(u);
	for (int v : E[u]) {
		if (v != fa) {
			dfs(v, 3 - d, u);
		}
	}
}

int main() {
	read(n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		read(u), read(v);
		E[u].push_back(v), E[v].push_back(u);
	}
	lim[0] = lim[1] = lim[2] = n / 3;
	for (int i = 1; i <= n % 3; ++i) {
		++lim[i];
	}
	dfs(1, 1);
	for (int i = 1; i <= 2; ++i) {
		while ((int)p[i].size() > lim[i]) {
			p[0].push_back(p[i].back());
			p[i].pop_back();
		}
	}
	for (int i = 1; i <= 2; ++i) {
		if ((int)p[i].size() < lim[i]) {
			p[i].swap(p[0]);
			while ((int)p[i].size() > lim[i]) {
				p[0].push_back(p[i].back());
				p[i].pop_back();
			}
			break;
		}
	}
	for (int k = 1; k <= 3; ++k) {
		for (int i = k; i <= n; i += 3) {
			ans[p[k % 3][(i - k) / 3]] = i;
		}
	}
	for (int i = 1; i <= n; ++i) {
		print(ans[i], " \n"[i == n]);
	}
}
