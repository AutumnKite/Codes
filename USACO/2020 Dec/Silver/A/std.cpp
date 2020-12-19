#include <bits/stdc++.h>

const int N = 100005;

int n;
std::vector<int> E[N];
int ans;

void dfs(int u, int fa) {
	int d = 1;
	for (int v : E[u]) {
		if (v != fa) {
			dfs(v, u);
			++d;
			++ans;
		}
	}
	int w = 1;
	while (w < d) {
		w *= 2;
		++ans;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		E[u].push_back(v), E[v].push_back(u);
	}
	dfs(1, 0);
	std::cout << ans << "\n";
}