#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	int n, m;
	std::cin >> n >> m;
	std::vector<int> fa(n), d(n), dep(n);
	fa[0] = -1, dep[0] = 0;
	for (int i = 1; i < n; ++i) {
		std::cin >> fa[i];
		--fa[i];
		++d[fa[i]];
		dep[i] = dep[fa[i]] + 1;
	}

	std::priority_queue<std::pair<int, int>> Q;
	for (int i = 0; i < n; ++i) {
		if (!d[i]) {
			Q.emplace(dep[i], i);
		}
	}
	std::vector<std::vector<int>> ans;
	while (!Q.empty()) {
		std::vector<int> tmp;
		while ((int)tmp.size() < m && !Q.empty()) {
			tmp.push_back(Q.top().second);
			Q.pop();
		}
		for (int u : tmp) {
			if (fa[u] != -1) {
				--d[fa[u]];
				if (!d[fa[u]]) {
					Q.emplace(dep[fa[u]], fa[u]);
				}
			}
		}
		ans.push_back(tmp);
	}
	std::reverse(ans.begin(), ans.end());
	std::cout << ans.size() << "\n";
	for (const auto &v : ans) {
		std::cout << v.size() << " ";
		for (int u : v) {
			std::cout << u + 1 << " ";
		}
		std::cout << "\n";
	}
}
