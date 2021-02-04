#include <bits/stdc++.h>

int n;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cout.setf(std::ios::fixed);
	std::cout.precision(10);

	std::cin >> n;
	long double ans = 0;
	for (int i = 1; i <= n; ++i) {
		long double R;
		std::cin >> R;
		ans += R * R / 2;
	}

	std::cout << ans << "\n";
}
