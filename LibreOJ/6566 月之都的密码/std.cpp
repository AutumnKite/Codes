#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);

	int n, T;
	std::cin >> n >> T;
	std::vector<int> ans(n);
	for (int k = 0; (1 << k) < n; ++k) {
		std::vector<int> p;
		for (int i = 0; i < n; ++i) {
			if ((i >> k & 1)) {
				p.push_back(i);
			}
		}
		std::cout << "encode " << p.size();
		for (int i : p) {
			std::cout << " " << i + 1;
		}
		std::cout << std::endl;
		for (int i = 0; i < (int)p.size(); ++i) {
			int x;
			std::cin >> x;
			--x;
			ans[x] |= 1 << k;
		}
	}
	std::cout << "submit";
	for (int i = 0; i < n; ++i) {
		std::cout << " " << ans[i] + 1;
	}
	std::cout << std::endl;
}