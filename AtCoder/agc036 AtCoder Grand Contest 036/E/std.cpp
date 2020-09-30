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

int n, cnt[3];
char s[N], ch[3];
bool ex[N];

void erase(int i) {
	if (ex[i]) {
		ex[i] = 0, --cnt[s[i] - 'A'];
	}
}

int get() {
	int m = 0;
	for (int i = 1; i <= n; ++i) {
		if (ex[i]) {
			s[++m] = s[i];
			ex[m] = 1;
		}
	}
	return m;
}

int main() {
	n = readStr(s + 1);
	for (int i = 1; i <= n; ++i) {
		++cnt[s[i] - 'A'];
		ex[i] = 1;
	}
	for (int i = 2; i <= n; ++i) {
		if (s[i] == s[i - 1]) {
			erase(i);
		}
	}
	n = get();
	for (int i = 0; i < 3; ++i) {
		ch[i] = i + 'A';
	}
	std::sort(ch, ch + 3, [&](char a, char b) {
		return cnt[a - 'A'] < cnt[b - 'A'];
	});
	memset(cnt, 0, sizeof cnt);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (ch[j] == s[i]) {
				s[i] = j + 'A';
				break;
			}
		}
		++cnt[s[i] - 'A'];
	}
	// printStr(s + 1, n);
	for (int i = 1; i <= n && cnt[2] > cnt[1]; ++i) {
		if (s[i] == 'C' && (i == 1 || i == n || s[i - 1] != s[i + 1])) {
			erase(i);
		}
	}
	for (int i = 2; i < n && cnt[2] > cnt[1]; ++i) {
		if (s[i] == 'C' && s[i - 1] == 'A' && s[i + 1] == 'A') {
			erase(i), erase(i - 1);
		}
	}
	if (cnt[2] > cnt[1]) {
		return 0;
	}
	n = get();
	// printStr(s + 1, n);
	int lst = 0;
	for (int i = 1; i < n && cnt[1] > cnt[0]; ++i) {
		if (((s[i] == 'B' && s[i + 1] == 'C') || (s[i] == 'C' && s[i + 1] == 'B')) && (lst == 0 || i == n - 1 || s[lst] != 'A' || s[i + 2] != 'A')) {
			erase(i), erase(i + 1), ++i;
		} else {
			lst = i;
		}
	}
	n = get();
	// printStr(s + 1, n);
	for (int i = 1; i <= n; ++i) {
		putchar(ch[s[i] - 'A']);
	}
	putchar('\n');
}
