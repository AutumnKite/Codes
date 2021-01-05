#include <bits/stdc++.h>

const int N = 100005;

int n;
std::pair<int, int> a[N];

std::mt19937 rnd(time(0));

struct Treap {
	static const int N = ::N;

	int cnt;
	int ls[N], rs[N], sz[N];
	unsigned key[N];
	int val[N];
	int tag[N];

	int new_node(int v) {
		int u = ++cnt;
		ls[u] = rs[u] = 0;
		sz[u] = 1;
		key[u] = rnd();
		val[u] = v;
		tag[u] = 0;
		return u;
	}

	void up(int u) {
		sz[u] = sz[ls[u]] + sz[rs[u]] + 1;
	}

	void add(int u, int v) {
		val[u] += v;
		tag[u] += v;
	}

	void down(int u) {
		if (ls[u]) {
			add(ls[u], tag[u]);
		}
		if (rs[u]) {
			add(rs[u], tag[u]);
		}
		tag[u] = 0;
	}

	std::pair<int, int> split_v(int u, int v) {
		if (!u) {
			return {0, 0};
		}
		down(u);
		if (v <= val[u]) {
			std::pair<int, int> res = split_v(ls[u], v);
			ls[u] = res.second;
			up(u);
			return {res.first, u};
		} else {
			std::pair<int, int> res = split_v(rs[u], v);
			rs[u] = res.first;
			up(u);
			return {u, res.second};
		}
	}

	std::pair<int, int> split_sz(int u, int k) {
		if (!u) {
			return {0, 0};
		}
		down(u);
		if (k <= sz[ls[u]]) {
			std::pair<int, int> res = split_sz(ls[u], k);
			ls[u] = res.second;
			up(u);
			return {res.first, u};
		} else {
			std::pair<int, int> res = split_sz(rs[u], k - sz[ls[u]] - 1);
			rs[u] = res.first;
			up(u);
			return {u, res.second};
		}
	}

	int merge(int u, int v) {
		if (!u || !v) {
			return u | v;
		}
		down(u), down(v);
		if (key[u] < key[v]) {
			rs[u] = merge(rs[u], v);
			up(u);
			return u;
		} else {
			ls[v] = merge(u, ls[v]);
			up(v);
			return v;
		}
	}

	int kth(int u, int k) {
		while (u) {
			down(u);
			if (k <= sz[ls[u]]) {
				u = ls[u];
			} else if (sz[ls[u]] + 1 == k) {
				return val[u];
			} else {
				k -= sz[ls[u]] + 1;
				u = rs[u];
			}
		}
		return 0;
	}

	long long get_ans(int u) {
		if (!u) {
			return 0;
		}
		down(u);
		return get_ans(ls[u]) + get_ans(rs[u]) + 1ll * val[u] * (val[u] - 1) / 2;
	}
} T;

int rt;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i].first >> a[i].second;
	}
	std::sort(a + 1, a + 1 + n);

	rt = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= a[i].first - a[i - 1].first; ++j) {
			rt = T.merge(T.new_node(0), rt);
		}
		int v = T.kth(rt, a[i].second);
		std::pair<int, int> t1 = T.split_v(rt, v);
		std::pair<int, int> t2 = T.split_v(t1.second, v + 1);
		std::pair<int, int> t3 = T.split_sz(t2.first, a[i].second - T.sz[t1.first]);
		T.add(t1.first, 1), T.add(t3.first, 1);
		rt = T.merge(T.merge(t1.first, t3.second), T.merge(t3.first, t2.second));
	}

	std::cout << T.get_ans(rt) << "\n";
}