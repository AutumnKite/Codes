#include <bits/stdc++.h>

const int N = 200005, B = 1000;

int n, q;
int ls[N], rs[N];
bool vis[N];
int rt;

int fa[N], sz[N], son[N];
bool may[N];
int top[N];
long long sum;

void dfs(int u, int f) {
	if (!u) {
		return;
	}
	fa[u] = f;
	dfs(ls[u], u);
	dfs(rs[u], u);
	may[u] = abs(sz[ls[u]] - sz[rs[u]]) <= B;
	if (!son[u] || sz[ls[u]] != sz[rs[u]]) {
		if (sz[ls[u]] >= sz[rs[u]]) {
			son[u] = ls[u];
		} else {
			son[u] = rs[u];
		}
	}
	sum += son[u];
	sz[u] = sz[ls[u]] + sz[rs[u]] + 1;
}

void get_top(int u, int tp) {
	if (!u) {
		return;
	}
	top[u] = tp;
	if (may[u]) {
		get_top(ls[u], ls[u]);
		get_top(rs[u], rs[u]);
	} else {
		get_top(ls[u], tp);
		get_top(rs[u], tp);
	}
}

void build() {
	sum = 0;
	dfs(rt, 0);
	get_top(rt, rt);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> ls[i] >> rs[i];
		vis[ls[i]] = vis[rs[i]] = true;
	}
	for (int i = 1; i <= n; ++i) {
		if (!vis[i]) {
			rt = i;
			break;
		}
	}

	build();
	std::cout << sum << "\n";
	std::cin >> q;
	for (int i = 1; i <= q; ++i) {
		int u;
		std::cin >> u;
		if (ls[fa[u]] == u) {
			ls[fa[u]] = 0;
		} else {
			rs[fa[u]] = 0;
		}
		sum -= son[fa[u]];
		son[fa[u]] = ls[fa[u]] ^ rs[fa[u]];
		sum += son[fa[u]];
		u = fa[u];
		while (top[u] != rt) {
			u = top[u];
			--sz[u];
			int v = ls[fa[u]] ^ rs[fa[u]] ^ u;
			if (sz[v] > sz[son[fa[u]]]) {
				sum -= son[fa[u]];
				sum += v;
				son[fa[u]] = v;
			}
			u = fa[u];
		}
		std::cout << sum << "\n";
		if (i % B == 0) {
			build();
		}
	}
}
