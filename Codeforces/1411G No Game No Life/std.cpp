#include <bits/stdc++.h>

const int P = 998244353;

int enlarge(int n) {
	int res = 1;
	while (res < n) {
		res <<= 1;
	}
	return res;
}

typedef std::vector<std::vector<int>> matrix;

std::vector<int> Gauss(matrix a, std::vector<int> b) {

}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> E(n);
	std::vector<int> deg(n);
	for (int i = 0; i < m; ++i) {
		int u, v;
		std::cin >> u >> v;
		--u, --v;
		E[u].push_back(v);
		++deg[v];
	}
	
	std::vector<int> Q;
	for (int i = 0; i < n; ++i) {
		if (!deg[i]) {
			Q.push_back(i);
		}
	}
	for (int i = 0; i < (int)Q.size(); ++i) {
		int u = Q[i];
		for (int v : E[u]) {
			--deg[v];
			if (!deg[v]) {
				Q.push_back(v);
			}
		}
	}

	std::reverse(Q.begin(), Q.end());
	std::vector<int> vis(n, -1);
	std::vector<int> SG(n);
	int mx = 0;
	for (int u : Q) {
		for (int v : E[u]) {
			vis[v] = u;
		}
		SG[u] = 0;
		while (vis[SG[u]] == u) {
			++SG[u];
		}
		mx = std::max(mx, SG[u]);
	}
	mx = enlarge(mx + 1);
	std::vector<int> cnt(mx);
	for (int i = 0; i < n; ++i) {
		++cnt[SG[i]];
	}

	matrix A(mx, std::vector<int>(mx));
	std::vector<int> b(mx);
	for (int i = 0; i < mx; ++i) {
		
	}
}