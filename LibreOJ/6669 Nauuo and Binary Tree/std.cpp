#include <bits/stdc++.h>

int query(int u, int v) {
	std::cout << "? " << u + 1 << " " << v + 1 << std::endl;
	int d;
	std::cin >> d;
	return d;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	
	int n;
	std::cin >> n;
	std::vector<int> d(n), id;
	for (int i = 1; i < n; ++i) {
		d[i] = query(0, i);
		id.push_back(i);
	}
	std::sort(id.begin(), id.end(), [&](int u, int v) {
		return d[u] < d[v];
	});
	std::vector<std::vector<int>> E(n);
	std::vector<int> fa(n, -1);
	std::vector<int> son(n, -1);
	std::vector<int> sz(n, 0);
	sz[0] = 1;
	for (int u : id) {
		int v = 0;
		while (1) {
			int b = v;
			std::vector<int> chain(1, v);
			while (son[b] != -1) {
				b = son[b];
				chain.push_back(b);
			}
			int z = chain[-(query(u, b) - d[u] - d[b]) / 2 - d[v]];
			if ((int)E[z].size() <= 1) {
				E[z].push_back(u);
				fa[u] = z;
				break;
			} else {
				v = E[z][0] ^ E[z][1] ^ son[z];
			}
		}
		v = u;
		while (v != -1) {
			++sz[v];
			if (son[fa[v]] == -1 || sz[v] > sz[son[fa[v]]]) {
				son[fa[v]] = v;
			}
			v = fa[v];
		}
	}
	std::cout << "! ";
	for (int i = 1; i < n; ++i) {
		std::cout << fa[i] + 1 << " ";
	}
	std::cout << std::endl;
}
