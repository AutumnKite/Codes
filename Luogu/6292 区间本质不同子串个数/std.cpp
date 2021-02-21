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
	std::vector<int> len;
	std::vector<std::vector<int>> trans;
	std::vector<int> link;

	SuffixAutomaton(int _C) : C(_C), n(0) {
		cur = new_node(0);
	}

	void add(int c) {
		int p = cur;
		cur = new_node(len[cur] + 1);
		while (p != -1 && trans[p][c] == -1) {
			trans[p][c] = cur;
			p = link[p];
		}
		if (p == -1) {
			link[cur] = 0;
			return;
		}
		int q = trans[p][c];
		if (len[q] == len[p] + 1) {
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
		link[q] = link[cur] = t;
	}
};

class AnswerSeq {
	int n;
	std::vector<long long> c, ci;

	void add(int x, long long v) {
		long long t = v * x;
		for (++x; x <= n; x += x & -x) {
			c[x] += v;
			ci[x] += t;
		}
	}

	long long query(int x) {
		int t = x;
		long long s = 0, si = 0;
		for (; x; x ^= x & -x) {
			s += c[x];
			si += ci[x];
		}
		return s * t - si;
	}

public:
	AnswerSeq(int _n) : n(_n), c(n + 1), ci(n + 1) {}

	void add(int l, int r, long long v) {
		add(l, v), add(r, -v);
	}

	long long query(int l, int r) {
		return query(r) - query(l);
	}
};

class LinkCutTree {
	struct Sons {
		int ls, rs;

		Sons() : ls(-1), rs(-1) {}
		
		int &operator[](int x) {
			if (x == 0) {
				return ls;
			} else {
				return rs;
			}
		}

		const int &operator[](int x) const {
			if (x == 0) {
				return ls;
			} else {
				return rs;
			}
		}
	};

	int n;
	std::vector<int> fa;
	std::vector<Sons> son;
	std::vector<int> las;
	std::vector<int> len;

	void upd_las(int u, int _las) {
		if (u != -1) {
			las[u] = _las;
		}
	}

	void down(int u) {
		upd_las(son[u][0], las[u]);
		upd_las(son[u][1], las[u]);
	}

	bool is_root(int u) {
		return fa[u] == -1 || (son[fa[u]][0] != u && son[fa[u]][1] != u);
	}

	int dir(int u) {
		return son[fa[u]][1] == u;
	}

	void change(int u, int k, int v) {
		if (v != -1) {
			fa[v] = u;
		}
		son[u][k] = v;
	}

	void rotate(int u) {
		int v = fa[u], k = dir(u);
		change(v, k, son[u][k ^ 1]);
		if (!is_root(v)) {
			change(fa[v], dir(v), u);
		} else {
			fa[u] = fa[v];
		}
		change(u, k ^ 1, v);
	}

	void splay(int u) {
		static std::vector<int> sta;
		sta.push_back(u);
		for (int i = u; !is_root(i); i = fa[i]) {
			sta.push_back(fa[i]);
		}
		while (!sta.empty()) {
			down(sta.back());
			sta.pop_back();
		}
		while (!is_root(u)) {
			int v = fa[u];
			if (is_root(v)) {
				rotate(u);
				break;
			}
			if (dir(u) == dir(v)) {
				rotate(v);
			} else {
				rotate(u);
			}
			rotate(u);
		}
	}

public:
	LinkCutTree() {}
	
	LinkCutTree(std::vector<int> _len)
	  : n(_len.size()), fa(n, -1), son(n), las(n, -1), len(_len) {}

	void link(int u, int v) {
		splay(u);
		fa[u] = v;
	}

	void change(int u, int p, AnswerSeq &T) {
		int v = -1;
		while (u != -1) {
			splay(u);
			son[u][1] = v;
			v = u, u = fa[u];
			int l = u == -1 ? -1 : len[u], r = len[v];
			if (las[v] != -1) {
				T.add(las[v] - r, las[v] - l, -1);
			}
			T.add(p - r, p - l, 1);
		}
		upd_las(v, p);
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::string s;
	std::cin >> s;

	int q;
	std::cin >> q;
	std::vector<std::vector<std::pair<int, int>>> Q(s.size());
	for (int i = 0; i < q; ++i) {
		int l, r;
		std::cin >> l >> r;
		--l, --r;
		Q[r].emplace_back(l, i);
	}

	SuffixAutomaton A(26);
	std::vector<int> nd(s.size());
	for (int i = 0; i < (int)s.size(); ++i) {
		A.add(s[i] - 'a');
		nd[i] = A.cur;
	}
	LinkCutTree T(A.len);
	for (int i = 0; i < A.n; ++i) {
		if (A.link[i] != -1) {
			T.link(i, A.link[i]);
		}
	}

	AnswerSeq S(s.size() + 1);
	std::vector<long long> ans(q);
	for (int i = 0; i < (int)s.size(); ++i) {
		T.change(nd[i], i + 1, S);
		for (auto p : Q[i]) {
			ans[p.second] = S.query(p.first, i + 1);
		}
	}

	for (long long v : ans) {
		std::cout << v << "\n";
	}
}