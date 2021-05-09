#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	std::vector<int> a;
	a.push_back(6), a.push_back(10), a.push_back(15);
	int now = 16;
	while (now <= 10000 && (int)a.size() < n) {
		if (now % 6 == 0 || now % 10 == 0 || now % 15 == 0) {
			a.push_back(now);
		}
		++now;
	}
	for (int i = 0; i < n; ++i) {
		std::cout << a[i] << " \n"[i == n - 1];
	}
}
