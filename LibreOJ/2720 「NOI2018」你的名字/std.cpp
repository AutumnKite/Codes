#include <bits/stdc++.h>

class SuffixAutomaton {
	int new_node(int _len) {
		len.push_back(_len);
		trans.push_back(std::vector<int>(C, -1));
		link.push_back(-1);
		return n++;
	}

public:
	const int C;

	int n, cur;
	std::vector<std::vector<int>> trans;
	std::vector<int> len;
	std::vector<int> link;

	SuffixAutomaton(int _C) : C(_C), n(0) {
		cur = new_node(0);
	}

	void reserve(int _n) {
		trans.reserve(_n * 2);
		len.reserve(_n * 2);
		link.reserve(_n * 2);
	}

	void add(int c) {
		int p = cur;
		cur = new_node(len[p] + 1);
		while (p != -1 && trans[p][c] == -1) {
			trans[p][c] = cur;
			p = link[p];
		}
		if (p == -1) {
			link[cur] = 0;
			return;
		}
		int q = trans[p][c];
		if (len[p] + 1 == len[q]) {
			link[cur] = q;
			return;
		}
		int t = new_node(len[p] + 1);
		link[t] = link[q];
		trans[t] = trans[q];
		while (p != -1 && trans[p][c] == q) {
			trans[p][c] = t;
			p = link[p];
		}
		link[cur] = link[q] = t;
	}
};

class SegmentTrees {
	int n, cnt;
	std::vector<int> mx;
	std::vector<int> ls, rs;

	int new_node() {
		mx.push_back(-1);
		ls.push_back(-1);
		rs.push_back(-1);
		return cnt++;
	}

	void up(int u) {
		mx[u] = -1;
		if (ls[u] != -1) {
			mx[u] = std::max(mx[u], mx[ls[u]]);
		}
		if (rs[u] != -1) {
			mx[u] = std::max(mx[u], mx[rs[u]]);
		}
	}

	int __insert(int l, int r, int x) {
		int u = new_node();
		mx[u] = x;
		if (l + 1 == r) {
			return u;
		}
		int mid = (l + r + 1) >> 1;
		if (x < mid) {
			int v = __insert(l, mid, x);
			ls[u] = v;
		} else {
			int v = __insert(mid, r, x);
			rs[u] = v;
		}
		return u;
	}

	int __merge(int u, int v, int l, int r) {
		if (u == -1 || v == -1) {
			return std::max(u, v);
		}
		int mid = (l + r + 1) >> 1;
		int s = new_node();
		int _ls = __merge(ls[u], ls[v], l, mid);
		int _rs = __merge(rs[u], rs[v], mid, r);
		ls[s] = _ls, rs[s] = _rs;
		up(s);
		return s;
	}

	int __query(int u, int l, int r, int L, int R) {
		if (u == -1) {
			return -1;
		}
		if (L <= l && r <= R) {
			return mx[u];
		}
		int mid = (l + r + 1) >> 1;
		if (R <= mid) {
			return __query(ls[u], l, mid, L, R);
		} else if (L >= mid) {
			return __query(rs[u], mid, r, L, R);
		} else {
			return std::max(__query(ls[u], l, mid, L, R), __query(rs[u], mid, r, L, R));
		}
	}

public:
	SegmentTrees(int _n) : n(_n), cnt(0) {}

	void reserve(int _n) {
		mx.reserve(_n);
		ls.reserve(_n);
		rs.reserve(_n);
	}

	int insert(int x) {
		return __insert(0, n, x);
	}

	int merge(int u, int v) {
		return __merge(u, v, 0, n);
	}

	int query(int u, int l, int r) {
		if (l >= r) {
			return -1;
		}
		return __query(u, 0, n, l, r);
	}
};

int main() {
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::string s;
	std::cin >> s;
	int n = s.size();

	SuffixAutomaton A(26);
	A.reserve(n);
	std::vector<int> preA(n);
	for (int i = 0; i < n; ++i) {
		A.add(s[i] - 'a');
		preA[i] = A.cur;
	}

	SegmentTrees T(n);
	T.reserve(40000000);
	std::vector<int> rt(A.n);
	for (int i = 0; i < n; ++i) {
		rt[preA[i]] = T.insert(i);
	}

	std::vector<std::vector<int>> EA(A.n);
	for (int i = 1; i < A.n; ++i) {
		EA[A.link[i]].push_back(i);
	}

	std::function<void(int)> dfs = [&](int u) {
		for (int v : EA[u]) {
			dfs(v);
			rt[u] = T.merge(rt[u], rt[v]);
		}
	};

	dfs(0);

	int q;
	std::cin >> q;
	while (q--) {
		std::string t;
		int l, r;
		std::cin >> t >> l >> r;
		--l;
		int m = t.size();

		SuffixAutomaton B(26);
		B.reserve(m);
		std::vector<int> preB(m);
		for (int i = 0; i < m; ++i) {
			B.add(t[i] - 'a');
			preB[i] = B.cur;
		}
		std::vector<std::vector<int>> EB(B.n);
		for (int i = 1; i < B.n; ++i) {
			EB[B.link[i]].push_back(i);
		}

		std::vector<int> len(B.n);
		int u = 0;
		int now = 0;
		for (int i = 0; i < m; ++i) {
			while (u != -1 && A.trans[u][t[i] - 'a'] == -1) {
				u = A.link[u];
			}
			if (u == -1) {
				u = 0;
				now = 0;
			} else {
				now = std::min(now, A.len[u]);
				u = A.trans[u][t[i] - 'a'];
				++now;
			}
			while (u && T.query(rt[u], l + A.len[A.link[u]], r) == -1) {
				u = A.link[u];
				now = A.len[u];
			}
			if (u) {
				now = std::min(now, T.query(rt[u], l + A.len[A.link[u]], r) - l + 1);
			} else {
				now = 0;
			}
			len[preB[i]] = now;
		}

		std::function<void(int)> get_len = [&](int u) {
			for (int v : EB[u]) {
				get_len(v);
				len[u] = std::max(len[u], len[v]);
			}
		};

		get_len(0);
		long long ans = 0;
		for (int i = 1; i < B.n; ++i) {
			ans += std::max(B.len[i] - std::max(B.len[B.link[i]], len[i]), 0);
		}
		std::cout << ans << "\n";
	}
}
