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

const int N = 500005;

int n, type, k;
char s[N];

struct SuffixAutomaton {
	static const int N = 1000005;
	static const int C = 26;

	int cnt, cur;
	int len[N], trans[N][C], link[N];
	int sz[N];
	long long sum[N];

	int newNode(int l) {
		int u = cnt++;
		len[u] = l, link[u] = -1, sz[u] = 0;
		for (int i = 0; i < C; ++i) {
			trans[u][i] = -1;
		}
		return u;
	}

	void init() {
		cnt = 0, cur = newNode(0), sz[cur] = 1;
	}

	void insert(int c) {
		int p = cur;
		cur = newNode(len[p] + 1), sz[cur] = 1;
		while (p != -1 && trans[p][c] == -1) {
			trans[p][c] = cur;
			p = link[p];
		}
		if (p == -1) {
			link[cur] = 0;
			return;
		}
		int q = trans[p][c];
		if (len[p] + 1 == len[q]) {
			link[cur] = q;
			return;
		}
		int t = newNode(len[p] + 1);
		link[t] = link[q];
		for (int i = 0; i < C; ++i) {
			trans[t][i] = trans[q][i];
		}
		while (p != -1 && trans[p][c] == q) {
			trans[p][c] = t;
			p = link[p];
		}
		link[q] = link[cur] = t;
	}

	std::vector<int> sortLen() {
		static int c[N];
		for (int i = 0; i <= len[cur]; ++i) {
			c[i] = 0;
		}
		for (int i = 0; i < cnt; ++i) {
			++c[len[i]];
		}
		for (int i = 1; i <= len[cur]; ++i) {
			c[i] += c[i - 1];
		}
		std::vector<int> id(cnt);
		for (int i = cnt - 1; ~i; --i) {
			id[--c[len[i]]] = i;
		}
		return id;
	}

	void getSum() {
		std::vector<int> id = sortLen();
		std::reverse(id.begin(), id.end());
		if (type) {
			for (int i : id) {
				if (link[i] != -1) {
					sz[link[i]] += sz[i];
				}
			}
		} else {
			for (int i = 0; i < cnt; ++i) {
				sz[i] = 1;
			}
		}
		sz[0] = 0;
		for (int i : id) {
			sum[i] = sz[i];
			for (int j = 0; j < C; ++j) {
				if (trans[i][j] != -1) {
					sum[i] += sum[trans[i][j]];
				}
			}
		}
	}
} A;

void printAns(int u, int k) {
	if (k <= A.sz[u]) {
		return;
	}
	k -= A.sz[u];
	for (int i = 0; i < A.C; ++i) {
		if (A.trans[u][i] != -1) {
			if (k <= A.sum[A.trans[u][i]]) {
				putchar(i + 'a');
				printAns(A.trans[u][i], k);
				return;
			} else {
				k -= A.sum[A.trans[u][i]];
			}
		}
	}
	print_(-1);
}

int main() {
	n = readStr(s), read(type), read(k);
	A.init();
	for (int i = 0; i < n; ++i) A.insert(s[i] - 'a');
	A.getSum();
	printAns(0, k);
	putchar('\n');
}
