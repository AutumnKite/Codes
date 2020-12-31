#include <bits/stdc++.h>

const int L = 105, N = 10005;

int n, m;
char tmp[L];
int tot;
int col[N];
int id[L][L];

std::vector<int> E[N];

bool vis[N];
int match[N];

bool find(int u) {
	for (int v : E[u]) {
		if (!vis[v]) {
			vis[v] = true;
			if (match[v] == -1 || find(match[v])) {
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

void dfs(int u) {
	if (vis[u]) {
		return;
	}
	vis[u] = true;
	for (int v : E[u]) {
		if (match[v] != -1) {
			dfs(match[v]);
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		std::cin >> tmp;
		for (int j = 0; j < m; ++j) {
			if (tmp[j] == '.') {
				id[i][j] = tot++;
				col[id[i][j]] = (i + j) & 1;
			} else {
				id[i][j] = -1;
			}
		}
	}

	auto add = [&](int x, int y) {
		E[x].push_back(y);
		E[y].push_back(x);
	};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (i + 1 < n && id[i][j] != -1 && id[i + 1][j] != -1) {
				add(id[i][j], id[i + 1][j]);
			}
			if (j + 1 < m && id[i][j] != -1 && id[i][j + 1] != -1) {
				add(id[i][j], id[i][j + 1]);
			}
		}
	}

	std::fill(match, match + tot, -1);
	int ans = 0;
	for (int i = 0; i < tot; ++i) {
		if (col[i] == 0) {
			std::fill(vis, vis + tot, false);
			ans += find(i);
		}
	}
	if (ans * 2 == tot) {
		std::cout << "LOSE\n";
		return 0;
	}

	for (int i = 0; i < tot; ++i) {
		if (col[i] == 1) {
			match[match[i]] = i;
		}
	}
	std::fill(vis, vis + tot, false);
	for (int i = 0; i < tot; ++i) {
		if (match[i] == -1) {
			dfs(i);
		}
	}
	std::cout << "WIN\n";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (id[i][j] != -1 && vis[id[i][j]]) {
				std::cout << i + 1 << " " << j + 1 << "\n";
			}
		}
	}
}