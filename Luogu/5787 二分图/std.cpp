#include <bits/stdc++.h>

const int N = 100005;

int n, m, k;

class DSU {
	int fa[N], fw[N], sz[N];
	bool is_bg;
	int top, sta[N];

public:
	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			fa[i] = i, fw[i] = 0, sz[i] = 1;
		}
		is_bg = true;
		top = 0;
	}

	int find(int x, int &w) {
		return fa[x] == x ? x : (w ^= fw[x], find(fa[x], w));
	}

	void merge(int x, int y, int w) {
		x = find(x, w), y = find(y, w);
		if (x == y) {
			if (is_bg && w) {
				is_bg = false;
				sta[++top] = 0;
			}
			return;
		}
		if (sz[x] < sz[y]) {
			std::swap(x, y);
		}
		fa[y] = x, fw[y] = w;
		sz[x] += sz[y];
		sta[++top] = y;
	}

	void undo() {
		int x = sta[top];
		--top;
		if (!x) {
			is_bg = true;
			return;
		}
		sz[fa[x]] -= sz[x];
		fa[x] = x, fw[x] = 0;
	}

	bool is_bigraph() {
		return is_bg;
	}

	int get_top() {
		return top;
	}
} D;

class SegmentTree {
	static const int N = ::N << 2;

	std::vector<std::pair<int, int>> E[N];

	void __add_edge(int u, int l, int r, int L, int R, std::pair<int, int> e) {
		if (L <= l && r <= R) {
			E[u].push_back(e);
			return;
		}
		int mid = (l + r) >> 1;
		if (L <= mid) {
			__add_edge(u << 1, l, mid, L, R, e);
		}
		if (R > mid) {
			__add_edge(u << 1 | 1, mid + 1, r, L, R, e);
		}
	}

	void __get_ans(int u, int l, int r, bool *ans) {
		int ntop = D.get_top();
		for (auto e : E[u]) {
			D.merge(e.first, e.second, 1);
		}
		if (l == r) {
			ans[l] = D.is_bigraph();
		} else {
			int mid = (l + r) >> 1;
			__get_ans(u << 1, l, mid, ans);
			__get_ans(u << 1 | 1, mid + 1, r, ans);
		}
		while (D.get_top() > ntop) {
			D.undo();
		}
	}

public:
	void add_edge(int x, int y, int l, int r) {
		if (l > r) {
			return;
		}
		__add_edge(1, 1, k, l, r, std::make_pair(x, y));
	}

	void get_ans(bool *ans) {
		D.init(n);
		__get_ans(1, 1, k, ans);
	}
} T;

bool ans[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m >> k;
	for (int i = 1; i <= m; ++i) {
		int x, y, l, r;
		std::cin >> x >> y >> l >> r;
		T.add_edge(x, y, l + 1, r);
	}
	T.get_ans(ans);
	for (int i = 1; i <= k; ++i) {
		if (ans[i]) {
			std::cout << "Yes\n";
		} else {
			std::cout << "No\n";
		}
	}
}