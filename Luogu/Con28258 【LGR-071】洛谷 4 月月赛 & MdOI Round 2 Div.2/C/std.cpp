#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

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

const int N = 100005, M = 200005, W = 100005;

int n, m, k, mx;

struct Edge{
	int u, v, w, l;
} E[M];

int cnt, prime[W], vis[W];
std::vector<std::pair<int, int>> pf[W];
std::pair<int, int> sim[W];

void init(int n) {
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			prime[++cnt] = i;
			pf[i].push_back({i, 1});
		}
		for (int j = 1; j <= cnt && 1ll * prime[j] * i <= n; ++j) {
			int v = prime[j] * i;
			vis[v] = 1;
			pf[v] = pf[i];
			if (i % prime[j] == 0) {
				++pf[v].back().second;
				break;
			} else {
				pf[v].push_back({prime[j], 1});
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		std::vector<std::pair<int, int>> PF = pf[i];
		int w = 1, nw = 1;
		for (int j = 0; j < (int)PF.size(); ++j) {
			int p = PF[j].first, b = PF[j].second % k;
			if (b == 0) {
				continue;
			}
			for (int t = 0; t < b; ++t) {
				w *= p;
			}
			for (int t = b; t < k; ++t) {
				if (1ll * nw * p <= mx) {
					nw *= p;
				} else {
					nw = mx + 1;
				}
			}
		}
		sim[i] = {w, nw};
	}
}

std::vector<int> G[N];
std::map<int, int> F[N];
int f[M];

void topo() {
	static int d[N];
	for (int i = 1; i <= n; ++i) {
		d[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		for (int id : G[i]) {
			++d[E[id].v];
		}
	}
	std::vector<int> Q;
	for (int i = 1; i <= n; ++i) {
		if (!d[i]) {
			Q.push_back(i);
		}
	}
	for (int i = 0; i < (int)Q.size(); ++i) {
		int u = Q[i];
		for (int id : G[u]) {
			int v = E[id].v, w = E[id].w, l = E[id].l;
			if (F[u].count(sim[w].first)) {
				f[id] = F[u][sim[w].first] + l;
			} else {
				f[id] = l;
			}
			F[v][sim[w].second] = std::max(F[v][sim[w].second], f[id]);
			--d[v];
			if (!d[v]) {
				Q.push_back(v);
			}
		}
	}
}

int main() {
	read(n), read(m), read(k);
	for (int i = 1; i <= m; ++i) {
		read(E[i].u), read(E[i].v), read(E[i].w), read(E[i].l);
		mx = std::max(mx, E[i].w);
		G[E[i].u].push_back(i);
	}
	init(mx);
	topo();
	int ans = 0;
	for (int i = 1; i <= m; ++i) {
		ans = std::max(ans, f[i]);
	}
	print(ans);
}
