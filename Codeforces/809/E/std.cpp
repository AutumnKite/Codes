#include <bits/stdc++.h>

const int N = 200000, LG = 18, P = 1000000007;

int n;
int id[N + 1];
std::vector<int> d[N];
std::vector<int> nd[N + 1];

int inv[N + 1], phi[N + 1], mu[N + 1], f[N + 1];
std::vector<int> E[N];

void init() {
	inv[1] = 1;
	for (int i = 2; i <= n; ++i) {
		inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	}
	for (int i = 1; i <= n; ++i) {
		phi[i] += i;
		for (int j = i + i; j <= n; j += i) {
			phi[j] -= phi[i];
		}
	}
	for (int i = 1; i <= n; ++i) {
		mu[i] += i == 1;
		for (int j = i + i; j <= n; j += i) {
			mu[j] -= mu[i];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; j += i) {
			f[j] = (f[j] + 1ll * i * inv[phi[i]] * mu[j / i]) % P;
		}
	}
}

int idx, dfn[N], ed[N], dep[N];
int st[LG + 1][N * 2 - 1];

void dfs(int u, int fa) {
	for (int i = 0; i < (int)d[u].size(); ++i) {
		int p = d[u][i];
		nd[p].push_back(u);
	}
	dfn[u] = idx;
	st[0][idx++] = u;
	for (int i = 0; i < (int)E[u].size(); ++i) {
		int v = E[u][i];
		if (v != fa) {
			dep[v] = dep[u] + 1;
			dfs(v, u);
			st[0][idx++] = u;
		}
	}
	ed[u] = idx;
}

int Log[N * 2];

int min(int u, int v) {
	return dep[u] < dep[v] ? u : v;
}

void initST() {
	Log[1] = 0;
	for (int i = 2; i <= idx; ++i) {
		Log[i] = Log[i >> 1] + 1;
	}
	for (int i = 1; i <= LG; ++i) {
		for (int j = 0; j + (1 << i) <= idx; ++j) {
			st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
		}
	}
}

int LCA(int u, int v) {
	int l = dfn[u], r = dfn[v];
	if (l > r) {
		std::swap(l, r);
	}
	++r;
	int t = Log[r - l];
	return min(st[t][l], st[t][r - (1 << t)]);
}

int top, sta[N];
std::vector<int> G[N];

void insert(int u) {
	if (!top) {
		sta[top++] = u;
		return;
	}
	int x = sta[top - 1], y;
	while (top && dfn[u] > ed[x]) {
		y = x;
		--top;

	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int v;
		std::cin >> v;
		id[v] = i;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; j += i) {
			d[id[j]].push_back(i);
		}
	}
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		std::cin >> u >> v;
		--u, --v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	init();
	dfs(0, -1);
	initST();
}
