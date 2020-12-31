#include <bits/stdc++.h>

const int N = 100005, B = 400, NB = 25000;

int n, q, tot;
int a[N];
int v[N];

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
} Q[NB * 3 + 5];

int ans[NB + 5];

std::bitset<N> now, com[NB + 5];
int cnt[N];

void add(int v) {
	now[v + cnt[v]] = 1;
	++cnt[v];
}

void del(int v) {
	--cnt[v];
	now[v + cnt[v]] = 0;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		v[i] = a[i];
	}
	std::sort(v + 1, v + 1 + n);
	for (int i = 1; i <= n; ++i) {
		a[i] = std::lower_bound(v + 1, v + 1 + n, a[i]) - v;
	}
	for (int k = 1; k <= q; k += NB) {
		int tq = std::min(q - k + 1, NB);
		tot = 0;
		for (int i = 1; i <= tq; ++i) {
			ans[i] = 0;
			com[i].set();
			for (int j = 0; j < 3; ++j) {
				++tot;
				std::cin >> Q[tot].l >> Q[tot].r;
				Q[tot].bl = (Q[tot].l - 1) / B + 1;
				Q[tot].id = i;
				ans[i] += Q[tot].r - Q[tot].l + 1;
			}
		}
		std::sort(Q + 1, Q + 1 + tot);
		now.reset();
		for (int i = 1; i <= n; ++i) {
			cnt[i] = 0;
		}
		int l = 1, r = 0;
		for (int i = 1; i <= tot; ++i) {
			while (l > Q[i].l) {
				add(a[--l]);
			}
			while (r < Q[i].r) {
				add(a[++r]);
			}
			while (l < Q[i].l) {
				del(a[l++]);
			}
			while (r > Q[i].r) {
				del(a[r--]);
			}
			com[Q[i].id] &= now;
		}
		for (int i = 1; i <= tq; ++i) {
			std::cout << ans[i] - 3 * com[i].count() << "\n";
		}
	}
}