#include <bits/stdc++.h>

#pragma optimize("no-stack-protector")
#define pb push_back
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define ALL(a) a.begin(), a.end()
#define lowbit(x) ((x) & -(x))

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, int> pii;
typedef pair<int, int> pi;
typedef vector<int> VI;

template <class T>
inline bool chkmin(T &a, T b) {
	return b < a ? a = b, true : false;
}
template <class T>
inline bool chkmax(T &a, T b) {
	return a < b ? a = b, true : false;
}

const int N = 100005, G = 20;
struct P {
	int x, y, pos;
	P() { x = y = pos = 0; }
	P(int x, int y, int pos) : x(x), y(y), pos(pos) {}
	P operator-(P a) { return P(x - a.x, y - a.y, -1); }
	ll len() { return (ll)x * x + (ll)y * y; }
} p[N];
#define func(name, type) bool name(const type &a, const type &b)
func(cmpx, P) { return a.x < b.x; }
func(cmpy, P) { return a.y < b.y; }
func(cmpid, P) { return a.pos < b.pos; }
struct E {
	int u, v;
	ll d;
	E() { u = v = d = 0; }
	E(int u, int v, ll d) : u(u), v(v), d(d) {}
	bool operator<(const E &t) const { return d < t.d; }
};
vector<E> all;
int n, q, dsu[N], fa[N][G], dep[N];
ll fd[N][G];
int find(int u) { return dsu[u] == u ? u : dsu[u] = find(dsu[u]); }
void link() {
	priority_queue<pii> q;
	int i, j, l, r, B = 1e6 / n, A = 6e7 / n;
	for (i = 1; i <= n; i++) {
		l = max(i - A, 1), r = min(i + A, n);
		for (j = l; j < i; j++) {
			ll dis = (p[j] - p[i]).len();
			if (q.size() < B || dis < q.top().fi) {
				q.push(pii(dis, j));
				if (q.size() > B) q.pop();
			}
		}
		while (q.size())
			all.pb(E(p[i].pos, p[q.top().se].pos, q.top().fi)), q.pop();
		for (j = i + 1; j <= r; j++) {
			ll dis = (p[j] - p[i]).len();
			if (q.size() < B || dis < q.top().fi) {
				q.push(pii(dis, j));
				if (q.size() > B) q.pop();
			}
		}
		while (q.size())
			all.pb(E(p[i].pos, p[q.top().se].pos, q.top().fi)), q.pop();
	}
}
vector<int> adj[N];
void dfs(int u) {
	dep[u] = dep[fa[u][0]] + 1;
	int d, t, v;
	for (d = 0; fa[u][d]; fa[u][d + 1] = fa[fa[u][d]][d],
			fd[u][d + 1] = max(fd[u][d], fd[fa[u][d]][d]), ++d)
		;
	for (t = 0; t < adj[u].size(); t ++)
		if ((v = adj[u][t]) != fa[u][0]) fa[v][0] = u, fd[v][0] = (p[u] - p[v]).len(), dfs(v);
}
ll ask(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	ll res = 0;
	int d = dep[u] - dep[v], i;
	for (i = 0; d; ++i)
		if (d >> i & 1) chkmax(res, fd[u][i]), u = fa[u][i], d ^= 1 << i;
	for (i = 17; i >= 0; i--)
		if (fa[u][i] != fa[v][i]) {
			chkmax(res, fd[u][i]), u = fa[u][i];
			chkmax(res, fd[v][i]), v = fa[v][i];
		}
	if (u != v) chkmax(res, fd[u][0]), chkmax(res, fd[v][0]);
	return res;
}
int main() {
	int i, u, v;
	ll ans;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y), p[i].pos = i;
	sort(p + 1, p + n + 1, cmpx);
	link();
	sort(p + 1, p + n + 1, cmpy);
	link();
	sort(all.begin(), all.end());
	sort(p + 1, p + n + 1, cmpid);
	for (i = 1; i <= n; i++) dsu[i] = i;
	E e;
	for (i = 0; i < all.size(); i ++) {
		e = all[i];
		if (find(u = e.u) != find(v = e.v))
			dsu[find(u)] = find(v), adj[u].pb(v), adj[v].pb(u);
	}
	dfs(1);
	scanf("%d", &q);
	for (i = 1; i <= q; i++) {
		scanf("%d%d", &u, &v);
		ans = ask(u, v);
		printf("%lld\n", ans);
	}
	return 0;
}
