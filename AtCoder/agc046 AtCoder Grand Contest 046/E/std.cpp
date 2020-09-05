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

const int N = 105;

int n, a[N], s;
int m, ans[1005];
int b[N];
int p[N], q[N], t[N];

bool work(int k) {
	for (int i = 1; i <= n; ++i) {
		b[i] = a[i];
	}
	for (int i = 1; i <= k; ++i) {
		--b[p[i]];
	}
	int mn = *std::min_element(b + 1, b + 1 + n);
	int mx = *std::max_element(b + 1, b + 1 + n);
	if (2 * mn + 1 < mx) {
		return false;
	}
	if (2 * mn >= mx) {
		for (int i = 1; i <= k; ++i) {
			q[i] = p[i];
		}
		std::sort(q + 1, q + 1 + k);
		return true;
	}
	std::vector<int> f1, f2;
	for (int i = 1; i <= k; ++i) {
		if (b[p[i]] == mn || b[p[i]] == mx) {
			f1.push_back(p[i]);
		} else {
			f2.push_back(p[i]);
		}
	}
	std::sort(f1.begin(), f1.end(), [&](int i, int j) {
		int x = b[i] == mn, y = b[j] == mn;
		return x < y || (x == y && i < j);
	});
	std::sort(f2.begin(), f2.end());
	std::merge(f1.begin(), f1.end(), f2.begin(), f2.end(), q + 1);
	int pos = n + 1;
	for (int i = k + 1; i <= n; ++i) {
		if (b[p[i]] == mn) {
			pos = i;
			break;
		}
	}
	for (int i = pos; i <= n; ++i) {
		if (b[p[i]] == mx) {
			return false;
		}
	}
	if (pos <= n && !f1.empty() && b[f1[0]] == mx) {
		return false;
	}
	return true;
}

bool cmp(int *a, int *b) {
	for (int i = 1; i <= n; ++i) {
		if (a[i] != b[i]) {
			return a[i] < b[i];
		}
	}
	return false;
}

int main() {
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		s += a[i];
	}
	for (int i = 1; i <= n; ++i) {
		p[i] = i;
	}
	int mx = *std::max_element(a + 1, a + 1 + n);
	int mn = *std::min_element(a + 1, a + 1 + n);
	if (mx > 2 * mn) {
		print(-1);
		return 0;
	}
	m = 0;
	for (int i = 1; i <= n; ++i) {
		p[i] = i;
	}
	work(n);
	for (int i = 1; i <= n; ++i) {
		ans[++m] = p[i] = q[i];
		--a[q[i]];
	}
	while (m < s) {
		for (int i = 1; i <= n; ++i) {
			t[i] = 0;
		}
		t[1] = n + 1;
		int k = 0;
		for (int i = 1; i <= n; ++i) {
			if (work(i) && cmp(q, t)) {
				k = i;
				for (int j = 1; j <= i; ++j) {
					t[j] = q[j];
				}
			}
		}
		for (int i = 1; i <= n - k; ++i) {
			p[i] = p[i + k];
		}
		for (int i = 1; i <= k; ++i) {
			p[n - k + i] = t[i];
			ans[++m] = t[i];
			--a[t[i]];
		}
	}
	for (int i = 1; i <= m; ++i) {
		print(ans[i], " \n"[i == m]);
	}
}