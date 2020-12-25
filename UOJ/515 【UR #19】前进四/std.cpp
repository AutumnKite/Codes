#include <bits/stdc++.h>

const int N = 1000005;
const int INF = 0x3f3f3f3f;

int n, mq, m, q;

int cnt, nxt[N * 3], first[N * 3], second[N * 3];

struct Vector {
	int head, tail;

	Vector() {
		head = tail = 0;
	}

	void push_back(int _first, int _second) {
		++cnt, first[cnt] = _first, second[cnt] = _second;
		if (tail) {
			nxt[tail] = cnt, tail = cnt;
		} else {
			head = tail = cnt;
		}
	}

	int begin() {
		return head;
	}

	int find_next(int x) {
		return nxt[x];
	}

	int get_first(int x) {
		return first[x];
	}

	int get_second(int x) {
		return second[x];
	}
} p[N], Q[N];

int ans[N];

struct Node {
	int mx, cnt, cmx;

	Node() {}
	Node(int v) {
		mx = v, cnt = 1, cmx = -INF;
	}
};

Node operator + (const Node &A, const Node &B) {
	Node res;
	res.cmx = std::max(A.cmx, B.cmx);
	if (A.mx == B.mx) {
		res.mx = A.mx;
		res.cnt = A.cnt + B.cnt;
	} else if (A.mx > B.mx) {
		res.mx = A.mx;
		res.cnt = A.cnt;
		res.cmx = std::max(res.cmx, B.mx);
	} else {
		res.mx = B.mx;
		res.cnt = B.cnt;
		res.cmx = std::max(res.cmx, A.mx);
	}
	return res;
}

struct SegmentTree {
	static const int N = ::N << 2;

	Node val[N];
	int tag[N], tot[N];

	void build(int u, int l, int r) {
		tag[u] = INF, tot[u] = 0;
		if (l == r) {
			val[u] = Node(INF);
			return;
		}
		int mid = (l + r) >> 1;
		build(u << 1, l, mid);
		build(u << 1 | 1, mid + 1, r);
		val[u] = val[u << 1] + val[u << 1 | 1];
	}

	void chmin(int u, int v, int t) {
		if (val[u].mx <= v) {
			return;
		}
		tag[u] = v, tot[u] += t;
		if (val[u].cmx < v) {
			val[u].mx = v;
			return;
		}
	}

	void down(int u) {
		chmin(u << 1, tag[u], tot[u]);
		chmin(u << 1 | 1, tag[u], tot[u]);
		tag[u] = INF, tot[u] = 0;
	}

	void modify(int u, int l, int r, int L, int R, int v) {
		if (val[u].mx <= v) {
			return;
		}
		if (L <= l && r <= R && val[u].cmx < v) {
			chmin(u, v, 1);
			return;
		}
		int mid = (l + r) >> 1;
		down(u);
		if (L <= mid) {
			modify(u << 1, l, mid, L, R, v);
		}
		if (R > mid) {
			modify(u << 1 | 1, mid + 1, r, L, R, v);
		}
		val[u] = val[u << 1] + val[u << 1 | 1];
	}

	int query(int u, int l, int r, int x) {
		if (l == r) {
			return tot[u];
		}
		int mid = (l + r) >> 1;
		down(u);
		if (x <= mid) {
			return query(u << 1, l, mid, x);
		} else {
			return query(u << 1 | 1, mid + 1, r, x);
		}
	}
} T;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> mq;
	for (int i = 1; i <= n; ++i) {
		int v;
		std::cin >> v;
		p[i].push_back(0, v);
	}
	for (int i = 1; i <= mq; ++i) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int x, v;
			std::cin >> x >> v;
			++m;
			p[x].push_back(m, v);
		} else {
			int x;
			std::cin >> x;
			++q;
			Q[x].push_back(m, q);
		}
	}

	T.build(1, 0, m);
	for (int i = n; i; --i) {
		for (int j = p[i].begin(); j; j = p[i].find_next(j)) {
			int t = p[i].find_next(j) ? p[i].get_first(p[i].find_next(j)) - 1 : m;
			T.modify(1, 0, m, p[i].get_first(j), t, p[i].get_second(j));
		}
		for (int j = Q[i].begin(); j; j = Q[i].find_next(j)) {
			ans[Q[i].get_second(j)] = T.query(1, 0, m, Q[i].get_first(j));
		}
	}

	for (int i = 1; i <= q; ++i) {
		std::cout << ans[i] << "\n";
	}
}
