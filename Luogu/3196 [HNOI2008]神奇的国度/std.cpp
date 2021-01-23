#include <bits/stdc++.h>

const int N = 10005;

int n, m;
bool a[N][N];

bool vis[N];
int label[N];

int id[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		std::cin >> u >> v;
		a[u][v] = a[v][u] = true;
	}

	int ans = 0;
	for (int i = n; i; --i) {
		int k = 0;
		for (int j = 1; j <= n; ++j) {
			if (!vis[j] && (!k || label[j] > label[k])) {
				k = j;
			}
		}
		ans = std::max(ans, label[k] + 1);
		vis[k] = true;
		for (int j = 1; j <= n; ++j) {
			if (a[k][j]) {
				++label[j];
			}
		}
	}
	std::cout << ans << "\n";
}