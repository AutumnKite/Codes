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

const int N = 100005;

int n, a[N], d[N], ans[N];

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		++d[a[i]];
	}
	if (n <= 2) {
		print(-1);
		return 0;
	}
	std::set<int> S;
	std::set<std::pair<int, int>> SD;
	for (int i = 1; i <= n; ++i) {
		S.insert(i);
		SD.insert({d[i], i});
	}
	int u = 1;
	for (int i = 1; i <= n - 3; ++i) {
		if ((--SD.end())->first == n - i) {
			u = (--SD.end())->second;
		}
		ans[i] = u;
		S.erase(u), SD.erase({d[u], u});
		if (S.count(a[u])) {
			SD.erase({d[a[u]], a[u]});
			--d[a[u]];
			SD.insert({d[a[u]], a[u]});
		} else {
			--d[a[u]];
		}
		if (*S.begin() == a[u]) {
			u = *(++S.begin());
		} else {
			u = *S.begin();
		}
	}
	int k = n - 3;
	for (int v : S) {
		ans[++k] = v;
	}
	while (1) {
		bool flag = 1;
		for (int i = std::max(n - 3, 1); i < n; ++i) {
			if (a[ans[i]] == ans[i + 1]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			for (int i = 1; i <= n; ++i) {
				print(ans[i], " \n"[i == n]);
			}
			return 0;
		}
		if (!std::next_permutation(ans + n - 2, ans + n + 1)) {
			break;
		}
	}
	print(-1);
}
