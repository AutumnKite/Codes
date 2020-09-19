#include <bits/stdc++.h>

#define debug(...) fprintf(stderr, __VA_ARGS__)

int n, ans[200];

bool Query(const std::vector<int> &A) {
	std::cout << "? ";
	for (int v : A) {
		std::cout << v + 1 << " ";
	}
	std::cout << std::endl;
	std::string res;
	std::cin >> res;
	return res == "Red" ? 1 : 0;
}

int getInterval(int l, int r, bool st) {
	if (l + 1 == r) {
		return r;
	}
	int md = (l + r + 1) >> 1;
	std::vector<int> id;
	for (int i = 0; i < n; ++i) {
		id.push_back(md + i);
	}
	if (Query(id) == st) {
		return getInterval(md, r, st);
	} else {
		return getInterval(l, md, st);
	}
}

int main() {
	std::cin >> n;
	std::vector<int> id;
	for (int i = 0; i < n; ++i) {
		id.push_back(i);
	}
	int st = Query(id);
	int p = getInterval(0, n, st);
	id.clear();
	for (int i = 0; i < n - 1; ++i) {
		id.push_back(p + i);
	}
	ans[p - 1] = st, ans[p + n - 1] = !st;
	std::vector<int> nid;
	for (int i = 0; i < 2 * n; ++i) {
		if (i < p - 1 || i >= p + n) {
			id.push_back(i);
			ans[i] = Query(id);
			id.pop_back();
			nid.push_back(i);
		}
	}
	for (int i = p; i < p + n - 1; ++i) {
		nid.push_back(i);
		ans[i] = Query(nid);
		nid.pop_back();
	}
	std::cout << "! ";
	for (int i = 0; i < 2 * n; ++i) {
		std::cout << (ans[i] ? 'R' : 'B');
	}
	std::cout << std::endl;
}