#include <bits/stdc++.h>

class PQ_tree {
	struct node {
		std::vector<node *> son;
		int type, op;

		node(int tp) : son(), type(tp), op(0) {}
	};

	int n;

	node *rt;
	std::vector<node *> p;

	PQ_tree(int _n) : n(_n), rt(new node(0)), p(n) {
		for (int i = 0; i < n; ++i) {
			p[i] = new node(0);
			rt->son.push_back(p[i]);
		}
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	int n, m;
	std::cin >> n >> m;

}
