#include <bits/stdc++.h>

const int N = 100005, B = 320;

int n, q;
int a[N];
int tot, L[N], R[N], bel[N];
int m, v[N];

struct Query {
	int l, r, bl, id;

	bool operator < (const Query &rhs) const {
		if (bl != rhs.bl) {
			return bl < rhs.bl;
		}
		return r < rhs.r;
	}
} Q[N];

long long ans[N];

int cnt[N], _cnt[N];
long long now;

void del(int x) {
	--cnt[x];
}

void add(int x) {
	++cnt[x];
	now = std::max(now, 1ll * cnt[x] * v[x]);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		v[++m] = a[i];
	}
	std::sort(v + 1, v + 1 + n);
	m = std::unique(v + 1, v + 1 + m) - v - 1;
	for (int i = 1; i <= n; ++i) {
		a[i] = std::lower_bound(v + 1, v + 1 + m, a[i]) - v;
	}

	tot = (n - 1) / B + 1;
	for (int i = 1; i <= tot; ++i) {
		L[i] = (i - 1) * B + 1;
		R[i] = std::min(n, i * B);
		for (int j = L[i]; j <= R[i]; ++j) {
			bel[j] = i;
		}
	}

	for (int i = 1; i <= q; ++i) {
		std::cin >> Q[i].l >> Q[i].r;
		Q[i].bl = bel[Q[i].l];
		Q[i].id = i;
	}
	std::sort(Q + 1, Q + 1 + q);

	int l = 1, r = 0, lst = 0;
	for (int i = 1; i <= q; ++i) {
		if (bel[Q[i].l] == bel[Q[i].r]) {
			for (int j = Q[i].l; j <= Q[i].r; ++j) {
				++_cnt[a[j]];
			}
			for (int j = Q[i].l; j <= Q[i].r; ++j) {
				ans[Q[i].id] = std::max(ans[Q[i].id], 1ll * _cnt[a[j]] * v[a[j]]);
			}
			for (int j = Q[i].l; j <= Q[i].r; ++j) {
				--_cnt[a[j]];
			}
			continue;
		}
		if (bel[Q[i].l] != lst) {
			lst = bel[Q[i].l];
			while (r > R[lst]) {
				del(a[r--]);
			}
			while (l < R[lst] + 1) {
				del(a[l++]);
			}
			now = 0;
		}
		while (r < Q[i].r) {
			add(a[++r]);
		}
		long long tmp = now;
		while (l > Q[i].l) {
			add(a[--l]);
		}
		ans[Q[i].id] = now;
		while (l < R[lst] + 1) {
			del(a[l++]);
		}
		now = tmp;
	}
	for (int i = 1; i <= q; ++i) {
		std::cout << ans[i] << "\n";
	}
}