#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	int m = *std::max_element(a.begin(), a.end()) + 1;
	std::vector<int> c(m);
	for (int x : a) {
		++c[x];
	}
}