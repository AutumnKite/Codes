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
		link[t] = q;
		trans[t] = trans[q];
		while (p != -1 && trans[p][c] == q) {
			trans[p][c] = t;
			p = link[p];
		}
		link[cur] = link[q] = t;
	}
};