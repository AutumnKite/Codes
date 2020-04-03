#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>

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
		std::vector<int> num;
		if (x < 0) {
			putchar('-');
			x = -x;
		}
		for (; x; x /= 10) {
			num.push_back(x % 10);
		}
		while (!num.empty()) {
			putchar(num.back() ^ '0');
			num.pop_back();
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

int n;
char s[N];

struct SuffixArray {
	static const int N = 1000005; // the length of the string

	int n, m, cnt[N], sa[N], rk[N], id[N];

	void radixSort() {
		for (int i = 0; i < m; ++i) {
			cnt[i] = 0;
		}
		for (int i = 0; i < n; ++i) {
			++cnt[rk[i]];
		}
		for (int i = 1; i < m; ++i) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = n - 1; ~i; --i) {
			sa[--cnt[rk[id[i]]]] = id[i];
		}
	}

	bool cmp(int x, int y, int l) {
		if (id[x] != id[y]) return false;
		x += l, y += l;
		return x < n && y < n && id[x] == id[y];
	}

	template<typename T>
	void initSA(T first, T last) {
		n = last - first, m = 0;
		for (int i = 0; i < n; ++i) {
			rk[i] = *(first + i);
			m = std::max(m, rk[i] + 1);
			id[i] = i;
		}
		radixSort();
		for (int l = 1, p = 0; p < n; m = p, l <<= 1) {
			p = 0;
			for (int i = n - l; i < n; ++i) {
				id[p++] = i;
			}
			for (int i = 0; i < n; ++i) {
				if (sa[i] >= l) {
					id[p++] = sa[i] - l;
				}
			}
			radixSort();
			std::swap(rk, id);
			p = 1, rk[sa[0]] = 0;
			for (int i = 1; i < n; ++i) {
				if (!cmp(sa[i - 1], sa[i], l)) {
					++p;
				}
				rk[sa[i]] = p - 1;
			}
		}
	}
} A;

int height[N];

void getHeight() {
	s[n] = -1;
	height[0] = 0;
	for (int i = 0, k = 0; i < n; ++i) {
		if (!A.rk[i]) {
			continue;
		}
		if (k) {
			--k;
		}
		while (s[i + k] == s[A.sa[A.rk[i] - 1] + k]) {
			++k;
		}
		height[A.rk[i]] = k;
	}
}

int main(){
	int T = 1;
	read(T);
	while (T--) {
		n = readStr(s);
		A.initSA(s, s + n);
		getHeight();
		long long ans = 1ll * n * (n + 1) / 2;
		for (int i = 1; i < n; ++i) {
			ans -= height[i];
		}
		print(ans);
	}
}
