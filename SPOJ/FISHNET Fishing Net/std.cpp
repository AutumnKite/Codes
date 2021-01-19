#include <bits/stdc++.h>

const int N = 1005;

int n, m;
bool a[N][N];

bool vis[N];
int label[N];

int id[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	while (1) {
		std::cin >> n >> m;
		if (n == 0 && m == 0) {
			break;
		}
		for (int i = 1; i <= n; ++i) {
			vis[i] = false;
			label[i] = 0;
			for (int j = 1; j <= n; ++j) {
				a[i][j] = false;
			}
		}
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
			vis[k] = true;
			id[i] = k;
			for (int j = 1; j <= n; ++j) {
				if (a[k][j]) {
					++label[j];
				}
			}
		}
		bool flag = true;
		for (int i = n; i; --i) {
			std::vector<int> v;
			for (int j = i + 1; j <= n; ++j) {
				if (a[id[i]][id[j]]) {
					v.push_back(id[j]);
				}
			}
			if ((int)v.size() >= 2) {
				for (int j = 1; j < (int)v.size(); ++j) {
					if (!a[v[0]][v[j]]) {
						flag = false;
						break;
					}
				}
				if (!flag) {
					break;
				}
			}
		}
		if (flag) {
			std::cout << "Perfect\n\n";
		} else {
			std::cout << "Imperfect\n\n";
		}
	}
}