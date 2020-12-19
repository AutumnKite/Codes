#include <bits/stdc++.h>

const int N = 100005, M = 500005, B = 70;

int n, q;
int a[N];
int m, v[N];
int c[N];
std::vector<int> E[N];
std::vector<int> son[N];

int idx, dfn[N], da[N], sz[N];
long long nans[N];

void dfs(int u, int fa) {
	dfn[u] = ++idx;
	da[idx] = a[u];
	nans[u] = c[a[u]];
	sz[u] = 1;
	for (int v : E[u]) {
		if (v != fa) {
			son[u].push_back(v);
			dfs(v, u);
			nans[u] += nans[v];
			sz[u] += sz[v];
		}
	}
}

bool insub(int u, int v) {
	return dfn[u] <= dfn[v] && dfn[v] < dfn[u] + sz[u];
}

int qcnt;

struct Query {
	int l, r, v, bl, id;

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
} Q[M * 4];

void addq(int r1, int r2, int v, int id) {
	if (r1 > r2) {
		std::swap(r1, r2);
	}
	Q[++qcnt] = {r1, r2, v, r1 / B + 1, id};
}

void addq(int l1, int r1, int l2, int r2, int v, int id) {
	addq(r1, r2, v, id);
	addq(l1 - 1, r2, -v, id);
	addq(r1, l2 - 1, -v, id);
	addq(l1 - 1, l2 - 1, v, id);
}

long long ans[M];
int cnt[2][N];
long long now;

void add(int k, int x, int v) {
	now -= 1ll * cnt[0][x] * cnt[1][x];
	cnt[k][x] += v;
	now += 1ll * cnt[0][x] * cnt[1][x];
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		v[++m] = a[i];
	}
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		E[u].push_back(v);
		E[v].push_back(u);
	}
	std::sort(v + 1, v + 1 + m);
	m = std::unique(v + 1, v + 1 + m) - v - 1;
	for (int i = 1; i <= n; ++i) {
		a[i] = std::lower_bound(v + 1, v + 1 + m, a[i]) - v;
		++c[a[i]];
	}
	dfs(1, 0);

	int rt = 1, id = 0;
	for (int i = 1; i <= q; ++i) {
		int op;
		std::cin >> op;
		if (op == 1) {
			std::cin >> rt;
		} else {
			int u, v;
			std::cin >> u >> v;
			++id;
			bool fu = u != rt && insub(u, rt), fv = v != rt && insub(v, rt);
			int su = 0, sv = 0;
			if (fu) {
				su = *(std::upper_bound(son[u].begin(), son[u].end(), rt, [&](int x, int y) {
					return dfn[x] < dfn[y];
				}) - 1);
			}
			if (fv) {
				sv = *(std::upper_bound(son[v].begin(), son[v].end(), rt, [&](int x, int y) {
					return dfn[x] < dfn[y];
				}) - 1);
			}
			if (u == rt && v == rt) {
				ans[id] = nans[1];
			} else if (u == rt) {
				if (fv) {
					ans[id] = nans[1] - nans[sv];
				} else {
					ans[id] = nans[v];
				}
			} else if (v == rt) {
				if (fu) {
					ans[id] = nans[1] - nans[su];
				} else {
					ans[id] = nans[u];
				}
			} else if (fu && fv) {
				ans[id] = nans[1] - nans[su] - nans[sv];
				addq(dfn[su], dfn[su] + sz[su] - 1, dfn[sv], dfn[sv] + sz[sv] - 1, 1, id);
			} else if (fu) {
				ans[id] = nans[v];
				addq(dfn[su], dfn[su] + sz[su] - 1, dfn[v], dfn[v] + sz[v] - 1, -1, id);
			} else if (fv) {
				ans[id] = nans[u];
				addq(dfn[u], dfn[u] + sz[u] - 1, dfn[sv], dfn[sv] + sz[sv] - 1, -1, id);
			} else {
				ans[id] = 0;
				addq(dfn[u], dfn[u] + sz[u] - 1, dfn[v], dfn[v] + sz[v] - 1, 1, id);
			}
		}
	}
	std::sort(Q + 1, Q + 1 + qcnt);

	int l = 0, r = 0;
	for (int i = 1; i <= qcnt; ++i) {
		while (l > Q[i].l) {
			add(0, da[l--], -1);
		}
		while (r < Q[i].r) {
			add(1, da[++r], 1);
		}
		while (l < Q[i].l) {
			add(0, da[++l], 1);
		}
		while (r > Q[i].r) {
			add(1, da[r--], -1);
		}
		ans[Q[i].id] += now * Q[i].v;
	}
	
	for (int i = 1; i <= id; ++i) {
		std::cout << ans[i] << "\n";
	}
}