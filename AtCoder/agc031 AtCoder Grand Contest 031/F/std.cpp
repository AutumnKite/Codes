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

const int N = 50005, M = 50005;

int n, m, Q, P, g, z;

struct Edge {
	int u, v, w;
} E[M];

int myabs(int a) {
	return a > 0 ? a : -a;
}

int fa[N * 6];

int find(int x) {
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

bool merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) {
		return false;
	}
	fa[y] = x;
	return true;
}

bool pq[1000005][2][3];

int main() {
	read(n), read(m), read(Q), read(P);
	g = P;
	for (int i = 1; i <= m; ++i) {
		read(E[i].u), read(E[i].v), read(E[i].w);
		g = std::__gcd(g, myabs(E[i].w - E[1].w));
	}
	P = std::__gcd(P, 3 * g);
	z = E[1].w % g;
	for (int i = 1; i <= m; ++i) {
		E[i].w = (E[i].w - z) / g;
		E[i].w %= 3;
	}
	for (int i = 1; i <= n * 6; ++i) {
		fa[i] = i;
	}
	for (int i = 1; i <= m; ++i) {
		for (int pu = 0; pu < 2; ++pu) {
			for (int qu = 0; qu < 3; ++qu) {
				int pv = pu ^ 1, qv = (2 * qu + E[i].w) % 3;
				int tu = pu * 3 + qu, tv = pv * 3 + qv;
				merge(E[i].u * 6 - tu, E[i].v * 6 - tv);
				merge(E[i].v * 6 - tu, E[i].u * 6 - tv);
			}
		}
	}
	int pw = z;
	for (int i = 0; i < P; ++i) {
		for (int j = 0; j < 3; ++j) {
			pq[(pw + j * g) % P][i & 1][j] = 1;
		}
		pw = 1ll * pw * 2 % P;
	}
	while (Q--) {
		int u, v, r;
		read(u), read(v), read(r);
		bool ans = 0;
		for (int p = 0; p < 2; ++p) {
			for (int q = 0; q < 3; ++q) {
				if (pq[(r + z) % P][p][q] && find(v * 6) == find(u * 6 - (p * 3 + q))) {
					ans = 1;
				}
			}
		}
		printStr(ans ? "YES" : "NO");
	}
}
