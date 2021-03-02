#include <bits/stdc++.h>

class BIT {
	int n;
	std::vector<int> c;

	int query(int x) {
		int s = 0;
		for (; x; x ^= x & -x) {
			s += c[x];
		}
		return s;
	}

public:
	BIT() {}

	BIT(int _n) : n(_n), c(n + 1) {}

	void add(int x, int v) {
		++x;
		for (; x <= n; x += x & -x) {
			c[x] += v;
		}
	}

	int query(int l, int r) {
		return query(r) - query(l);
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, q;
	std::cin >> n >> q;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::vector<int> sta;
	std::vector<int> lst(n);
	sta.push_back(-1);
	for (int i = 0; i < n; ++i) {
		while (sta.back() != -1 && a[sta.back()] > a[i]) {
			sta.pop_back();
		}
		lst[i] = sta.back();
		if (a[lst[i]] < a[i]) {
			lst[i] = -1;
		}
		sta.push_back(i);
	}

	std::vector<std::vector<std::pair<int, int>>> Q(n);
	for (int i = 0; i < q; ++i) {
		int l, r;
		std::cin >> l >> r;
		--l, --r;
		Q[r].emplace_back(l, i);
	}

	BIT T(n);
	std::vector<int> ans(q);
	for (int i = 0; i < n; ++i) {
		T.add(lst[i] + 1, 1);
		if (i + 1 < n) {
			T.add(i + 1, -1);
		}
		for (auto p : Q[i]) {
			ans[p.second] = T.query(0, p.first + 1);
		}
	}
	
	for (int v : ans) {
		std::cout << v << "\n";
	}
}