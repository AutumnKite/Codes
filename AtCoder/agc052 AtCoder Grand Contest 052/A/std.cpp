#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int T;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		std::string s1, s2, s3;
		std::cin >> s1 >> s2 >> s3;
		for (int i = 0; i < n; ++i) {
			std::cout << '0';
		}
		for (int i = 0; i < n; ++i) {
			std::cout << '1';
		}
		std::cout << '0';
		std::cout << "\n";
	}
}