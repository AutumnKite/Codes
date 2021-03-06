#include <bits/stdc++.h>

#ifndef AT_HOME
#define getchar myGetchar
#define putchar myPutchar
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

const int N = 2000000, LG = 21;

int Q;

struct Oper {
	int op, t, x, y;
} q[N];

int m;
int v[N];

struct BIT {
	int ca[N + 1], cb[N + 1];
	int sa, sb;

	void add_a(int x, int v) {
		++x;
		sa += v;
		for (; x <= m; x += x & -x) {
			ca[x] += v;
		}
	}

	void add_b(int x, int v) {
		++x;
		sb += v;
		for (; x <= m; x += x & -x) {
			cb[x] += v;
		}
	}

	int query_a(int x) {
		int s = 0;
		for (; x; x ^= x & -x) {
			s += ca[x];
		}
		return s;
	}

	int query_b(int x) {
		int s = 0;
		for (; x; x ^= x & -x) {
			s += cb[x];
		}
		return s;
	}

	int find(int v) {
		int x = 0;
		int sum = 0;
		for (int i = LG - 1; i >= 0; --i) {
			if (x + (1 << i) <= m && sum + ca[x + (1 << i)] + cb[x + (1 << i)] <= sb + v) {
				x += 1 << i;
				sum += ca[x] + cb[x];
			}
		}
		return x;
	}

	int find_b(int v) {
		int x = 0;
		int sum = 0;
		for (int i = LG - 1; i >= 0; --i) {
			if (x + (1 << i) <= m && sum + cb[x + (1 << i)] <= v) {
				x += 1 << i;
				sum += cb[x];
			}
		}
		return x;
	}
};

BIT T;

int main() {
	read(Q);
	for (int i = 0; i < Q; ++i) {
		read(q[i].op);
		if (q[i].op == 1) {
			read(q[i].t), read(q[i].x), read(q[i].y);
			if (!q[i].t) {
				--q[i].x;
			}
			v[m++] = q[i].x;
		} else {
			read(q[i].t);
			--q[i].t;
		}
	}
	std::sort(v, v + m);
	m = std::unique(v, v + m) - v;
	
	for (int i = 0; i < Q; ++i) {
		if (q[i].op == 1) {
			q[i].x = std::lower_bound(v, v + m, q[i].x) - v;
			if (q[i].t == 0) {
				T.add_a(q[i].x, q[i].y);
			} else {
				T.add_b(q[i].x, q[i].y);
			}
		} else {
			int j = q[i].t;
			if (q[j].t == 0) {
				T.add_a(q[j].x, -q[j].y);
			} else {
				T.add_b(q[j].x, -q[j].y);
			}
		}
		if (!T.sa || !T.sb) {
			printStr("Peace");
			continue;
		}
		int x1 = T.find(0), x2 = x1 + 1;
		int v1 = T.query_a(x1), v2 = T.sb - T.query_b(x2);
		if (std::max(v1, v2) == 0) {
			printStr("Peace");
			continue;
		}
		if (v1 > v2) {
			print(v[x1], ' '), print(v1 * 2);
		} else {
			x2 = T.find_b(T.sb - v2);
			print(v[x2], ' '), print(v2 * 2);
		}
	}
}
