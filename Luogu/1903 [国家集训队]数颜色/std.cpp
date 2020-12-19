#include <bits/stdc++.h>

const int N = 133339, B = 2600;

int n, mq, q, m;
int a[N], tmp[N];

struct Query {
	int l, r, t, lbl, rbl, id;

	bool operator < (const Query &rhs) const {
		if (lbl != rhs.lbl) {
			return lbl < rhs.lbl;
		}
		if (rbl != rhs.rbl) {
			if (lbl & 1) {
				return rbl < rhs.rbl;
			} else {
				return rbl > rhs.rbl;
			}
		}
		if (rbl & 1) {
			return t < rhs.t;
		} else {
			return t > rhs.t;
		}
	}
} Q[N];

struct Modify {
	int x, from, to;
} M[N];

int cnt[1000005];
int l, r, t, now;

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

void modify(int x, int v) {
	if (l <= x && x <= r) {
		del(a[x]);
		add(v);
	}
	a[x] = v;
}

int ans[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> mq;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		tmp[i] = a[i];
	}
	for (int i = 1; i <= mq; ++i) {
		char op;
		std::cin >> op;
		if (op == 'Q') {
			int l, r;
			std::cin >> l >> r;
			++q;
			Q[q] = {l, r, m, (l - 1) / B + 1, (r - 1) / B + 1, q};
		} else {
			int x, c;
			std::cin >> x >> c;
			++m;
			M[m] = {x, tmp[x], c};
			tmp[x] = c;
		}
	}

	std::sort(Q + 1, Q + 1 + q);
	l = 1, r = 0, t = 0;
	for (int i = 1; i <= q; ++i) {
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
		while (t < Q[i].t) {
			++t;
			modify(M[t].x, M[t].to);
		}
		while (t > Q[i].t) {
			modify(M[t].x, M[t].from);
			--t;
		}
		ans[Q[i].id] = now;
	}

	for (int i = 1; i <= q; ++i) {
		std::cout << ans[i] << "\n";
	}
}