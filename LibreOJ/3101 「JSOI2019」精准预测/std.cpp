#include <bits/stdc++.h>

const int N = 50005, M = 100005;
const int GN = M << 2;

int T, n, m, gn;

std::vector<int> tm[N];
std::vector<int> id[N];

struct Relation {
	int op, t, x, y;
} a[M];

std::vector<int> G[GN];

int ID(int x, int dx) {
	return x * 2 - dx;
}

void addEdge(int x, int dx, int y, int dy) {
	G[ID(y, dy)].push_back(ID(x, dx));
	G[ID(x, !dx)].push_back(ID(y, !dy));
}

int deg[GN];

const int B = 16700;

std::bitset<B> f[GN], mask;
bool flag[N];
int ans[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> T >> n >> m;
	for (int i = 1; i <= m; ++i) {
		std::cin >> a[i].op >> a[i].t >> a[i].x >> a[i].y;
		if (a[i].op == 0) {
			tm[a[i].x].push_back(a[i].t);
			tm[a[i].y].push_back(a[i].t + 1);
		} else {
			tm[a[i].x].push_back(a[i].t);
			tm[a[i].y].push_back(a[i].t);
		}
	}

	gn = 0;
	for (int i = 1; i <= n; ++i) {
		std::sort(tm[i].begin(), tm[i].end());
		tm[i].erase(std::unique(tm[i].begin(), tm[i].end()), tm[i].end());
		id[i].resize(tm[i].size());
		for (int j = 0; j < (int)tm[i].size(); ++j) {
			id[i][j] = ++gn;
		}
		for (int j = 1; j < (int)tm[i].size(); ++j) {
			addEdge(id[i][j], 1, id[i][j - 1], 1);
		}
	}
	for (int i = 1; i <= m; ++i) {
		int x = a[i].x, y = a[i].y;
		if (a[i].op == 0) {
			int u = id[x][std::lower_bound(tm[x].begin(), tm[x].end(), a[i].t) - tm[x].begin()];
			int v = id[y][std::lower_bound(tm[y].begin(), tm[y].end(), a[i].t + 1) - tm[y].begin()];
			addEdge(u, 0, v, 0);
		} else {
			int u = id[x][std::lower_bound(tm[x].begin(), tm[x].end(), a[i].t) - tm[x].begin()];
			int v = id[y][std::lower_bound(tm[y].begin(), tm[y].end(), a[i].t) - tm[y].begin()];
			addEdge(u, 1, v, 0);
		}
	}

	for (int i = 1; i <= gn * 2; ++i) {
		std::sort(G[i].begin(), G[i].end());
		G[i].erase(std::unique(G[i].begin(), G[i].end()), G[i].end());
	}

	for (int i = 1; i <= n; ++i) {
		ans[i] = n - 1;
		flag[i] = true;
	}

	for (int l = 1; l <= n; l += B) {
		int r = std::min(l + B - 1, n);
		for (int i = 1; i <= gn * 2; ++i) {
			f[i] = 0;
			deg[i] = 0;
		}
		for (int i = l; i <= r; ++i) {
			if (!id[i].empty()) {
				f[ID(id[i].back(), 0)][i - l] = 1;
			}
		}
		for (int i = 1; i <= gn * 2; ++i) {
			for (int j : G[i]) {
				++deg[j];
			}
		}
		std::vector<int> Q;
		for (int i = 1; i <= gn * 2; ++i) {
			if (!deg[i]) {
				Q.push_back(i);
			}
		}
		for (int i = 0; i < (int)Q.size(); ++i) {
			int u = Q[i];
			for (int v : G[u]) {
				f[v] |= f[u];
				--deg[v];
				if (!deg[v]) {
					Q.push_back(v);
				}
			}
		}
		mask = 0;
		for (int i = l; i <= r; ++i) {
			mask[i - l] = !id[i].empty() && f[ID(id[i].back(), 1)][i - l];
			if (mask[i - l]) {
				flag[i] = false;
			}
		}
		for (int i = 1; i <= n; ++i) {
			if (id[i].empty()) {
				ans[i] -= mask.count();
			} else {
				ans[i] -= (f[ID(id[i].back(), 1)] | mask).count();
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (flag[i]) {
			std::cout << ans[i];
		} else {
			std::cout << 0;
		}
		std::cout << " \n"[i == n];
	}
}