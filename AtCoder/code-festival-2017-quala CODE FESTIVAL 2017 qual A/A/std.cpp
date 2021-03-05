#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::string s;
	std::cin >> s;
	if ((int)s.size() >= 4 && s[0] == 'Y' && s[1] == 'A' && s[2] == 'K' && s[3] == 'I') {
		std::cout << "Yes\n";
	} else {
		std::cout << "No\n";
	}
}