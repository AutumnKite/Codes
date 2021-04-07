#include <bits/stdc++.h>

const int N = 525010, LG = 21;

int n;
int a[N];
std::vector<int> E[N];

struct Trie {
	static const int N = ::N * LG + 1;
	
	int cnt;
	int son[N][2];
	int sz[N];
	int sum[N];

	int new_node() {
		int u = cnt++;
		son[u][0] = son[u][1] = -1;
		sz[u] = sum[u] = 0;
		return u;
	}

	void up(int u) {
		sum[u] = 0;
		if (son[u][0] != -1) {
			sum[u] ^= sum[son[u][0]] << 1;
		}
		if (son[u][1] != -1) {
			sum[u] ^= sum[son[u][1]] << 1 | (sz[son[u][1]] & 1);
		}
	}

public:
	Trie() : cnt(0) {}

	void insert(int &rt, int x) {
		if (rt == -1) {
			rt = new_node();
		}
		int u = rt;
		for (int i = 0; i < LG; ++i) {
			int &v = son[u][x >> i & 1];
			if (v == -1) {
				v = new_node();
			}
			++sz[u];
			sum[u] ^= x >> i;
			u = v;
		}
		++sz[u];
	}

	int merge(int u, int v) {
		if (u == -1 || v == -1) {
			return u == -1 ? v : u;
		}
		sz[u] += sz[v];
		son[u][0] = merge(son[u][0], son[v][0]);
		son[u][1] = merge(son[u][1], son[v][1]);
		up(u);
		return u;
	}

	void add(int u) {
		if (u == -1) {
			return;
		}
		std::swap(son[u][0], son[u][1]);
		add(son[u][0]);
		up(u);
	}

	int val(int u) {
		return sum[u];
	}
};

Trie T;

int rt[N];
int ans[N];

void dfs(int u) {
	rt[u] = -1;
	for (int i = 0; i < (int)E[u].size(); ++i) {
		int v = E[u][i];
		dfs(v);
		rt[u] = T.merge(rt[u], rt[v]);
	}
	T.add(rt[u]);
	T.insert(rt[u], a[u]);
	ans[u] = T.val(rt[u]);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	for (int i = 1; i < n; ++i) {
		int p;
		std::cin >> p;
		--p;
		E[p].push_back(i);
	}

	dfs(0);
	
	long long sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += ans[i];
	}
	std::cout << sum << "\n";
}
