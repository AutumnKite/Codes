#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>

#define debug(...) fprintf(stderr, __VA_ARGS__)

#define getchar() IO::myGetchar()
#define putchar(x) IO::myPutchar(x)

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

struct SuffixAutomaton {
	static const int N = 2000005; // twice the length of the string
	static const int C = 26; // the size of the character set

	int cnt, cur;
	int len[N], trans[N][C], link[N], sz[N];
	std::vector<int> E[N];

	int newNode(int Len) {
		int u = cnt++;
		len[u] = Len, link[u] = -1, sz[u] = 0, E[u].clear();
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
		cur = newNode(len[cur] + 1), sz[cur] = 1;
		while (p != -1 && trans[p][c] == -1) {
			trans[p][c] = cur;
			p = link[p];
		}
		if (p == -1) {
			link[cur] = 0;
			return;
		}
		int q = trans[p][c];
		if (len[q] == len[p] + 1) {
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

	void getSize(int u) {
		for (int v : E[u]) {
			getSize(v);
			sz[u] += sz[v];
		}
	}

	void buildTree() {
		for (int i = 1; i < cnt; ++i) {
			E[link[i]].push_back(i);
		}
		getSize(0);
	}
} SAM;

int main(){
	n = readStr(s);
	SAM.init();
	for (int i = 0; i < n; ++i) {
		SAM.insert(s[i] - 'a');
	}
	SAM.buildTree();
	long long ans = 0;
	for (int i = 0; i < SAM.cnt; ++i) {
		if (SAM.sz[i] > 1) {
			ans = std::max(ans, 1ll * SAM.len[i] * SAM.sz[i]);
		}
	}
	print(ans);
}
