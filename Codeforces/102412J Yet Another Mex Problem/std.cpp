#include <bits/stdc++.h>

const long long INF = 0x3f3f3f3f3f3f3f3fll;

struct Line {
	long long k, b;

	Line() : k(0), b(-INF) {}
	Line(long long _k, long long _b) : k(_k), b(_b) {}

	long long get(long long x) {
		return k * x + b;
	}
};

std::vector<int> a;

class LiChaoTree {
	const long long L, R;

	struct Node {
		Node *ls, *rs;
		Line v;

		Node(Node *_ls, Node *_rs, Line _v) : ls(_ls), rs(_rs), v(_v) {}

		~Node() {
			delete ls;
			delete rs;
		}
	};

	Node *rt;

	void insert(Node *&u, long long l, long long r, Line v) {
		if (u == NULL) {
			u = new Node(NULL, NULL, v);
			return;
		}
		if (u->v.get(l) >= v.get(l) && u->v.get(r) >= v.get(r)) {
			return;
		}
		if (v.get(l) >= u->v.get(l) && v.get(r) >= u->v.get(r)) {
			u->v = v;
			return;
		}
		long long mid = (l + r) >> 1;
		if (u->v.get(mid) < v.get(mid)) {
			std::swap(u->v, v);
		}
		if (u->v.get(l) < v.get(l)) {
			insert(u->ls, l, mid, v);
		} else {
			insert(u->rs, mid + 1, r, v);
		}
	}

	long long query(Node *&u, long long l, long long r, long long x) {
		if (u == NULL) {
			return -INF;
		}
		long long mid = (l + r) >> 1;
		if (x <= mid) {
			return std::max(query(u->ls, l, mid, x), u->v.get(x));
		} else {
			return std::max(query(u->rs, mid + 1, r, x), u->v.get(x));
		}
	}

public:
	LiChaoTree(long long _L, long long _R) : L(_L), R(_R), rt(NULL) {}

	~LiChaoTree() {
		delete rt;
	}

	void insert(Line v) {
		return insert(rt, L, R, v);
	}

	long long query(long long x) {
		return query(rt, L, R, x);
	}
};

int enlarge_to_pow2(int n) {
	int res = 1;
	while (res < n) {
		res <<= 1;
	}
	return res;
}

class SegmentTree_LiChaoTree {
	int n;
	std::vector<LiChaoTree> a;

	void modify(int u, int l, int r, int x, Line v) {
		a[u].insert(v);
		if (l + 1 == r) {
			return;
		}
		int mid = (l + r + 1) >> 1;
		if (x < mid) {
			modify(u << 1, l, mid, x, v);
		} else {
			modify(u << 1 | 1, mid, r, x, v);
		}
	}

	long long query(int u, int l, int r, int L, int R, long long x) {
		if (L <= l && r <= R) {
			return a[u].query(x);
		}
		int mid = (l + r + 1) >> 1;
		if (R <= mid) {
			return query(u << 1, l, mid, L, R, x);
		} else if (L >= mid) {
			return query(u << 1 | 1, mid, r, L, R, x);
		} else {
			return std::max(query(u << 1, l, mid, L, R, x), query(u << 1 | 1, mid, r, L, R, x));
		}
	}

public:
	SegmentTree_LiChaoTree(int _n, long long L, long long R)
	  : n(_n), a(enlarge_to_pow2(n) * 2, LiChaoTree(L, R)) {}

	void modify(int x, Line v) {
		modify(1, 0, n, x, v);
	}

	long long query(int l, int r, long long x) {
		return query(1, 0, n, l, r, x);
	}
};

class SegmentTree {
	int n;
	std::vector<int> a;

	void modify(int u, int l, int r, int x, int v) {
		if (l + 1 == r) {
			a[u] = v;
			return;
		}
		int mid = (l + r + 1) >> 1;
		if (x < mid) {
			modify(u << 1, l, mid, x, v);
		} else {
			modify(u << 1 | 1, mid, r, x, v);
		}
		a[u] = std::min(a[u << 1], a[u << 1 | 1]);
	}

	int query(int u, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			return a[u];
		}
		int mid = (l + r + 1) >> 1;
		if (R <= mid) {
			return query(u << 1, l, mid, L, R);
		} else if (L >= mid) {
			return query(u << 1 | 1, mid, r, L, R);
		} else {
			return std::min(query(u << 1, l, mid, L, R), query(u << 1 | 1, mid, r, L, R));
		}
	}

	int find(int u, int l, int r, int v) {
		if (l + 1 == r) {
			return a[u] < v ? l : r;
		}
		int mid = (l + r + 1) >> 1;
		if (a[u << 1] < v) {
			return find(u << 1, l, mid, v);
		} else {
			return find(u << 1 | 1, mid, r, v);
		}
	}

public:
	SegmentTree(int _n) : n(_n), a(enlarge_to_pow2(n) * 2) {}

	void modify(int x, int v) {
		modify(1, 0, n, x, v);
	}

	int query(int l, int r) {
		return query(1, 0, n, l, r);
	}

	int find(int v) {
		return find(1, 0, n, v);
	}
};

int main() {
	freopen("mex.in", "r", stdin);
	freopen("mex.out", "w", stdout);

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	std::vector<long long> pre(n + 1);
	for (int i = 0; i < n; ++i) {
		pre[i + 1] = pre[i] + a[i];
	}

	SegmentTree_LiChaoTree pt(n + 1, 0, n), bt(n + 1, 0, pre[n]);
	SegmentTree pos(n + 1);
	std::vector<long long> f(n + 1);
	f[0] = 0;
	pt.modify(0, Line(0, 0));
	bt.modify(0, Line(0, 0));
	for (int i = 1; i <= n; ++i) {
		int x = a[i - 1];
		int l = pos.query(0, x + 1), r = x == 0 ? i : pos.query(0, x);
		pos.modify(x, i);
		while (r > l) {
			int mex = pos.find(r);
			int lst = pos.query(0, mex + 1);
			bt.modify(lst, Line(mex, pt.query(lst, r, mex)));
			r = lst;
		}
		f[i] = bt.query(std::max(0, i - m), i, pre[i]);
		int L = std::max(0, i - m);
		int mex = pos.find(L);
		int R = mex == 0 ? i : pos.query(0, mex);
		if (L < R) {
			f[i] = std::max(f[i], mex * pre[i] + pt.query(L, R, mex));
		}
		pt.modify(i, Line(-pre[i], f[i]));
		bt.modify(pos.query(0, 1), Line(0, f[i]));
	}
	std::cout << f[n] << "\n";
}
