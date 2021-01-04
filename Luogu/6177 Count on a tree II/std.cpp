#include <bits/stdc++.h>

const int N = 40005, B = 350, C = N / B + 5;

int n, q;
int a[N];
int m, v[N];

std::vector<int> E[N];

int fa[N];

int mx[N];
int cnt, key[N];

void get_keys(int u) {
	mx[u] = 0;
	for (int v : E[u]) {
		if (v != fa[u]) {
			get_keys(v);
			mx[u] = std::max(mx[u], mx[v] + 1);
		}
	}
	if (mx[u] >= B) {
		key[u] = ++cnt;
		mx[u] = 0;
	} else {
		key[u] = 0;
	}
}

int idx, dfn[N], sz[N];

void dfs(int u) {
	dfn[u] = ++idx;
	sz[u] = 1;
	for (int v : E[u]) {
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v);
			sz[u] += sz[v];
		}
	}
}

bool subtree(int u, int v) {
	return dfn[u] <= dfn[v] && dfn[v] < dfn[u] + sz[u];
}

std::bitset<N> col[C][C];
std::bitset<N> now;

void get_cols(int rt, int u, int fa = 0) {
	if (key[u]) {
		col[key[rt]][key[u]] = now;
	}
	bool tmp = now[a[u]];
	now[a[u]] = true;
	for (int v : E[u]) {
		if (v != fa) {
			get_cols(rt, v, u);
		}
	}
	now[a[u]] = tmp;
}

int lst[N];

void get_lst(int u) {
	if (fa[u] && !key[fa[u]]) {
		lst[u] = lst[fa[u]];
	} else {
		lst[u] = fa[u];
	}
	for (int v : E[u]) {
		if (v != fa[u]) {
			get_lst(v);
		}
	}
}

void update(int &u, int v) {
	if (lst[u] && !subtree(lst[u], v)) {
		while (!key[u]) {
			now[a[u]] = 1;
			u = fa[u];
		}
		int p = u;
		while (lst[u] && !subtree(lst[u], v)) {
			u = lst[u];
		}
		now |= col[key[p]][key[u]];
	}
	while (!subtree(u, v)) {
		now[a[u]] = 1;
		u = fa[u];
	}
	now[a[u]] = 1;
}

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
		E[u].push_back(v);
		E[v].push_back(u);
	}

	fa[1] = 0, dfs(1);
	get_keys(1);
	for (int i = 1; i <= n; ++i) {
		if (key[i]) {
			get_cols(i, i);
		}
	}
	get_lst(1);

	int ans = 0;
	while (q--) {
		int u, v;
		std::cin >> u >> v;
		u ^= ans;
		now.reset();
		update(u, v);
		update(v, u);
		ans = now.count();
		std::cout << ans << "\n";
	}
}