#include <bits/stdc++.h>

const int N = 38, M = 19;
const int P = 998244353;

int qpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = 1ll * s * a % P;
		}
		a = 1ll * a * a % P;
	}
	return s;
}

const int Inv2 = qpow(2, P - 2), Inv = qpow(10000, P - 2);

int n, m;

struct Edge {
	int u, v, w;

	Edge() {}
	Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
} E[M];

int fa[N];
std::vector<int> id[N];

int find(int x) {
	return fa[x] == x ? x : (fa[x] = find(fa[x]));
}

bool merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) {
		return false;
	}
	fa[y] = x;
	return true;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		fa[i] = i;
	}
	for (int i = 0; i < m; ++i) {
		std::cin >> E[i].u >> E[i].v >> E[i].w;
		--E[i].u, --E[i].v;
		E[i].w = 1ll * E[i].w * Inv % P;
		merge(E[i].u, E[i].v);
	}

	for (int i = 0; i < n; ++i) {
		id[find(i)].push_back(i);
	}
	std::vector<int> f(1, 1);
	for (int i = 0; i < n; ++i) {
		if (find(i) == i) {
			std::vector<int> node = id[i];
			std::vector<Edge> edge;
			for (int j = 0; j < m; ++j) {
				if (find(E[j].u) == i) {
					int u = std::lower_bound(node.begin(), node.end(), E[j].u) - node.begin();
					int v = std::lower_bound(node.begin(), node.end(), E[j].v) - node.begin();
					edge.push_back(Edge(u, v, E[j].w));
				}
			}
			int sz = node.size();
			std::vector<int> g(sz + 1);
			for (int S = 0; S < (1 << sz); ++S) {
				int c = 0;
				for (int i = 0; i < sz; ++i) {
					c += S >> i & 1;
				}
				int s = 1;
				for (auto e : edge) {
					if ((S >> e.u & 1) ^ (S >> e.v & 1)) {
						if (S >> e.u & 1) {
							s = 2ll * s * e.w % P;
						} else {
							s = 2ll * s * (P + 1 - e.w) % P;
						}
					}
				}
				g[c] = (g[c] + s) % P;
			}
			std::vector<int> res(f.size() + sz);
			for (int j = 0; j < (int)f.size(); ++j) {
				for (int k = 0; k <= sz; ++k) {
					res[j + k] = (res[j + k] + 1ll * f[j] * g[k]) % P;
				}
			}
			f.swap(res);
		}
	}

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		ans = (ans + 1ll * f[i] * qpow(Inv2, i * (n - i))) % P;
	}
	std::cout << 1ll * ans * qpow(10000, n * (n - 1)) % P << "\n";
}
