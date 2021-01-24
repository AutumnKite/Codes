#include <bits/stdc++.h>

const int N = 2005;

int n;
bool E[N][N];

int idx, dfn[N], low[N];
int top, sta[N];
bool vis[N];

int cnt, bel[N];
std::vector<int> scc[N];

void tarjan(int u) {
	dfn[u] = low[u] = idx++;
	sta[top++] = u, vis[u] = true;
	for (int v = 0; v < n; ++v) {
		if (E[u][v]) {
			if (dfn[v] == -1) {
				tarjan(v);
				low[u] = std::min(low[u], low[v]);
			} else if (vis[v]) {
				low[u] = std::min(low[u], dfn[v]);
			}
		}
	}
	if (dfn[u] == low[u]) {
		int v;
		do {
			v = sta[--top];
			vis[v] = false;
			bel[v] = cnt;
			scc[cnt].push_back(v);
		} while (u != v);
		++cnt;
	}
}

std::vector<int> solve(std::vector<int> v) {
	if ((int)v.size() == 1) {
		return v;
	}
	std::vector<int> h;
	for (int u : v) {
		h.insert(std::find_if(h.begin(), h.end(), [&](int x) {
			return E[u][x];
		}), u);
	}
	auto it = std::find_if(h.begin(), h.end(), [&](int x) {
		return E[x][h[0]];
	}) + 1;
	std::vector<int> c(h.begin(), it);
	while (it != h.end()) {
		auto r = it;
		while (std::find_if(c.begin(), c.end(), [&](int x) {
			return E[*r][x];
		}) == c.end()) {
			++r;
		}
		auto p = c.begin();
		while (p + 1 != c.end() && !(E[*p][*it] && E[*r][*(p + 1)])) {
			++p;
		}
		c.insert(p == c.end() ? c.begin() : p + 1, it, r + 1);
		it = r + 1;
	}
	return c;
}

std::vector<int> ans[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			std::cin >> E[j][i];
			E[i][j] = E[j][i] ^ 1;
		}
	}

	for (int i = 0; i < n; ++i) {
		dfn[i] = -1;
	}
	for (int i = 0; i < n; ++i) {
		if (dfn[i] == -1) {
			tarjan(i);
		}
	}

	for (int i = 0; i < cnt; ++i) {
		int len = scc[i].size();
		scc[i] = solve(scc[i]);
		for (int j = 0; j < len; ++j) {
			int u = scc[i][j];
			for (int k = 0; k < len; ++k) {
				ans[u].push_back(scc[i][(j + k) % len]);
			}
			for (int k = i - 1; k >= 0; --k) {
				ans[u].insert(ans[u].end(), scc[k].begin(), scc[k].end());
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		std::cout << ans[i].size() << " ";
		for (int u : ans[i]) {
			std::cout << u + 1 << " ";
		}
		std::cout << "\n";
	}
}