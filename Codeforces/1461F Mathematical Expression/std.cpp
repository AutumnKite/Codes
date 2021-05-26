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
	std::string s;
	std::cin >> s;
	std::sort(s.begin(), s.end());

	if ((int)s.size() == 1 || s == "+-") {
		for (int i = 0; i < n; ++i) {
			std::cout << a[i];
			if (i < n - 1) {
				std::cout << s[0];
			}
		}
		std::cout << "\n";
		return 0;
	}

	s.resize(2);
	if (s == "*-") {
		bool flag = false;
		for (int i = 0; i < n; ++i) {
			std::cout << a[i];
			if (i < n - 1) {
				if (!flag && a[i + 1] == 0) {
					std::cout << "-";
					flag = true;
				} else {
					std::cout << "*";
				}
			}
		}
		std::cout << "\n";
		return 0;
	}
	
}