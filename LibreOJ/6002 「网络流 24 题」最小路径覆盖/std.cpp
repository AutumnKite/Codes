#include <bits/stdc++.h>

const int N = 205;

int n, m;
std::vector<int> E[N];

int match[N];
bool vis[N];

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

int nxt[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		std::cin >> u >> v;
		E[u].push_back(v);
	}

	int ans = n;
	std::fill(match + 1, match + 1 + n, -1);
	for (int i = 1; i <= n; ++i) {
		std::fill(vis + 1, vis + 1 + n, false);
		if (find(i)) {
			--ans;
		}
	}
	
	std::fill(nxt + 1, nxt + 1 + n, -1);
	for (int i = 1; i <= n; ++i) {
		nxt[match[i]] = i;
	}
	for (int i = 1; i <= n; ++i) {
		if (match[i] == -1) {
			for (int j = i; j != -1; j = nxt[j]) {
				std::cout << j << " ";
			}
			std::cout << "\n";
		}
	}
	std::cout << ans << "\n";
}