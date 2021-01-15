#include <bits/stdc++.h>

const int N = 100005, INF = 0x3f3f3f3f;

int n, q, tp;
int a[N];

struct SegmentTree {
	static const int N = ::N << 2;

	int mx[N];
	int mn[N];
	int left[N];

	int get(int u, int l, int r, int suf) {
		if (l == r) {
			return std::max(mx[u], suf) + l;
		}
		int mid = (l + r) >> 1;
		if (mx[u << 1 | 1] < suf) {
			return std::min(get(u << 1, l, mid, suf), suf + mid + 1);
		} else {
			return std::min(left[u], get(u << 1 | 1, mid + 1, r, suf));
		}
	}

	void up(int u, int l, int mid) {
		mx[u] = std::max(mx[u << 1], mx[u << 1 | 1]);
		left[u] = get(u << 1, l, mid, mx[u << 1 | 1]);
		mn[u] = std::min(left[u], mn[u << 1 | 1]);
	}

	void build(int u, int l, int r) {
		if (l == r) {
			mx[u] = a[l] - l;
			mn[u] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		up(u, l, mid);
	}

	void modify(int u, int l, int r, int x, int v) {
		if (l == r) {
			mx[u] = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid) {
			modify(u << 1, l, mid, x, v);
		} else {
			modify(u << 1 | 1, mid + 1, r, x, v);
		}
		up(u, l, mid);
	}

	int get_mx(int u, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return mx[u];
		}
		int mid = (l + r) >> 1;
		if (R <= mid) {
			return get_mx(u << 1, l, mid, L, R);
		} else if (L > mid) {
			return get_mx(u << 1 | 1, mid + 1, r, L, R);
		} else {
			return std::max(get_mx(u << 1, l, mid, L, R), get_mx(u << 1 | 1, mid + 1, r, L, R));
		}
	}

	int query(int u, int l, int r, int x, int suf) {
		if (l == r) {
			return std::max(mx[u], suf) + l;
		}
		int mid = (l + r) >> 1;
		if (x <= mid) {
			return query(u << 1, l, mid, x, std::max(suf, mx[u << 1 | 1]));
		} else {
			return std::min(get(u << 1, l, mid, std::max(suf, mx[u << 1 | 1])), query(u << 1 | 1, mid + 1, r, x, suf));
		}
	}
} T;

void modify(int x, int v) {
	T.modify(1, 1, n, x, v - x);
}

int query() {
	int l = 1, r = n - 1, ans = n;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (T.get_mx(1, 1, n, 1, mid) >= T.get_mx(1, 1, n, mid + 1, n) + n) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	int t1 = T.get_mx(1, 1, n, 1, ans) + ans;
	int t2 = T.query(1, 1, n, ans, -INF) + n - 1;
	return std::min(t1, t2);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> q >> tp;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}

	T.build(1, 1, n);

	int ans = query();
	std::cout << ans << "\n";
	while (q--) {
		int x, y;
		std::cin >> x >> y;
		if (tp) {
			x ^= ans, y ^= ans;
		}
		modify(x, y);
		ans = query();
		std::cout << ans << "\n";
	}
}