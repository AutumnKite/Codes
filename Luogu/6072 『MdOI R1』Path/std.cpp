#include <bits/stdc++.h>

const int N = 30005, B = 300, LG = 30;

int n;
std::vector<std::pair<int, int>> E[N];

int idx, dfn[N], sz[N];
int wxor[N];

void dfs(int u, int fa = 0) {
	dfn[u] = ++idx;
	sz[u] = 1;
	for (auto p : E[u]) {
		int v = p.first, w = p.second;
		if (v != fa) {
			wxor[v] = wxor[u] ^ w;
			dfs(v, u);
			sz[u] += sz[v];
		}
	}
}

int a[N * 2];

int tot, L[N * 2], R[N * 2], bel[N * 2];

int q;

struct Query {
	int l, r, bl, id;
	
	Query() {}
	
	Query(int _l, int _r, int _id) : l(_l), r(_r), bl(bel[l]), id(_id) {}

	bool operator < (const Query &rhs) const {
		if (bl != rhs.bl) {
			return bl < rhs.bl;
		}
		return r < rhs.r;
	}
} Q[N * 2];

struct Trie {
	static const int N = ::N * LG;

	int rt, cnt, sz[N], son[N][2];

	int new_node() {
		++cnt;
		sz[cnt] = 0;
		son[cnt][0] = son[cnt][1] = 0;
		return cnt;
	}

	Trie() : cnt(0) {
		rt = new_node();
	}

	void insert(int v) {
		int u = rt;
		for (int i = LG - 1; ~i; --i) {
			if (!son[u][v >> i & 1]) {
				son[u][v >>i & 1] = new_node();
			}
			u = son[u][v >> i & 1];
		}
	}

	void add(int v, int d) {
		int u = rt;
		sz[u] += d;
		for (int i = LG - 1; ~i; --i) {
			u = son[u][v >> i & 1];
			sz[u] += d;
		}
	}

	int query(int v) {
		int u = rt;
		int res = 0;
		for (int i = LG - 1; ~i; --i) {
			if (sz[son[u][!(v >> i & 1)]]) {
				u = son[u][!(v >> i & 1)];
				res |= 1 << i;
			} else {
				u = son[u][v >> i & 1];
			}
		}
		return res;
	}
} T, _T;

int now, _now;

void add(Trie &T, int v, int &now) {
	T.add(v, 1);
	now = std::max(now, T.query(v));
}

void del(Trie &T, int v) {
	T.add(v, -1);
}

int ans[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		E[u].emplace_back(v, w);
		E[v].emplace_back(u, w);
	}

	dfs(1);
	for (int i = 1; i <= n; ++i) {
		T.insert(wxor[i]);
		_T.insert(wxor[i]);
		a[dfn[i]] = wxor[i];
		a[dfn[i] + n] = wxor[i];
	}

	tot = (2 * n - 1) / B + 1;
	for (int i = 1; i <= tot; ++i) {
		L[i] = (i - 1) * B + 1;
		R[i] = std::min(2 * n, i * B);
		for (int j = L[i]; j <= R[i]; ++j) {
			bel[j] = i;
		}
	}

	for (int i = 2; i <= n; ++i) {
		Q[++q] = Query(dfn[i], dfn[i] + sz[i] - 1, i);
		Q[++q] = Query(dfn[i] + sz[i], n + dfn[i] - 1, i);
	}
	std::sort(Q + 1, Q + 1 + q);

	now = 0;
	int l = 1, r = 0, lst = 0;
	for (int i = 1; i <= q; ++i) {
		if (bel[Q[i].l] == bel[Q[i].r]) {
			_now = 0;
			for (int j = Q[i].l; j <= Q[i].r; ++j) {
				add(_T, a[j], _now);
			}
			ans[Q[i].id] += _now;
			for (int j = Q[i].l; j <= Q[i].r; ++j) {
				del(_T, a[j]);
			}
			continue;
		}
		if (bel[Q[i].l] != lst) {
			lst = bel[Q[i].l];
			while (r >= l) {
				del(T, a[r--]);
			}
			now = 0;
			r = R[lst], l = r + 1;
		}
		while (r < Q[i].r) {
			add(T, a[++r], now);
		}
		int tmp = now;
		while (l > Q[i].l) {
			add(T, a[--l], now);
		}
		ans[Q[i].id] += now;
		while (l < R[lst] + 1) {
			del(T, a[l++]);
		}
		now = tmp;
	}
	
	int Ans = 0;
	for (int i = 2; i <= n; ++i) {
		Ans = std::max(Ans, ans[i]);
	}
	std::cout << Ans << "\n";
}
