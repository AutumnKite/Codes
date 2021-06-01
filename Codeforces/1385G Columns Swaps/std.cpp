#include <bits/stdc++.h>

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n), b(n);
	std::vector<std::vector<int>> E(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
		--a[i];
	}
	for (int i = 0; i < n; ++i) {
		std::cin >> b[i];
		--b[i];
	}
	std::vector<int> d(n);
	for (int i = 0; i < n; ++i) {
		E[a[i]].push_back(b[i]);
		E[b[i]].push_back(a[i]);
		++d[a[i]], --d[b[i]];
	}
	for (int i = 0; i < n; ++i) {
		if ((int)E[i].size() != 2) {
			std::cout << -1 << "\n";
			return;
		}
		d[i] /= 2;
	}
	
	std::vector<bool> vis(n);
	for (int i = 0; i < n; ++i) {
		if (!vis[i]) {
			int lst = E[i][1];
			for (int j = i; !vis[j]; j = E[j][0]) {
				E[i].erase(std::find(E[i].begin(), E[i].end(), lst));
				
			}
		}
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

}
