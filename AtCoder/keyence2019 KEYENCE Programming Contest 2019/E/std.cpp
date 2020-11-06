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
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n, d, a[N];

struct DSU {
	int fa[N], sz[N];

	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			fa[i] = i, sz[i] = 1;
		}
	}

	int find(int x) {
		return fa[x] == x ? x : (fa[x] = find(fa[x]));
	}

	int merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) {
			return false;
		}
		if (sz[x] < sz[y]) {
			std::swap(x, y);
		}
		sz[x] += sz[y], fa[y] = x;
		return true;
	}
} D;

std::pair<long long, int> v[N];

void upd(std::pair<long long, int> &a, std::pair<long long, int> b) {
	a = std::min(a, b);
}

int main() {
	read(n), read(d);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
	}
	D.init(n);
	long long ans = 0;
	while (1) {
		for (int i = 1; i <= n; ++i) {
			v[i] = {INF, 0};
		}
		std::pair<long long, int> mn(INF, 0), cmn(INF, 0);
		for (int i = 1; i <= n; ++i) {
			std::pair<long long, int> tmp;
			if (D.find(i) != D.find(mn.second)) {
				tmp = mn;
			} else {
				tmp = cmn;
			}
			tmp.first += 1ll * d * i + a[i];
			upd(v[D.find(i)], tmp);
			tmp.first = -1ll * d * i + a[i];
			tmp.second = i;
			if (tmp.first < mn.first) {
				if (D.find(mn.second) != D.find(i)) {
					cmn = mn;
				}
				mn = tmp;
			} else if (tmp.first < cmn.first && D.find(mn.second) != D.find(i)) {
				cmn = tmp;
			}
		}
		mn = {INF, 0}, cmn = {INF, 0};
		for (int i = n; i; --i) {
			std::pair<long long, int> tmp;
			if (D.find(i) != D.find(mn.second)) {
				tmp = mn;
			} else {
				tmp = cmn;
			}
			tmp.first += -1ll * d * i + a[i];
			upd(v[D.find(i)], tmp);
			tmp.first = 1ll * d * i + a[i];
			tmp.second = i;
			if (tmp.first < mn.first) {
				if (D.find(mn.second) != D.find(i)) {
					cmn = mn;
				}
				mn = tmp;
			} else if (tmp.first < cmn.first && D.find(mn.second) != D.find(i)) {
				cmn = tmp;
			}
		}
		bool flag = 0;
		for (int i = 1; i <= n; ++i) {
			if (D.find(i) == i && v[i].second && D.merge(i, v[i].second)) {
				ans += v[i].first;
				flag = 1;
			}
		}
		if (!flag) {
			break;
		}
	}
	print(ans);
}
