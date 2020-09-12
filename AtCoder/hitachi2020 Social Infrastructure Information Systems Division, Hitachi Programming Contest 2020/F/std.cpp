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

const int N = 200005, P = 998244353, I2 = (P + 1) >> 1;

int n;
std::vector<int> E[N];
int Fa[N];

std::pair<int, int> dfs(int u, int fa = 0) {
	Fa[u] = fa;
	std::pair<int, int> ans(0, u);
	for (int v : E[u]) {
		if (v != fa) {
			std::pair<int, int> tmp = dfs(v, u);
			++tmp.first;
			ans = std::max(ans, tmp);
		}
	}
	return ans;
}

int diam;

int f[N][3][3], g[3][3];

void DP(int u, int d, int fa = 0) {
	if (d == diam / 2) {
		f[u][1][1] = 1;
	} else {
		f[u][0][0] = 1;
	}
	for (int v : E[u]) {
		if (v != fa) {
			DP(v, d + 1, u);
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					for (int x = 0; x < 3; ++x) {
						for (int y = 0; y < 3; ++y) {
							for (int k = 0; k < 3; ++k) {
								int p = std::min(2, i + x * (k == 1)), q = std::min(2, j + y * (k == 2));
								g[p][q] = (g[p][q] + 1ll * f[u][i][j] * f[v][x][y]) % P;
							}
						}
					}
				}
			}
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					f[u][i][j] = g[i][j];
					g[i][j] = 0;
				}
			}
		}
	}
}

int main() {
	read(n);
	for (int i = 1; i < n; ++i) {
		int u, v;
		read(u), read(v);
		E[u].push_back(v), E[v].push_back(u);
	}
	int S = dfs(1).second, T = dfs(S).second;
	std::vector<int> p;
	for (int u = T; u; u = Fa[u]) {
		p.push_back(u);
	}
	diam = (int)p.size() - 1;
	if (diam % 2 == 0) {
		int x = p[diam >> 1];
		DP(x, 0);
		print(1ll * f[x][1][1] * I2 % P);
	} else {
		int x = p[(diam - 1) >> 1], y = p[(diam + 1) >> 1];
		DP(x, 0, y), DP(y, 0, x);
		int fx = (1ll * f[x][1][0] + f[x][1][1] + f[x][1][2]) % P;
		int fy = (1ll * f[y][0][1] + f[y][1][1] + f[y][2][1]) % P;
		print(1ll * fx * fy % P);
	}
}