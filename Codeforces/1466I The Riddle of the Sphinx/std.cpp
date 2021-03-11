#include <bits/stdc++.h>

int n, b;

std::vector<int> cur;

bool query(int p) {
	std::cout << p + 1 << " ";
	for (int i = 0; i < (int)cur.size(); ++i) {
		std::cout << cur[i];
	}
	for (int i = (int)cur.size(); i < b; ++i) {
		std::cout << "1";
	}
	std::cout << std::endl;
	std::string str;
	std::cin >> str;
	return str == "yes";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> b;
	std::vector<int> now;
	for (int i = 0; i < n; ++i) {
		now.push_back(i);
	}
	while ((int)cur.size() < b) {
		std::vector<int> sta;
		for (int i : now) {
			while (!sta.empty() && query(i)) {
				sta.pop_back();
				cur.pop_back();
			}
			
		}
	}
}