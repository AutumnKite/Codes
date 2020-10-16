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

const int N = 100005;
const long long INF = 0x3f3f3f3f3f3f3f3fll;

int n[2], m, q;
char tmp[N];
int d[2][N];
int L[2][N][2], R[2][N][2];

int myabs(int x) {
	return x > 0 ? x : -x;
}

int main() {
	read(n[0]), read(n[1]), read(q);
	for (int k = 0; k < 2; ++k) {
		readStr(tmp + 1);
		for (int i = 1; i <= n[k]; ++i) {
			d[k][i] = tmp[i] == (k ? 'S' : 'E');
		}
		L[k][0][0] = L[k][0][1] = 0;
		for (int i = 1; i <= n[k]; ++i) {
			L[k][i][0] = L[k][i - 1][0], L[k][i][1] = L[k][i - 1][1];
			L[k][i][d[k][i]] = i;
		}
		R[k][n[k] + 1][0] = R[k][n[k] + 1][1] = n[k] + 1;
		for (int i = n[k]; i; --i) {
			R[k][i][0] = R[k][i + 1][0], R[k][i][1] = R[k][i + 1][1];
			R[k][i][d[k][i]] = i;
		}
	}
	while (q--) {
		int V[2][2];
		std::vector<int> p[2];
		for (int t = 0; t < 2; ++t) {
			for (int k = 0; k < 2; ++k) {
				int v;
				read(v);
				V[t][k] = v;
				for (int i = 0; i < 2; ++i) {
					if (L[k][v][i]) {
						p[k].push_back(L[k][v][i]);
					}
					if (R[k][v][i] <= n[k]) {
						p[k].push_back(R[k][v][i]);
					}
				}
			}
		}
		for (int k = 0; k < 2; ++k) {
			std::sort(p[k].begin(), p[k].end());
			p[k].erase(std::unique(p[k].begin(), p[k].end()), p[k].end());
		}
		int H = p[0].size(), W = p[1].size();
		std::vector<std::vector<std::pair<int, int>>> E(H * W);
		for (int i = 0; i < H; ++i) {
			for (int j = 0; j < W; ++j) {
				int x = i + (d[1][p[1][j]] ? 1 : -1);
				if (x >= 0 && x < H) {
					E[i * W + j].push_back({x * W + j, myabs(p[0][i] - p[0][x])});
				}
				int y = j + (d[0][p[0][i]] ? 1 : -1);
				if (y >= 0 && y < W) {
					E[i * W + j].push_back({i * W + y, myabs(p[1][j] - p[1][y])});
				}
			}
		}
		for (int t = 0; t < 2; ++t) {
			for (int k = 0; k < 2; ++k) {
				V[t][k] = std::lower_bound(p[k].begin(), p[k].end(), V[t][k]) - p[k].begin();
			}
		}
		auto Dijkstra = [&](int s, int t) {
			int n = E.size();
			std::vector<long long> dis(n, INF);
			std::vector<bool> vis(n, 0);
			std::priority_queue<std::pair<long long, int>> Q;
			dis[s] = 0, Q.push({0, s});
			while (!Q.empty()) {
				int u = Q.top().second;
				Q.pop();
				if (vis[u]) {
					continue;
				}
				vis[u] = 1;
				for (auto p : E[u]) {
					int v = p.first, w = p.second;
					if (dis[v] > dis[u] + w) {
						dis[v] = dis[u] + w;
						Q.push({-dis[v], v});
					}
				}
			}
			return dis[t];
		};
		long long ans = Dijkstra(V[0][0] * W + V[0][1], V[1][0] * W + V[1][1]);
		if (ans == INF) {
			print(-1);
		} else {
			print(ans);
		}
	}
}
