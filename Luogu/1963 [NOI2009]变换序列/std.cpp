#include <bits/stdc++.h>

const int N = 10005;

int n, d[N];
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

int ans[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> d[i];
	}
	for (int i = 0; i < n; ++i) {
		if (d[i] > n / 2) {
			std::cout << "No Answer\n";
			return 0;
		}
		E[i].push_back((i + n - d[i]) % n);
		E[i].push_back((i + d[i]) % n);
		std::sort(E[i].begin(), E[i].end());
		E[i].erase(std::unique(E[i].begin(), E[i].end()), E[i].end());
		match[i] = -1;
	}

	for (int u = n - 1; ~u; --u) {
		for (int v = 0; v < n; ++v) {
			vis[v] = false;
		}
		if (!find(u)) {
			std::cout << "No Answer\n";
			return 0;
		}
	}
	for (int i = 0; i < n; ++i) {
		ans[match[i]] = i;
	}
	for (int i = 0; i < n; ++i) {
		std::cout << ans[i] << " \n"[i == n - 1];
	}
}