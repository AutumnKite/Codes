#include <bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
namespace io {
const int L = (1 << 21) + 1;
char ibuf[L], *iS, *iT, obuf[L], *oS = obuf, *oT = obuf + L - 1, c, st[55];
int f, tp;
#define gc()                                                \
	(iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, L, stdin), \
							 (iS == iT ? EOF : *iS++))                    \
						: *iS++)
inline void flush() {
	fwrite(obuf, 1, oS - obuf, stdout);
	oS = obuf;
}
inline void putc(char x) {
	*oS++ = x;
	if (oS == oT) flush();
}
template <class I>
inline void gi(I& x) {
	for (f = 1, c = gc(); c < '0' || c > '9'; c = gc())
		if (c == '-') f = -1;
	for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15);
	x *= f;
}
template <class I>
inline void print(I x) {
	if (!x) putc('0');
	if (x < 0) putc('-'), x = -x;
	while (x) st[++tp] = x % 10 + '0', x /= 10;
	while (tp) putc(st[tp--]);
}
struct IOF {
	~IOF() { flush(); }
} iof;
};
using io::putc;
using io::gi;
using io::print;
const int N = 400005, G = 20;
const ll inf = 1e18;
int n, cnt, lg[N << 1], m, nxt[N], id[N];
ll ret;
struct T {
	vector<pi> e[N];
	int fa[N], dep[N], f[G][N << 1], dfc, dfn[N];
	ll dis[N];
	int cmin(int x, int y) { return dep[x] < dep[y] ? x : y; }
	void dfs(int u) {
		f[0][++dfc] = u;
		dfn[u] = dfc;
		dep[u] = dep[fa[u]] + 1;
		int v, t;
		pi i;
		for(t = 0; t < (int)e[u].size(); t++) {
			i = e[u][t];
			if ((v = i.fi) != fa[u])
				dis[v] = dis[u] + i.se, fa[v] = u, dfs(v), f[0][++dfc] = u;
		}
	}
	void read() {
		int u, v, i, j, k, w;
		for (i = 1; i < n; i++)
			gi(u), gi(v), gi(w), e[u].pb(pi(v, w)), e[v].pb(pi(u, w));
		dfs(1);
		for (k = 2, i = 1; k <= m; k <<= 1, i++)
			for (j = 1; j <= m - k + 1; j++)
				f[i][j] = cmin(f[i - 1][j], f[i - 1][j + (k >> 1)]);
	}
	int rmq(int u, int v) {
		int d = lg[v - u + 1];
		return cmin(f[d][u], f[d][v - (1 << d) + 1]);
	}
	int lca(int u, int v) {
		u = dfn[u];
		v = dfn[v];
		if (u > v) swap(u, v);
		return rmq(u, v);
	}
} A, B;
ll calc(int u, int v) {
	return A.dis[u] + A.dis[v] - A.dis[A.lca(u, v)] - B.dis[B.lca(u, v)];
}
int find(int u) {
	int v, r;
	ll dis = -inf, t;
	for (v = 1; v <= n; v++)
		if ((t = calc(u, v)) > dis) dis = t, r = v;
	ret = max(ret, dis);
	return r;
}
int fix(int u) {
	if (nxt[u]) return nxt[u];
	return ++cnt, nxt[u] = find(u);
}
struct mrnd {
	unsigned seed;
	mrnd() { seed = 19260817 ^ time(0) ^ size_t(new char); }
	unsigned operator()() {
		seed ^= seed << 13;
		seed ^= seed >> 17;
		seed ^= seed << 5;
		return seed;
	}
};

bool cmp1(const int &x, const int &y) {
	return A.dis[x] < A.dis[y];
}
bool cmp2(const int &x, const int &y) {
	return B.dis[x] < B.dis[y];
}

int main() {
	mrnd rand;
	int i, t, u;
	gi(n);
	for (i = 1; i <= n; i++) id[i] = i;
	for (m = 2 * n - 2, i = 2; i <= m; i++) lg[i] = lg[i - 1] + !(i & (i - 1));
	A.read();
	B.read();
	sort(id + 1, id + n + 1, cmp1);
	for (i = 1; i <= min(10, n); i++) fix(id[i]);
	sort(id + 1, id + n + 1, cmp2);
	for (i = 1; i <= min(10, n); i++) fix(id[i]);
	while (cnt != n && clock() * 1.0 / CLOCKS_PER_SEC < 0.4 * 0.99)
		for (t = rand() % 30 + 2, u = rand() % n + 1; t--; u = fix(u))
			;
	print(ret);
	putc('\n');
	return 0;
}
