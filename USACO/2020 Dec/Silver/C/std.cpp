#include <bits/stdc++.h>

const int N = 1005, INF = 0x3f3f3f3f;

int n;
char d[N];
int x[N], y[N];
std::vector<std::pair<int, int>> p[N];
std::vector<int> U, R;

int ans[N], fa[N];

std::vector<int> E[N];
int sz[N];

void dfs(int u) {
	sz[u] = 1;
	for (int v : E[u]) {
		dfs(v);
		sz[u] += sz[v];
	}
}

bool check(int i, int j) {
	if (d[i] == 'E') {
		std::swap(i, j);
	}
	int d1 = x[i] - x[j], d2 = y[j] - y[i];
	if (d1 < 0 || d1 > ans[j] || d2 < 0 || d2 > ans[i] || d1 == d2) {
		return false;
	}
	return true;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> d[i] >> x[i] >> y[i];
		ans[i] = INF;
		fa[i] = 0;
	}

	for (int i = 1; i <= n; ++i) {
		if (d[i] == 'N') {
			for (int j = 1; j <= n; ++j) {
				if (d[j] == 'E') {
					int d1 = x[i] - x[j], d2 = y[j] - y[i];
					if (d1 < 0 || d2 < 0 || d1 == d2) {
						continue;
					}
					if (d1 < d2) {
						p[i].push_back({d2, j});
					} else {
						p[j].push_back({d1, i});
					}
				}
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		std::sort(p[i].begin(), p[i].end());
		std::reverse(p[i].begin(), p[i].end());
	}

	for (int k = 1; k <= n; ++k) {
		int mn = 0, id = 0, kid = 0;
		for (int i = 1; i <= n; ++i) {
			if (ans[i] < INF) {
				continue;
			}
			while (!p[i].empty() && !check(p[i].back().second, i)) {
				p[i].pop_back();
			}
			if (!p[i].empty() && (!id || p[i].back().first < mn)) {
				mn = p[i].back().first;
				id = i;
				kid = p[i].back().second;
			}
		}
		if (!id) {
			break;
		}
		ans[id] = mn;
		fa[id] = kid;
	}

	for (int i = 1; i <= n; ++i) {
		E[fa[i]].push_back(i);
	}
	dfs(0);
	for (int i = 1; i <= n; ++i) {
		std::cout << sz[i] - 1 << "\n";
	}
}
