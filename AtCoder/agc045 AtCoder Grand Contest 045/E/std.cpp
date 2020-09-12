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

const int N = 100005, INF = 0x3f3f3f3f;

int n, m;

struct Edge {
	int u, v, w;
} E[N];

int deg[N];
int fa[N], sz[N];
long long sumE[N];
bool is_cycle[N];

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

int main() {
	read(n), read(m);
	for (int i = 1; i <= n; ++i) {
		fa[i] = i;
		is_cycle[i] = 1;
	}
	for (int i = 1; i <= m; ++i) {
		read(E[i].u), read(E[i].v), read(E[i].w);
		merge(E[i].u, E[i].v);
		++deg[E[i].u];
	}
	for (int i = 1; i <= n; ++i) {
		++sz[find(i)];
		if (deg[i] != 1) {
			is_cycle[find(i)] = 0;
		}
	}
	int add = 0;
	long long sl_sum = 0;
	std::vector<int> sl, slc;
	for (int i = 1; i <= m; ++i) {
		int id = find(E[i].u);
		if (E[i].u != E[i].v) {
			sumE[id] += E[i].w - 1;
			++add;
		} else {
			if (!is_cycle[id]) {
				if (E[i].w > 1) {
					sl.push_back(E[i].w - 1);
					sl_sum += E[i].w - 1;
				}
			} else {
				if (E[i].w > 1) {
					slc.push_back(E[i].w - 1);
				}
			}
		}
	}
	std::sort(sl.begin(), sl.end(), std::greater<int>());
	std::sort(slc.begin(), slc.end(), std::greater<int>());
	long long sum = 0;
	int cyc = 0;
	for (int i = 1; i <= n; ++i) {
		if (find(i) == i) {
			if (is_cycle[i]) {
				cyc += sz[i] > 1;
			} else {
				sum += sumE[i];
			}
		}
	}
	if (!cyc) {
		print(add);
		return 0;
	}
	if (sum + sl_sum == 0) {
		print(-1);
		return 0;
	}
	long long cyc_sum = 0;
	for (int i = 1; i <= n; ++i) {
		if (find(i) == i && is_cycle[i]) {
			cyc_sum += sumE[i];
		}
	}
	std::vector<long long> pre(slc.size() + 1);
	for (int i = 0; i < (int)slc.size(); ++i) {
		pre[i + 1] = pre[i] + slc[i];
	}
	int p = slc.size();
	int ans = INF;
	for (int i = 0; i <= (int)sl.size(); ++i) {
		while (p && sum + cyc_sum + pre[p - 1] >= cyc + p - 1) {
			--p;
		}
		if (sum + cyc_sum + pre[p] >= cyc + p && sum) {
			ans = std::min(ans, add + cyc + i + 2 * p);
		}
		if (i < (int)sl.size()) {
			sum += sl[i];
		}
	}
	if (ans == INF) {
		print(-1);
	} else {
		print(ans);
	}
}
