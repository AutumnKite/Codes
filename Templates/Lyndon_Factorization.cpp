#include <bits/stdc++.h>

std::vector<int> lyndon_fact(std::string s) {
	std::vector<int> res;
	int n = s.size();
	int i = 0;
	while (i < n) {
		int j = i, k = i + 1;
		while (j < n && s[j] <= s[k]) {
			if (s[j] < s[k]) {
				j = i;
			} else {
				++j;
			}
			++k;
		}
		while (i <= j) {
			res.push_back(i + k - j);
			i += k - j;
		}
	}
	return res;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::string s;
	std::cin >> s;
	
	std::vector<int> p(lyndon_fact(s));
	int ans = 0;
	for (int v : p) {
		ans ^= v;
	}
	std::cout << ans << "\n";
}