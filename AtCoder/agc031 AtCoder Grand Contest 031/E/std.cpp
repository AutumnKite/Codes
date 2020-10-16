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

struct Jewel {
	int x, y;
	long long v;
};

struct Constraint {
	int op, a, b;
};

struct Network {
	const int INFcap = 0x3f3f3f3f;
	const long long INFcost = 0x3f3f3f3f3f3f3f3fll;

	struct Edge {
		int u, v;
		int cap;
		long long cost;
	};

	int n, S, T;
	std::vector<Edge> edge;
	std::vector<std::vector<int>> E;

	std::vector<long long> dis;
	std::vector<int> mn;
	std::vector<int> pre;

	Network() {}

	Network(int _n) : n(_n) {
		E.resize(n);
		dis.resize(n);
		mn.resize(n);
		pre.resize(n);
	}

	void setST(int _S, int _T) {
		S = _S, T = _T;
	}

	void addEdge(int u, int v, int cap, long long cost) {
		E[u].push_back((int)edge.size()), edge.push_back({u, v, cap, cost});
		E[v].push_back((int)edge.size()), edge.push_back({v, u, 0, -cost});
	}

	bool SPFA() {
		std::fill(dis.begin(), dis.end(), INFcost);
		std::fill(mn.begin(), mn.end(), 0);
		std::fill(pre.begin(), pre.end(), -1);
		std::vector<bool> vis(n, 0);
		std::vector<int> Q;
		dis[S] = 0, mn[S] = INFcap;
		Q.push_back(S), vis[S] = 1;
		for (int i = 0; i < (int)Q.size(); ++i) {
			int u = Q[i];
			vis[u] = 0;
			for (int id : E[u]) {
				int v = edge[id].v;
				int cap = edge[id].cap;
				long long cost = edge[id].cost;
				if (cap && dis[v] > dis[u] + cost) {
					dis[v] = dis[u] + cost;
					mn[v] = std::min(mn[u], cap);
					pre[v] = id;
					if (!vis[v]) {
						Q.push_back(v);
						vis[v] = 1;
					}
				}
			}
		}
		return dis[T] < INFcost;
	}

	void slope(int &flow, long long &cost) {
		flow = 0, cost = 0;
		while (SPFA()) {
			for (int u = T; u != S; u = edge[pre[u]].u) {
				edge[pre[u]].cap -= mn[T], edge[pre[u] ^ 1].cap += mn[T];
			}
			flow += mn[T], cost += dis[T] * mn[T];
		}
	}
};

struct LU_Network {
	const int INFcap = 0x3f3f3f3f;
	const long long INFcost = 0x3f3f3f3f3f3f3f3fll;

	struct Edge {
		int u, v;
		int lower, upper;
		long long cost;
	};

	int n, S, T;
	std::vector<Edge> edge;

	LU_Network() {}
	
	LU_Network(int _n) : n(_n) {}

	void setST(int _S, int _T) {
		S = _S, T = _T;
	}

	void addEdge(int u, int v, int lower, int upper, long long cost) {
		edge.push_back({u, v, lower, upper, cost});
	}

	bool slope(long long &cost) {
		std::vector<int> in(n), out(n);
		Network G(n + 2);
		long long tmp = 0;
		G.setST(n, n + 1);
		for (auto e : edge) {
			if (e.upper < e.lower) {
				return false;
			}
			G.addEdge(e.u, e.v, e.upper - e.lower, e.cost);
			in[e.v] += e.lower, out[e.u] += e.lower;
			tmp += e.lower * e.cost;
		}
		G.addEdge(T, S, INFcap, 0);
		int full = 0;
		for (int i = 0; i < n; ++i) {
			int delta = in[i] - out[i];
			if (delta > 0) {
				G.addEdge(G.S, i, delta, 0);
				full += delta;
			} else if (delta < 0) {
				G.addEdge(i, G.T, -delta, 0);
			}
		}
		int flow;
		G.slope(flow, cost);
		if (flow < full) {
			return false;
		}
		cost += tmp;
		return true;
	}
};

long long solve(const std::vector<Jewel> &jew, const std::vector<Constraint> &con, int tot) {
	int nx = 0, ny = 0;
	for (auto v : jew) {
		nx = std::max(nx, v.x + 1);
		ny = std::max(ny, v.y + 1);
	}
	for (auto v : con) {
		if (v.op < 2) {
			nx = std::max(nx, v.a + 1);
		} else {
			ny = std::max(ny, v.a + 1);
		}
	}
	LU_Network G(nx + ny + 2);
	std::vector<int> Lx(nx, 0), Rx(nx, G.INFcap);
	std::vector<int> Ly(ny, 0), Ry(ny, G.INFcap);
	Lx[nx - 1] = Rx[nx - 1] = Ly[ny - 1] = Ry[ny - 1] = tot;
	for (auto v : con) {
		if (v.op == 0) {
			Rx[v.a] = std::min(Rx[v.a], v.b);
		} else if (v.op == 1) {
			Lx[v.a - 1] = std::max(Lx[v.a - 1], tot - v.b);
		} else if (v.op == 2) {
			Ry[v.a] = std::min(Ry[v.a], v.b);
		} else {
			Ly[v.a - 1] = std::max(Ly[v.a - 1], tot - v.b);
		}
	}
	G.setST(nx + ny, nx + ny + 1);
	G.addEdge(G.S, nx - 1, Lx[nx - 1], Rx[nx - 1], 0);
	for (int i = 0; i < nx - 1; ++i) {
		G.addEdge(i + 1, i, Lx[i], Rx[i], 0);
	}
	G.addEdge(nx + ny - 1, G.T, Ly[ny - 1], Ry[ny - 1], 0);
	for (int i = 0; i < ny - 1; ++i) {
		G.addEdge(nx + i, nx + i + 1, Ly[i], Ry[i], 0);
	}
	for (auto v : jew) {
		G.addEdge(v.x, nx + v.y, 0, 1, -v.v);
	}
	long long cost = 0;
	if (!G.slope(cost)) {
		return 0;
	} else {
		return -cost;
	}
}

int main() {
	int n, m;
	read(n);
	std::vector<Jewel> jew(n);
	for (int i = 0; i < n; ++i) {
		read(jew[i].x), read(jew[i].y), read(jew[i].v);
	}
	read(m);
	std::vector<Constraint> con(m);
	for (int i = 0; i < m; ++i) {
		char tmp[5];
		readStr(tmp);
		if (tmp[0] == 'L') {
			con[i].op = 0;
		} else if (tmp[0] == 'R') {
			con[i].op = 1;
		} else if (tmp[0] == 'D') {
			con[i].op = 2;
		} else {
			con[i].op = 3;
		}
		read(con[i].a), read(con[i].b);
	}
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans = std::max(ans, solve(jew, con, i));
	}
	print(ans);
}
