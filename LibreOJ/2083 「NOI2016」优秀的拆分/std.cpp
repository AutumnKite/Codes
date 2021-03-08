#include <bits/stdc++.h>

class SuffixAutomaton {
	int new_node(int _len) {
		len.push_back(_len);
		trans.push_back(std::vector<int>(C, -1));
		link.push_back(-1);
		return n++;
	}

public:
	const int C;

	int n, cur;
	std::vector<std::vector<int>> trans;
	std::vector<int> len;
	std::vector<int> link;

	SuffixAutomaton(int _C) : C(_C), n(0) {
		cur = new_node(0);
	}

	void reserve(int _n) {
		trans.reserve(_n * 2);
		len.reserve(_n * 2);
		link.reserve(_n * 2);
	}

	void add(int c) {
		int p = cur;
		cur = new_node(len[p] + 1);
		while (p != -1 && trans[p][c] == -1) {
			trans[p][c] = cur;
			p = link[p];
		}
		if (p == -1) {
			link[cur] = 0;
			return;
		}
		int q = trans[p][c];
		if (len[p] + 1 == len[q]) {
			link[cur] = q;
			return;
		}
		int t = new_node(len[p] + 1);
		link[t] = link[q];
		trans[t] = trans[q];
		while (p != -1 && trans[p][c] == q) {
			trans[p][c] = t;
			p = link[p];
		}
		link[cur] = link[q] = t;
	}
};

class Tree {
	std::vector<std::vector<int>> E;
	std::vector<int> dep;
	std::vector<std::vector<int>> id;
	std::vector<int> dfn;

	void dfs(int u) {
		dfn[u] = id[0].size();
		id[0].push_back(u);
		for (int v : E[u]) {
			dep[v] = dep[u] + 1;
			dfs(v);
			id[0].push_back(u);
		}
	}

	std::vector<int> Log;

	int min(int x, int y) {
		return dep[x] < dep[y] ? x : y;
	}

public:
	Tree(int n) : E(n), dep(n), id(1), dfn(n) {}

	void add_edge(int fa, int u) {
		E[fa].push_back(u);
	}

	void init() {
		dfs(0);
		Log.resize(id[0].size() + 1);
		Log[1] = 0;
		for (int i = 2; i <= (int)id[0].size(); ++i) {
			Log[i] = Log[i >> 1] + 1;
		}
		id.resize(Log[id[0].size()] + 1);
		for (int i = 1; i <= Log[id[0].size()]; ++i) {
			id[i].resize(id[0].size() - (1 << i) + 1);
			for (int j = 0; j + (1 << i) <= (int)id[0].size(); ++j) {
				id[i][j] = min(id[i - 1][j], id[i - 1][j + (1 << (i - 1))]);
			}
		}
	}

	int LCA(int x, int y) {
		x = dfn[x], y = dfn[y];
		if (x > y) {
			std::swap(x, y);
		}
		int t = Log[y - x + 1];
		return min(id[t][x], id[t][y - (1 << t) + 1]);
	}
};

void solve() {
	std::string s;
	std::cin >> s;
	int n = s.size();
	SuffixAutomaton S(26), T(26);
	std::vector<int> pre(n), suf(n);
	for (int i = 0; i < n; ++i) {
		S.add(s[i] - 'a');
		pre[i] = S.cur;
	}
	for (int i = n - 1; ~i; --i) {
		T.add(s[i] - 'a');
		suf[i] = T.cur;
	}

	Tree St(S.n), Tt(T.n);
	for (int i = 1; i < S.n; ++i) {
		St.add_edge(S.link[i], i);
	}
	for (int i = 1; i < T.n; ++i) {
		Tt.add_edge(T.link[i], i);
	}
	St.init(), Tt.init();

	std::vector<int> A(n), B(n);
	for (int l = 1; l <= n / 2; ++l) {
		for (int i = l; i + l <= n; i += l) {
			int t1 = S.len[St.LCA(pre[i - 1], pre[i + l - 1])];
			int t2 = i + l == n ? 0 : T.len[Tt.LCA(suf[i], suf[i + l])];
			if (t1 + t2 < l) {
				continue;
			}
			t1 = std::min(t1, l), t2 = std::min(t2 + 1, l);
			++A[i - t1];
			--A[i - l + t2];
			if (i + l + l - t1 < n) {
				++B[i + l + l - t1];
				if (i + l + t2 < n) {
					--B[i + l + t2];
				}
			}
		}
	}
	long long ans = 0;
	for (int i = 1; i < n; ++i) {
		A[i] += A[i - 1];
		B[i] += B[i - 1];
		ans += 1ll * A[i] * B[i];
	}
	std::cout << ans << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int T;
	std::cin >> T;
	while (T--) {
		solve();
	}
}