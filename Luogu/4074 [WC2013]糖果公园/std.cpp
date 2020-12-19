#include <bits/stdc++.h>

const int N = 100005, B = 2500;

int n, mx, mq, m, q;
int v[N], w[N];
int a[N], tmp[N];
std::vector<int> E[N];

int fa[N], sz[N], dep[N], son[N];
int top[N];
int idx, st[N], ed[N], idt[N << 1];

void dfs(int u) {
	sz[u] = 1;
	dep[u] = dep[fa[u]] + 1;
	for (int v : E[u]) {
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v);
			sz[u] += sz[v];
			if (!son[u] || sz[v] > sz[son[u]]) {
				son[u] = v;
			}
		}
	}
}

void dfs(int u, int tp) {
	top[u] = tp;
	st[u] = ++idx;
	idt[idx] = u;
	if (son[u]) {
		dfs(son[u], tp);
	}
	for (int v : E[u]) {
		if (v != fa[u] && v != son[u]) {
			dfs(v, v);
		}
	}
	ed[u] = ++idx;
	idt[idx] = u;
}

int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) {
			std::swap(u, v);
		}
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}

struct Query {
	int l, r, t, z, lbl, rbl, id;

	Query() {}

	Query(int _l, int _r, int _t, int _z, int _id) {
		l = _l, r = _r, t = _t, z = _z, id = _id;
		lbl = (l - 1) / B + 1, rbl = (r - 1) / B + 1;
	}

	bool operator < (const Query &rhs) const {
		if (lbl != rhs.lbl) {
			return lbl < rhs.lbl;
		}
		if (rbl != rhs.rbl) {
			if (lbl & 1) {
				return rbl < rhs.rbl;
			} else {
				return rbl > rhs.rbl;
			}
		}
		if (rbl & 1) {
			return t < rhs.t;
		} else {
			return t > rhs.t;
		}
	}
} Q[N];

struct Modify {
	int x, from, to;
} M[N];

bool vis[N];
int cnt[N];
long long now;

void add(int x) {
	++cnt[x];
	now += 1ll * v[x] * w[cnt[x]];
}

void del(int x) {
	now -= 1ll * v[x] * w[cnt[x]];
	--cnt[x];
}

void flip(int x) {
	if (vis[x]) {
		del(a[x]);
	} else {
		add(a[x]);
	}
	vis[x] ^= 1;
}

void modify(int x, int v) {
	if (vis[x]) {
		del(a[x]);
		add(v);
	}
	a[x] = v;
}

long long ans[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> mx >> mq;
	for (int i = 1; i <= mx; ++i) {
		std::cin >> v[i];
	}
	for (int i = 1; i <= n; ++i) {
		std::cin >> w[i];
	}
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		E[u].push_back(v), E[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		tmp[i] = a[i];
	}
	dfs(1), dfs(1, 1);

	for (int i = 1; i <= mq; ++i) {
		int op;
		std::cin >> op;
		if (op == 0) {
			int x, c;
			std::cin >> x >> c;
			++m;
			M[m] = {x, tmp[x], c};
			tmp[x] = c;
		} else {
			int u, v;
			std::cin >> u >> v;
			++q;
			if (st[u] > st[v]) {
				std::swap(u, v);
			}
			int z = LCA(u, v);
			if (z == u) {
				Q[q] = Query(st[u], st[v], m, 0, q);
			} else {
				Q[q] = Query(ed[u], st[v], m, z, q);
			}
		}
	}
	std::sort(Q + 1, Q + 1 + q);

	int l = 1, r = 0, t = 0;
	for (int i = 1; i <= q; ++i) {
		while (l > Q[i].l) {
			flip(idt[--l]);
		}
		while (r < Q[i].r) {
			flip(idt[++r]);
		}
		while (l < Q[i].l) {
			flip(idt[l++]);
		}
		while (r > Q[i].r) {
			flip(idt[r--]);
		}
		while (t < Q[i].t) {
			++t;
			modify(M[t].x, M[t].to);
		}
		while (t > Q[i].t) {
			modify(M[t].x, M[t].from);
			--t;
		}
		if (Q[i].z) {
			flip(Q[i].z);
			ans[Q[i].id] = now;
			flip(Q[i].z);
		} else {
			ans[Q[i].id] = now;
		}
	}

	for (int i = 1; i <= q; ++i) {
		std::cout << ans[i] << "\n";
	}
}