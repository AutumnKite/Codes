#include <bits/stdc++.h>

const int N = 40005, M = 100005, B = 120;

int n, q;
int a[N];
int m, v[N];
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
	int l, r, z, bl, id;

	bool operator < (const Query &rhs) const {
		if (bl != rhs.bl) {
			return bl < rhs.bl;
		}
		if (bl & 1) {
			return r < rhs.r;
		} else {
			return r > rhs.r;
		}
	}
} Q[M];

bool vis[N];
int cnt[N];
int now;

void add(int x) {
	if (!cnt[x]) {
		++now;
	}
	++cnt[x];
}

void del(int x) {
	--cnt[x];
	if (!cnt[x]) {
		--now;
	}
}

void flip(int x) {
	if (vis[x]) {
		del(a[x]);
	} else {
		add(a[x]);
	}
	vis[x] ^= 1;
}

int ans[M];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		v[++m] = a[i];
	}
	std::sort(v + 1, v + 1 + m);
	m = std::unique(v + 1, v + 1 + m) - v - 1;
	for (int i = 1; i <= n; ++i) {
		a[i] = std::lower_bound(v + 1, v + 1 + m, a[i]) - v;
	}
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		E[u].push_back(v), E[v].push_back(u);
	}
	dfs(1), dfs(1, 1);

	for (int i = 1; i <= q; ++i) {
		int u, v;
		std::cin >> u >> v;
		if (st[u] > st[v]) {
			std::swap(u, v);
		}
		int z = LCA(u, v);
		if (z == u) {
			Q[i] = {st[u], st[v], 0, (st[u] - 1) / B + 1, i};
		} else {
			Q[i] = {ed[u], st[v], z, (ed[u] - 1) / B + 1, i};
		}
	}
	std::sort(Q + 1, Q + 1 + q);

	int l = 1, r = 0;
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