#include <bits/stdc++.h>

typedef __uint128_t u128;

std::istream &operator>>(std::istream &input, u128 &x) {
	std::string s;
	input >> s;
	x = 0;
	for (int i = 0; i < (int)s.size(); ++i) {
		x = x << 4 | (s[i] <= '9' ? s[i] - '0' : s[i] - 'a' + 10);
	}
	return input;
}

std::ostream &operator<<(std::ostream &output, u128 x) {
	std::string s;
	do {
		s += (x & 15) >= 10 ? (x & 15) - 10 + 'a' : (x & 15) + '0';
		x >>= 4;
	} while (x);
	for (int i = (int)s.size() - 1; i >= 0; --i) {
		output << s[i];
	}
	return output;
}

struct node {
	u128 sor, sum;

	node() {}
	node(u128 v) : sor(v), sum(v) {}
	node(u128 _sor, u128 _sum) : sor(_sor), sum(_sum) {}
};

node operator+(const node &a, const node &b) {
	return node(a.sor | b.sor, a.sum + b.sum);
}

int enlarge(int n) {
	int res = 1;
	while (res < n) {
		res <<= 1;
	}
	return res;
}

class segment_tree {
	int n;
	std::vector<node> a;

	void build(int u, int l, int r, const std::vector<u128> &v) {
		if (l + 1 == r) {
			a[u] = node(v[l]);
			return;
		}
		int mid = (l + r + 1) >> 1;
		build(u << 1, l, mid, v);
		build(u << 1 | 1, mid, r, v);
		a[u] = a[u << 1] + a[u << 1 | 1];
	}

	void div(int u, int l, int r, int L, int R, u128 v) {
		if (!a[u].sor) {
			return;
		}
		if (l + 1 == r) {
			a[u].sor /= v;
			a[u].sum /= v;
			return;
		}
		int mid = (l + r + 1) >> 1;
		if (L < mid) {
			div(u << 1, l, mid, L, R, v);
		}
		if (mid < R) {
			div(u << 1 | 1, mid, r, L, R, v);
		}
		a[u] = a[u << 1] + a[u << 1 | 1];
	}

	void iand(int u, int l, int r, int L, int R, u128 v) {
		if ((a[u].sor | v) == v) {
			return;
		}
		if (l + 1 == r) {
			a[u].sor &= v;
			a[u].sum &= v;
			return;
		}
		int mid = (l + r + 1) >> 1;
		if (L < mid) {
			iand(u << 1, l, mid, L, R, v);
		}
		if (mid < R) {
			iand(u << 1 | 1, mid, r, L, R, v);
		}
		a[u] = a[u << 1] + a[u << 1 | 1];
	}

	u128 query(int u, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return a[u].sum;
		}
		int mid = (l + r + 1) >> 1;
		if (R <= mid) {
			return query(u << 1, l, mid, L, R);
		} else if (L >= mid) {
			return query(u << 1 | 1, mid, r, L, R);
		} else {
			return query(u << 1, l, mid, L, R) + query(u << 1 | 1, mid, r, L, R);
		}
	}

public:
	segment_tree(const std::vector<u128> &v) : n(v.size()), a(enlarge(n) << 1) {
		build(1, 0, n, v);
	}

	void div(int l, int r, u128 v) {
		if (v <= 1) {
			return;
		}
		div(1, 0, n, l, r, v);
	}

	void iand(int l, int r, u128 v) {
		iand(1, 0, n, l, r, v);
	}

	u128 query(int l, int r) {
		return query(1, 0, n, l, r);
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, q;
	std::cin >> n >> q;
	std::vector<u128> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	
	segment_tree T(a);
	while (q--) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int l, r;
			u128 v;
			std::cin >> l >> r >> v;
			--l;
			T.div(l, r, v);
		} else if (op == 2) {
			int l, r;
			u128 v;
			std::cin >> l >> r >> v;
			--l;
			T.iand(l, r, v);
		} else {
			int l, r;
			std::cin >> l >> r;
			--l;
			std::cout << T.query(l, r) << "\n";
		}
	}
}
