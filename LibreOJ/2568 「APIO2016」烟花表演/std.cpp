#include <bits/stdc++.h>

const int N = 300005;

int n, m;
int fa[N], w[N], d[N];
long long sum;

struct leftist_tree {
	static const int N = ::N * 2;

	int cnt;
	int top, rub[N];
	int ls[N], rs[N], dis[N];
	long long val[N];

	leftist_tree() {
		cnt = top = 0;
	}

	int new_node(long long v) {
		int u = top ? rub[top--] : ++cnt;
		ls[u] = rs[u] = 0;
		dis[u] = 0;
		val[u] = v;
		return u;
	}

	int merge(int u, int v) {
		if (!u || !v) {
			return u | v;
		}
		if (val[u] < val[v]) {
			std::swap(u, v);
		}
		rs[u] = merge(rs[u], v);
		if (dis[ls[u]] < dis[rs[u]]) {
			std::swap(ls[u], rs[u]);
		}
		if (!rs[u]) {
			dis[u] = 0;
		} else {
			dis[u] = dis[rs[u]] + 1;
		}
		return u;
	}

	int pop(int u) {
		rub[++top] = u;
		return merge(ls[u], rs[u]);
	}

	int push(int u, long long v) {
		return merge(u, new_node(v));
	}
} T;

int rt[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	n += m;
	for (int i = 2; i <= n; ++i) {
		std::cin >> fa[i] >> w[i];
		++d[fa[i]];
		sum += w[i];
	}

	for (int i = n; i > 1; --i) {
		if (d[i]) {
			for (int j = 1; j < d[i]; ++j) {
				rt[i] = T.pop(rt[i]);
			}
			long long l, r;
			r = T.val[rt[i]] + w[i], rt[i] = T.pop(rt[i]);
			l = T.val[rt[i]] + w[i], rt[i] = T.pop(rt[i]);
			rt[i] = T.push(rt[i], l);
			rt[i] = T.push(rt[i], r);
		} else {
			rt[i] = T.push(rt[i], w[i]);
			rt[i] = T.push(rt[i], w[i]);
		}
		rt[fa[i]] = T.merge(rt[fa[i]], rt[i]);
	}

	for (int i = 1; i <= d[1]; ++i) {
		rt[1] = T.pop(rt[1]);
	}
	long long ans = sum;
	while (rt[1]) {
		ans -= T.val[rt[1]];
		rt[1] = T.pop(rt[1]);
	}
	std::cout << ans << "\n";
}