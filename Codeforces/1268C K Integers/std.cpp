#include <bits/stdc++.h>

class set {
	std::priority_queue<int> Q;
	std::priority_queue<int, std::vector<int>, std::greater<int>> R;
	long long sumQ, sumR;

	void shift() {
		while (Q.size() < R.size()) {
			Q.push(R.top());
			R.pop();
		}
	}

public:
	set() : sumQ(0), sumR(0) {}

	void insert(int x) {
		if (!Q.empty() && x < Q.top()) {
			R.push(Q.top());
			Q.pop();
			Q.push(x);
		} else {
			R.push(x);
		}
		shift();
	}

	int get_ans() {
		return 
	}
};