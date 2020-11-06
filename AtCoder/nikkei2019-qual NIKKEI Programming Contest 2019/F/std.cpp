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

const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n, m;

struct Jewels {
	int c;
	long long v;
	int k;

	bool operator < (const Jewels &rhs) const {
		long long t1 = v * rhs.k, t2 = rhs.v * k;
		return t1 > t2 || (t1 == t2 && k > rhs.k);
	}
};

int main() {
	read(n), read(m);
	std::vector<std::vector<long long>> a(m);
	for (int i = 0; i < n; ++i) {
		int c, v;
		read(c), read(v);
		a[--c].push_back(v);
	}
	std::vector<Jewels> all;
	for (int i = 0; i < m; ++i) {
		std::sort(a[i].begin(), a[i].end(), std::greater<long long>());
		all.push_back({i, a[i][0] + a[i][1], 2});
		for (int j = 2; j < (int)a[i].size(); ++j) {
			all.push_back({i, a[i][j], 1});
		}
	}
	std::sort(all.begin(), all.end());
	std::vector<long long> ans(n + 1, 0);
	std::vector<int> used(m, 0);
	std::multiset<long long> P, Q, R, S, T;
	for (int i = 0; i < m; ++i) {
		S.insert(a[i][0] + a[i][1]);
		if ((int)a[i].size() > 2) {
			T.insert(a[i][0] + a[i][1] + a[i][2]);
		}
	}
	long long sum = 0;
	int id = 0;
	for (auto p : all) {
		ans[id] = sum;
		if (p.k == 1) {
			Q.erase(Q.find(p.v));
			P.insert(p.v);
			if (used[p.c] == 2) {
				R.erase(R.find(a[p.c][0] + a[p.c][1]));
			}
			id += p.k;
			used[p.c] += p.k;
			sum += p.v;
			continue;
		}
		long long t = -INF;
		if (!Q.empty()) {
			t = std::max(t, *(--Q.end()));
		}
		if (!P.empty() && !S.empty()) {
			t = std::max(t, *(--S.end()) - *P.begin());
		}
		if (!R.empty() && !T.empty()) {
			t = std::max(t, *(--T.end()) - *R.begin());
		}
		if (t == -INF) {
			ans[id + 1] = -1;
		} else {
			ans[id + 1] = sum + t;
		}
		S.erase(S.find(p.v));
		if ((int)a[p.c].size() > 2) {
			T.erase(T.find(p.v + a[p.c][2]));
		}
		R.insert(p.v);
		for (int j = 2; j < (int)a[p.c].size(); ++j) {
			Q.insert(a[p.c][j]);
		}
		id += p.k;
		used[p.c] += p.k;
		sum += p.v;
	}
	ans[id] = sum;
	for (int i = 1; i <= n; ++i) {
		print(ans[i]);
	}
}
