#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	int lst = 0;
	int res = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		std::cin >> x;
		int c = (x & -x) != x;
		int k = 0;
		while (x > 1) {
			x >>= 1;
			++k;
		}
		res += k + c;
		int t = std::min(k, lst);
		lst -= t;
		res -= t;
		if (lst && c) {
			--res;
			--c;
		}
		lst = k + c;
	}
	std::cout << res << "\n";
}