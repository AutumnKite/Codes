#include <bits/stdc++.h>

const int P = 998244353;

struct Node {
	int cnt[2], pre[2], suf[2], tot;
	long long ans;
	
	Node() : tot(0), ans(0) {
		cnt[0] = cnt[1] = pre[0] = pre[1] = suf[0] = suf[1] = 0;
	}

	Node(int l, int r) : tot(0), ans(0) {
		cnt[1] = (r >> 1) - (l >> 1);
		cnt[0] = r - l - cnt[1];
		pre[0] = pre[1] = suf[0] = suf[1] = 0;
	}
};

Node operator+(const Node &a, const Node &b) {
	Node res;
	res.tot = a.tot ^ b.tot;
	res.ans = a.ans + b.ans;
	for (int i = 0; i < 2; ++i) {
		res.cnt[i] = a.cnt[i] + b.cnt[i];
		res.pre[i] = a.pre[i] + (a.tot ? b.cnt[i] - b.pre[i] : b.pre[i]);
		res.suf[i] = b.suf[i] + (b.tot ? a.cnt[i] - a.suf[i] : a.suf[i]);
		res.ans += 1ll * a.suf[i ^ 1] * (b.cnt[i] - b.pre[i]);
		res.ans += 1ll * b.pre[i ^ 1] * (a.cnt[i] - a.suf[i]);
	}
	return res;
}

struct SegmentTree {
	SegmentTree *ls, *rs;
	Node a;

	SegmentTree() : ls(NULL), rs(NULL) {}
	~SegmentTree() {
		delete ls;
		delete rs;
	}
};

void up(SegmentTree *u, int l, int mid, int r) {
	u->a = (u->ls == NULL ? Node(l, mid) : u->ls->a) + (u->rs == NULL ? Node(mid, r) : u->rs->a);
}

void modify(SegmentTree *&u, int l, int r, int x) {
	if (u == NULL) {
		u = new SegmentTree;
	}
	if (l + 1 == r) {
		u->a.tot = 1;
		u->a.ans = 0;
		u->a.cnt[l & 1] = u->a.pre[l & 1] = u->a.suf[l & 1] = 1;
		return;
	}
	int mid = (l + r + 1) >> 1;
	if (x < mid) {
		modify(u->ls, l, mid, x);
	} else {
		modify(u->rs, mid, r, x);
	}
	up(u, l, mid, r);
}

SegmentTree *merge(SegmentTree *u, SegmentTree *v, int l, int r) {
	if (u == NULL) {
		return v;
	}
	if (v == NULL) {
		return u;
	}
	if (l + 1 == r) {
		return u;
	}
	int mid = (l + r + 1) >> 1;
	u->ls = merge(u->ls, v->ls, l, mid);
	u->rs = merge(u->rs, v->rs, mid, r);
	up(u, l, mid, r);
	return u;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<std::pair<int, int>>> E(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		--u, --v;
		E[u].emplace_back(v, w);
		E[v].emplace_back(u, w);
	}
	std::vector<std::vector<int>> pos(n);
	for (int i = 0; i < m; ++i) {
		int u;
		std::cin >> u;
		--u;
		pos[u].push_back(i);
	}
	
	std::vector<SegmentTree*> rt(n);
	int ans = 0;

	std::function<void(int, int)> dfs = [&](int u, int fa) {
		for (int x : pos[u]) {
			modify(rt[u], 0, m, x);
		}
		for (auto p : E[u]) {
			int v = p.first, w = p.second;
			if (v != fa) {
				dfs(v, u);
				if (rt[v] != NULL) {
					ans = (ans + rt[v]->a.ans % P * w) % P;
				}
				rt[u] = merge(rt[u], rt[v], 0, m);
			}
		}
	};

	dfs(0, -1);
	std::cout << ans << "\n";
}
