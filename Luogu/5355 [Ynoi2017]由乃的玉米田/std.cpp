#include <bits/stdc++.h>

const int N = 100005, B = 400, S = 500;

int n, m, q;
int a[N];

struct Query {
	int op, l, r, x, bl, id;

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

std::vector<int> qid[S + 5];

bool ans[N];

int lst[N], p[N];

std::bitset<N> now1, now2;
int cnt[N];

void add(int x) {
	if (!cnt[a[x]]) {
		now1[a[x]] = now2[m - a[x]] = 1;
	}
	++cnt[a[x]];
}

void del(int x) {
	--cnt[a[x]];
	if (!cnt[a[x]]) {
		now1[a[x]] = now2[m - a[x]] = 0;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	m = 0;
	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		m = std::max(m, a[i]);
	}
	for (int i = 1; i <= q; ++i) {
		std::cin >> Q[i].op >> Q[i].l >> Q[i].r >> Q[i].x;
		Q[i].bl = (Q[i].l - 1) / B + 1;
		Q[i].id = i;
		m = std::max(m, Q[i].x);
	}

	std::sort(Q + 1, Q + 1 + q);

	for (int i = 1; i <= q; ++i) {
		if (Q[i].op == 4 && Q[i].x <= S) {
			qid[Q[i].x].push_back(i);
		}
	}
	for (int i = 0; i <= S; ++i) {
		if (qid[i].empty()) {
			continue;
		}
		for (int j = 0; j <= m; ++j) {
			lst[j] = 0;
		}
		p[0] = 0;
		for (int j = 1; j <= n; ++j) {
			lst[a[j]] = j;
			p[j] = p[j - 1];
			if (a[j] && 1ll * a[j] * i <= m) {
				p[j] = std::max(p[j], lst[a[j] * i]);
			}
			if (i && a[j] && a[j] % i == 0) {
				p[j] = std::max(p[j], lst[a[j] / i]);
			}
		}
		for (int j : qid[i]) {
			ans[Q[j].id] = (Q[j].l <= p[Q[j].r]);
		}
	}

	int l = 1, r = 0;
	for (int i = 1; i <= q; ++i) {
		if (Q[i].op == 4 && Q[i].x <= S) {
			continue;
		}
		while (l > Q[i].l) {
			add(--l);
		}
		while (r < Q[i].r) {
			add(++r);
		}
		while (l < Q[i].l) {
			del(l++);
		}
		while (r > Q[i].r) {
			del(r--);
		}
		if (Q[i].op == 1) {
			ans[Q[i].id] = (now1 << Q[i].x & now1).any();
		} else if (Q[i].op == 2) {
			ans[Q[i].id] = (now1 << (m - Q[i].x) & now2).any();
		} else if (Q[i].op == 3) {
			if (Q[i].x == 0) {
				ans[Q[i].id] = now1[0];
			} else {
				ans[Q[i].id] = false;
				for (int j = 1; j * j <= Q[i].x; ++j) {
					if (Q[i].x % j == 0 && now1[j] && now1[Q[i].x / j]) {
						ans[Q[i].id] = true;
						break;
					}
				}
			}
		} else {
			ans[Q[i].id] = false;
			for (int j = 1; j <= m / Q[i].x; ++j) {
				if (now1[j] && now1[j * Q[i].x]) {
					ans[Q[i].id] = true;
				}
			}
		}
	}
	for (int i = 1; i <= q; ++i) {
		if (ans[i]) {
			std::cout << "yuno\n";
		} else {
			std::cout << "yumi\n";
		}
	}
}