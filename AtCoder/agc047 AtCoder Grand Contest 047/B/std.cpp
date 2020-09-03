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

const int N = 200005, M = 1000005;

int n;
char a[M];
int id[N];

int rt, cnt;
int ex[M], fa[M], fw[M], go[M][26];

void init() {
	cnt = rt = 1;
	ex[rt] = 0, fa[rt] = 0;
}

int insert(char *a, int len) {
	int u = rt;
	for (int i = 1; i <= len; ++i) {
		if (!go[u][a[i] - 'a']) {
			go[u][a[i] - 'a'] = ++cnt;
			fa[cnt] = u, fw[cnt] = a[i] - 'a';
		}
		u = go[u][a[i] - 'a'];
	}
	ex[u] = 1;
	return u;
}

int main() {
	read(n);
	init();
	for (int i = 1; i <= n; ++i) {
		int len = readStr(a + 1);
		std::reverse(a + 1, a + len + 1);
		id[i] = insert(a, len);
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		static int ch[26];
		memset(ch, 0, sizeof ch);
		for (int u = id[i]; u; u = fa[u]) {
			for (int k = 0; k < 26; ++k) {
				if (ch[k] && go[u][k] && ex[go[u][k]]) {
					++ans;
				}
			}
			++ch[fw[u]];
		}
	}
	print(ans - n);
}