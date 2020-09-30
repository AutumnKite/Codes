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

const int N = 400005;

int n, L;
int tot, a[N], lv[N], rv[N], pr[N], nx[N], vis[N];
int sl[N], sr[N], ans;

int main() {
	read(n), read(L);
	std::priority_queue<std::pair<int, int>> Q;
	tot = n;
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		Q.push({-a[i], i});
		lv[i] = rv[i] = 1;
		pr[i] = i - 1, nx[i] = i + 1;
		vis[i] = 0;
	}
	nx[n] = 0;
	long long ans = 0;
	while (!Q.empty()) {
		int v = Q.top().second;
		Q.pop();
		if (vis[v]) {
			continue;
		}
		int l = v, r = v, cnt = 1;
		while (pr[l] && a[pr[l]] == a[v]) {
			l = pr[l], ++cnt;
		}
		while (nx[r] && a[nx[r]] == a[v]) {
			r = nx[r], ++cnt;
		}
		int lst = 0;
		for (int i = 1, j = l; i <= cnt; ++i, j = nx[j]) {
			sl[i] = sl[i - 1] + lv[j];
			sr[i] = sr[i - 1] + rv[j];
			if (j <= n) {
				lst = i;
			}
			if (lst && i >= L) {
				ans += 1ll * sl[std::min(i - L + 1, lst)] * rv[j];
			}
			vis[j] = 1;
		}
		if (cnt < L) {
			nx[pr[l]] = pr[nx[r]] = 0;
			continue;
		}
		int pos = tot + 1;
		for (int i = 1; i <= cnt / L; ++i) {
			a[++tot] = a[v] + 1;
			rv[tot] = sr[std::min((i + 1) * L - 1, cnt)] - sr[i * L - 1];
			lv[tot] = sl[cnt % L + (i - 1) * L + 1] - sl[std::max(cnt % L + (i - 2) * L + 1, 0)];
			pr[tot] = tot - 1, nx[tot] = tot + 1;
		}
		nx[pr[l]] = pos, pr[pos] = pr[l];
		pr[nx[r]] = tot, nx[tot] = nx[r];
		Q.push({-a[pos], pos});
	}
	print(ans + n);
}
