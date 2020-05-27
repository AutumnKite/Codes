#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <ctime>

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

namespace randNumber {
	unsigned long long seed = 0x3C9FC1DA24BB75DFull;

	inline void srnd(unsigned long long _sd) {
		seed ^ _sd ? seed ^= _sd : 0;
	}

	inline unsigned long long rnd() {
		seed ^= seed << 13;
		seed ^= seed >> 7;
		seed ^= seed << 17;
		return seed + 0x764FF49E4F6C521Dull;
	}
}
using namespace randNumber;

const int N = 55, P = 998244353;

int n, m, mx, nv, col[N * 2], cnt[2], id[N * 2];
std::vector<int> E[N * 2];

struct Edge {
	int u, v, w, k;
} e[N * N * 2];

void dfs(int u, int c) {
	if (col[u] != -1) {
		return;
	}
	col[u] = c, id[u] = cnt[c]++;
	for (int v : E[u]) {
		dfs(v, c ^ 1);
	}
}

typedef std::vector<std::vector<int>> matrix;

int qpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = 1ll * s * a % P;
		}
		a = 1ll * a * a % P;
	}
	return s;
}

int det(matrix a) {
	int n = a.size();
	int ans = 1;
	for (int i = 0; i < n; ++i) {
		int k = -1;
		for (int j = i; j < n; ++j) {
			if (a[j][i]) {
				k = j;
				break;
			}
		}
		if (k == -1) {
			return 0;
		}
		if (k != i) {
			for (int j = i; j < n; ++j) {
				std::swap(a[i][j], a[k][j]);
			}
			ans = (P - ans) % P;
		}
		for (int j = i + 1; j < n; ++j) {
			if (a[j][i]) {
				int t = 1ll * (P - a[j][i]) * qpow(a[i][i], P - 2) % P;
				for (int k = i; k < n; ++k) {
					a[j][k] = (a[j][k] + 1ll * a[i][k] * t) % P;
				}
			}
		}
		ans = 1ll * ans * a[i][i] % P;
	}
	return ans;
}

int omega[1024];

typedef std::vector<int> poly;

poly rev;

void init() {
	int k = 0;
	while ((1 << k) < nv) {
		++k;
	}
	rev.resize(nv), rev[0] = 0, --k;
	for (int i = 1; i < nv; ++i) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << k);
	}
}

void IDFT(poly &f) {
	f.resize(nv);
	poly g(nv);
	for (int i = 0; i < nv; ++i) {
		for (int j = 0; j < nv; ++j) {
			g[i] = (g[i] + 1ll * omega[i * j % nv] * f[j]) % P;
		}
	}
	f = g, std::reverse(f.begin() + 1, f.end());
	int t = qpow(nv, P - 2);
	for (int i = 0; i < nv; ++i) {
		f[i] = 1ll * f[i] * t % P;
	}
}

int main() {
	srnd(time(0));
	read(n), read(m), n /= 2;
	for (int i = 0; i < m; ++i) {
		read(e[i].u), read(e[i].v), read(e[i].w);
		e[i].k = rnd() % P;
		E[e[i].u].push_back(e[i].v);
		E[e[i].v].push_back(e[i].u);
		mx = std::max(mx, e[i].w);
	}
	for (int i = 0; i < 2 * n; ++i) {
		col[i] = id[i] = -1;
	}
	for (int i = 0; i < 2 * n; ++i) {
		if (col[i] == -1) {
			dfs(i, 0);
			if (cnt[0] != cnt[1]) {
				printStr("YOU ARE IN TROUBLE");
				return 0;
			}
		}
	}
	nv = 1;
	while (nv <= n * mx) {
		nv <<= 1;
	}
	omega[0] = 1, omega[1] = qpow(3, (P - 1) / nv);
	for (int i = 2; i < nv; ++i) {
		omega[i] = 1ll * omega[i - 1] * omega[1] % P;
	}
	poly f(nv);
	for (int k = 0; k < nv; ++k) {
		matrix A(n, std::vector<int>(n, 0));
		for (int i = 0; i < m; ++i) {
			int u = e[i].u, v = e[i].v, w = e[i].w, p = e[i].k;
			if (col[u] == 1) {
				std::swap(u, v);
			}
			A[id[u]][id[v]] = 1ll * p * omega[k * w % nv] % P;
		}
		f[k] = det(A);
	}
	init(), IDFT(f);
	std::vector<int> ans;
	for (int i = 0; i < nv; ++i) {
		if (f[i]) {
			ans.push_back(i);
		}
	}
	if (!ans.size()) {
		printStr("YOU ARE IN TROUBLE");
		return 0;
	}
	print((int)ans.size());
	for (int v : ans) {
		print(v, ' ');
	}
}
