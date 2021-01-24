#include <bits/stdc++.h>

const int N = 1000005;

int n, m, q;
int d[N];

struct Edge {
	int u, v, c;
} E[N];

struct DSU {
	int fa[N];

	void init(int n) {
		for (int i = 1; i <= n; ++i) {
			fa[i] = i;
		}
	}

	int find(int x) {
		return fa[x] == x ? x : (fa[x] = find(fa[x]));
	}

	bool merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) {
			return false;
		}
		fa[y] = x;
		return true;
	}
} D;

int cnt[N];
int tot;

void add(int x, int v) {
	x = D.find(x);
	tot += !cnt[x];
	cnt[x] += v;
	tot -= !cnt[x];
}

int sd;

void add_deg(int x, int v) {
	sd -= d[x] & 1;
	d[x] += v;
	sd += d[x] & 1;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	D.init(n);
	for (int i = 0; i < m; ++i) {
		std::cin >> E[i].u >> E[i].v >> E[i].c;
		D.merge(E[i].u, E[i].v);
	}
	for (int i = 0; i < m; ++i) {
		add(E[i].u, E[i].c);
		add_deg(E[i].u, E[i].c), add_deg(E[i].v, E[i].c);
	}
	
	std::cin >> q;
	while (q--) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int x;
			std::cin >> x;
			add(E[x].u, -E[x].c);
			add_deg(E[x].u, -E[x].c), add_deg(E[x].v, -E[x].c);
			E[x].c ^= 1;
			add(E[x].u, E[x].c);
			add_deg(E[x].u, E[x].c), add_deg(E[x].v, E[x].c);
		} else {
			if (sd) {
				std::cout << -1 << "\n";
			} else {
				std::cout << tot << "\n";
			}
		}
	}
}