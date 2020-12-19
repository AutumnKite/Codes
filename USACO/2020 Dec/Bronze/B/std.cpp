#include <bits/stdc++.h>

int n, a[105];

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		int s = 0;
		for (int j = i; j <= n; ++j) {
			s += a[j];
			bool flag = 0;
			for (int k = i; k <= j; ++k) {
				if (a[k] * (j - i + 1) == s) {
					flag = 1;
					break;
				}
			}
			ans += flag;
		}
	}
	std::cout << ans << "\n";
}