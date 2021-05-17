#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	std::vector<int> l(n), r(n);
	std::vector<std::tuple<int, int, int>> pos;
	for (int i = 0; i < n; ++i) {
		std::cin >> l[i] >> r[i];
		pos.emplace_back(l[i], i, 0);
		pos.emplace_back(r[i], i, 1);
	}
	std::sort(pos.begin(), pos.end());
	std::vector<std::vector<int>> E(n + 1);
	std::vector<int> fa(n + 1);
	int now = n;
	for (auto p : pos) {
		int id = std::get<1>(p), op = std::get<2>(p);
		if (op) {
			now = fa[now];
		} else {
			E[now].push_back(id);
			now = id;
		}
	}

	
}