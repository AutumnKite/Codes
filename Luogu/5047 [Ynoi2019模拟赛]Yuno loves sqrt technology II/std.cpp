#include <bits/stdc++.h>

const int N = 100005, B = 320;

int n, q;
int a[N];
int m, v[N];

struct Query {
	int l, r, bl, id;

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
} Q[N];

struct UpdateQuery {
	int l, r, v, id;
};

std::vector<UpdateQuery> pre[N], suf[N];

long long ans[N];

int tot, L[N], R[N], bel[N];

struct Block {
	int v[N], tag[N];

	void clear() {
		for (int i = 1; i <= tot; ++i) {
			tag[i] = 0;
		}
		for (int i = 1; i <= m; ++i) {
			v[i] = 0;
		}
	}

	void add(int x) {
		for (int i = x; i <= R[bel[x]]; ++i) {
			++v[i];
		}
		for (int i = bel[x] + 1; i <= tot; ++i) {
			++tag[i];
		}
	}

	int query(int x) {
		return v[x] + tag[bel[x]];
	}
} T;

int pre_ans[N], suf_ans[N];

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

	for (int i = 1; i <= q; ++i) {
		std::cin >> Q[i].l >> Q[i].r;
		Q[i].bl = (Q[i].l - 1) / B + 1;
		Q[i].id = i;
	}
	std::sort(Q + 1, Q + 1 + q);

	int l = 1, r = 0;
	for (int i = 1; i <= q; ++i) {
		if (l > Q[i].l) {
			pre[r].push_back({Q[i].l, l - 1, 1, Q[i].id});
			l = Q[i].l;
		}
		if (r < Q[i].r) {
			suf[l].push_back({r + 1, Q[i].r, 1, Q[i].id});
			r = Q[i].r;
		}
		if (l < Q[i].l) {
			pre[r].push_back({l, Q[i].l - 1, -1, Q[i].id});
			l = Q[i].l;
		}
		if (r > Q[i].r) {
			suf[l].push_back({Q[i].r + 1, r, -1, Q[i].id});
			r = Q[i].r;
		}
	}

	tot = (m - 1) / B + 1;
	for (int i = 1; i <= tot; ++i) {
		L[i] = (i - 1) * B + 1;
		R[i] = std::min(m, i * B);
		for (int j = L[i]; j <= R[i]; ++j) {
			bel[j] = i;
		}
	}

	T.clear();
	for (int i = 1; i <= n; ++i) {
		T.add(a[i]);
		pre_ans[i] = T.query(a[i] - 1);
		for (auto v : pre[i]) {
			for (int x = v.l; x <= v.r; ++x) {
				ans[v.id] += T.query(a[x] - 1) * v.v;
			}
		}
	}

	T.clear();
	for (int i = n; i; --i) {
		T.add(a[i]);
		suf_ans[i] = T.query(m) - T.query(a[i]);
		for (auto v : suf[i]) {
			for (int x = v.l; x <= v.r; ++x) {
				ans[v.id] += (T.query(m) - T.query(a[x])) * v.v;
			}
		}
	}

	l = 1, r = 0;
	for (int i = 1; i <= q; ++i) {
		if (i > 1) {
			ans[Q[i].id] += ans[Q[i - 1].id];
		}
		while (l > Q[i].l) {
			ans[Q[i].id] -= pre_ans[--l];
		}
		while (r < Q[i].r) {
			ans[Q[i].id] -= suf_ans[++r];
		}
		while (l < Q[i].l) {
			ans[Q[i].id] += pre_ans[l++];
		}
		while (r > Q[i].r) {
			ans[Q[i].id] += suf_ans[r--];
		}
	}

	for (int i = 1; i <= q; ++i) {
		std::cout << ans[i] << "\n";
	}
}
/*
3 2
1 3 5
1 2
2 3
*/