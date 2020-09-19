#include <bits/stdc++.h>

int n;
std::string s[55], x;
int t[55], ans;

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> s[i] >> t[i];
	}
	std::cin >> x;
	int k = 1;
	while (s[k] != x) {
		++k;
	}
	for (int i = k + 1; i <= n; ++i) {
		ans += t[i];
	}
	std::cout << ans << std::endl;
}