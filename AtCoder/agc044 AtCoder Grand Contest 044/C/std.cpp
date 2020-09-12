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

const int N = 1000005;

int n, q;
char op[N];

int pw[13];

int ans[N];

struct Trie {
	int rt, cnt, son[N][3], id[N];
	bool tag[N];

	void build(int &u, int d, int v) {
		u = ++cnt, tag[u] = 0;
		if (d == n) {
			id[u] = v;
			return;
		}
		for (int i = 0; i < 3; ++i) {
			build(son[u][i], d + 1, v + i * pw[d]);
		}
	}

	void rev(int u) {
		std::swap(son[u][1], son[u][2]);
		tag[u] ^= 1;
	}

	void down(int u) {
		if (tag[u]) {
			rev(son[u][0]), rev(son[u][1]), rev(son[u][2]);
			tag[u] = 0;
		}
	}

	void add(int u) {
		if (!son[u][0]) {
			return;
		}
		down(u);
		int t = son[u][2];
		son[u][2] = son[u][1];
		son[u][1] = son[u][0];
		son[u][0] = t;
		add(son[u][0]);
	}

	void getans(int u, int d, int v) {
		if (d == n) {
			ans[id[u]] = v;
			return;
		}
		down(u);
		for (int i = 0; i < 3; ++i) {
			getans(son[u][i], d + 1, v + i * pw[d]);
		}
	}
} T;

int main() {
	read(n);
	q = readStr(op + 1);
	pw[0] = 1;
	for (int i = 1; i <= n; ++i) {
		pw[i] = pw[i - 1] * 3;
	}
	T.build(T.rt, 0, 0);
	for (int i = 1; i <= q; ++i) {
		if (op[i] == 'S') {
			T.rev(T.rt);
		} else {
			T.add(T.rt);
		}
	}
	T.getans(T.rt, 0, 0);
	for (int i = 0; i < pw[n]; ++i) {
		print(ans[i], ' ');
	}
	putchar('\n');
}
