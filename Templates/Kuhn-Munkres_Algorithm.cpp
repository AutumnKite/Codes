#include <bits/stdc++.h>

template <class Tp>
class Bigraph {
	const Tp INF = std::numeric_limits<Tp>::max();

	int n;
	std::vector<std::vector<Tp>> E;
	std::vector<Tp> a, b;
	std::vector<int> p;

	void bfs(int x) {
		std::vector<bool> vis(n + 1, false);
		std::vector<Tp> d(n + 1, INF);
		std::vector<int> pre(n + 1, -1);
		p[0] = x;
		int u = 0, v = 0;
		while (p[v]) {
			u = p[v];
			vis[v] = true;
			Tp c = INF;
			int nxt = 0;
			for (int i = 1; i <= n; ++i) {
				if (!vis[i]) {
					Tp val = a[u] + b[i] - E[u - 1][i - 1];
					if (val < d[i]) {
						d[i] = val;
						pre[i] = v;
					}
					if (d[i] < c) {
						c = d[i];
						nxt = i;
					}
				}
			}
			for (int i = 0; i <= n; ++i) {
				if (vis[i]) {
					a[p[i]] -= c;
					b[i] += c;
				} else {
					d[i] -= c;
				}
			}
			v = nxt;
		}
		while (v) {
			p[v] = p[pre[v]];
			v = pre[v];
		}
	}

public:
	Bigraph(int _n, std::vector<std::vector<Tp>> _E) : n(_n), E(_E), a(_n + 1), b(_n + 1), p(_n + 1) {}

	std::vector<int> match() {
		for (int i = 1; i <= n; ++i) {
			a[i] = *std::max_element(E[i - 1].begin(), E[i - 1].end());
			b[i] = 0;
			p[i] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			bfs(i);
		}
		std::vector<int> res(n);
		for (int i = 1; i <= n; ++i) {
			res[i - 1] = p[i] - 1;
		}
		return res;
	}
};
