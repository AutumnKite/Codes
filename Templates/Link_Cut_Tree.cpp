#include <bits/stdc++.h>

const int N = 300005;

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

	std::vector<int> a, val;

	void up(int u) {
		val[u] = a[u];
		if (son[u][0] != -1) {
			val[u] ^= val[son[u][0]];
		}
		if (son[u][1] != -1) {
			val[u] ^= val[son[u][1]];
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
	LinkCutTree() {}
	
	LinkCutTree(std::vector<int> A)
	  : n(A.size()), fa(n, -1), son(n), rev(n, false), a(A), val(A) {}

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

	void link(int u, int v) {
		make_root(u);
		if (find_root(v) != u) {
			fa[u] = v;
		}
	}

	void cut(int u, int v) {
		make_root(u);
		if (find_root(v) == u && fa[v] == u && son[v][0] == -1) {
			son[u][1] = fa[v] = -1;
			up(u);
		}
	}

	int query(int u, int v) {
		split(u, v);
		return val[v];
	}

	void modify(int u, int _a) {
		splay(u);
		a[u] = _a;
		up(u);
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, q;
	std::cin >> n >> q;
	std::vector<int> a(n);
	for (int &v : a) {
		std::cin >> v;
	}
	
	LinkCutTree T(a);
	while (q--) {
		int op;
		std::cin >> op;
		if (op == 3) {
			int x, v;
			std::cin >> x >> v;
			--x;
			T.modify(x, v);
		} else {
			int x, y;
			std::cin >> x >> y;
			--x, --y;
			if (op == 0) {
				std::cout << T.query(x, y) << "\n";
			} else if (op == 1) {
				T.link(x, y);
			} else if (op == 2) {
				T.cut(x, y);
			}
		}
	}
}