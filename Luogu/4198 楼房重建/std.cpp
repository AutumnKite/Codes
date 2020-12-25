#include <bits/stdc++.h>

const int N = 100005;

int n, q;

struct Node {
	int x, y;

	bool operator < (const Node &rhs) const {
		return 1ll * y * rhs.x < 1ll * rhs.y * x;
	}
};

struct SegmentTree {
	static const int N = ::N << 2;
	
	Node mx[N];
	int sum[N], right[N];

	void build(int u, int l, int r) {
		mx[u] = {l, 0};
		sum[u] = 0;
		right[u] = 0;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
	}

	int get(int u, int l, int r, Node pre) {
		if (l == r) {
			return pre < mx[u];
		}
		int mid = (l + r) >> 1;
		if (mx[u << 1] < pre) {
			return get(u << 1 | 1, mid + 1, r, pre);
		} else {
			return get(u << 1, l, mid, pre) + right[u];
		}
	}

	void modify(int u, int l, int r, int x, int v) {
		if (l == r) {
			mx[u].y = v;
			sum[u] = v > 0;
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid) {
			modify(u << 1, l, mid, x, v);
		} else {
			modify(u << 1 | 1, mid + 1, r, x, v);
		}
		mx[u] = std::max(mx[u << 1], mx[u << 1 | 1]);
		right[u] = get(u << 1 | 1, mid + 1, r, mx[u << 1]);
		sum[u] = sum[u << 1] + right[u];
	}
} T;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> q;
	T.build(1, 1, n);
	while (q--) {
		int x, y;
		std::cin >> x >> y;
		T.modify(1, 1, n, x, y);
		std::cout << T.sum[1] << "\n";
	}
}