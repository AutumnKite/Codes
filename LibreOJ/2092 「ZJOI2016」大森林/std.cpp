#include <bits/stdc++.h>

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
	std::vector<bool> rev;

	std::vector<int> sz, tp;

	void up(int u) {
		sz[u] = tp[u];
		if (son[u][0] != -1) {
			sz[u] += sz[son[u][0]];
		}
		if (son[u][1] != -1) {
			sz[u] += sz[son[u][1]];
		}
	}

	void reverse(int u) {
		if (u != -1) {
			std::swap(son[u][0], son[u][1]);
			rev[u] = !rev[u];
		}
	}

	void down(int u) {
		if (rev[u]) {
			reverse(son[u][0]);
			reverse(son[u][1]);
			rev[u] = false;
		}
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
		up(v), up(u);
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

	void access(int u) {
		int v = -1;
		while (u != -1) {
			splay(u);
			son[u][1] = v;
			up(u);
			v = u, u = fa[u];
		}
	}

	void split(int u, int v) {
		make_root(u);
		access(v);
		splay(v);
	}

public:
	LinkCutTree() : n(0) {}

	void reserve(int _n) {
		fa.reserve(_n), son.reserve(_n);
		rev.reserve(_n);
		sz.reserve(_n), tp.reserve(_n);
	}

	int new_node(int _tp) {
		fa.push_back(-1), son.push_back(Sons());
		rev.push_back(false);
		sz.push_back(_tp), tp.push_back(_tp);
		return n++;
	}

	void make_root(int u) {
		access(u);
		splay(u);
		reverse(u);
	}

	int find_root(int u) {
		access(u);
		splay(u);
		while (son[u][0] != -1) {
			down(u);
			u = son[u][0];
		}
		splay(u);
		return u;
	}
	
	int LCA(int u, int v, int rt) {
		make_root(rt);
		access(v);
		v = -1;
		while (u != -1) {
			splay(u);
			son[u][1] = v;
			up(u);
			v = u, u = fa[u];
		}
		return tp[v];
	}

	void link(int u, int v) {
		make_root(u);
		if (find_root(v) != u) {
			fa[u] = v;
		}
	}

	void cut(int u, int v) {
		make_root(v);
		access(u);
		splay(u);
		fa[son[u][0]] = -1;
		son[u][0] = -1;
		up(u);
	}

	int query(int u, int v) {
		split(u, v);
		return sz[v];
	}
};

struct Oper {
	int id, x, y;

	Oper() {}
	Oper(int _id, int _x, int _y) : id(_id), x(_x), y(_y) {}

	bool operator<(const Oper &rhs) const {
		return id < rhs.id;
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<Oper>> Q(n + 1);
	LinkCutTree T;
	T.reserve(m + 2);
	int qr = 0;
	std::vector<int> L, R, nd;
	L.push_back(0), R.push_back(n), nd.push_back(T.new_node(1));
	int now = T.new_node(0);
	T.link(now, nd.back());
	for (int i = 0; i < m; ++i) {
		int op;
		std::cin >> op;
		if (op == 0) {
			int l, r;
			std::cin >> l >> r;
			--l;
			L.push_back(l), R.push_back(r), nd.push_back(T.new_node(1));
			T.link(nd.back(), now);
		} else if (op == 1) {
			int l, r, x;
			std::cin >> l >> r >> x;
			--l, --x;
			l = std::max(L[x], l);
			r = std::min(R[x], r);
			if (l >= r) {
				continue;
			}
			int t = T.new_node(0);
			T.link(t, now);
			Q[l].push_back(Oper(-1, t, nd[x]));
			Q[r].push_back(Oper(-1, t, now));
			now = t;
		} else {
			int x, u, v;
			std::cin >> x >> u >> v;
			--x, --u, --v;
			Q[x].push_back(Oper(qr++, nd[u], nd[v]));
		}
	}

	std::vector<int> ans(qr);
	for (int i = 0; i < n; ++i) {
		std::sort(Q[i].begin(), Q[i].end());
		for (Oper v : Q[i]) {
			if (v.id == -1) {
				T.cut(v.x, nd[0]);
				T.link(v.x, v.y);
			} else {
				ans[v.id] = T.query(v.x, v.y) - T.LCA(v.x, v.y, nd[0]);
			}
		}
	}

	for (int v : ans) {
		std::cout << v << "\n";
	}
}
/*
100 6
0 3 92
0 50 97
0 70 90
0 68 100
0 16 90
2 82 4 6
*/