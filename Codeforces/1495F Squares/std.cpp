#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, q;
	std::cin >> n >> q;
	std::vector<int> p(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> p[i];
		--p[i];
	}

	std::vector<int> sta;
	sta.push_back(n);
	for (int i = 0; i < n; ++i) {
		while ((int)sta.size() > 1 && p[sta.back()] > p[i]) {
			sta.pop_back();
		}
		
	}
}