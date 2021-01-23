#include <bits/stdc++.h>

const int N = 205;

int n, m;
bool a[N][N];

bool vis[N];
int label[N];

int id[N];

bool used[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		std::cin >> u >> v;
		a[u][v] = a[v][u] = true;
	}

	for (int i = n; i; --i) {
		int k = 0;
		for (int j = 1; j <= n; ++j) {
			if (!vis[j] && (!k || label[j] > label[k])) {
				k = j;
			}
		}
		id[i] = k;
		vis[k] = true;
		for (int j = 1; j <= n; ++j) {
			if (a[k][j]) {
				++label[j];
			}
		}
	}

	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		used[i] = true;
		for (int j = 1; j < i; ++j) {
			if (used[j] && a[id[i]][id[j]]) {
				used[i] = false;
			}
		}
		ans += used[i];
	}
	std::cout << ans << "\n";
}