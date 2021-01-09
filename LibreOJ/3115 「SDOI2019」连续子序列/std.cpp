#include <bits/stdc++.h>

typedef std::pair<std::string, long long> State;

const int P = 1000000009;

std::map<State, int> f;

int solve(std::string s, long long k) {
	if ((int)s.size() == 1) {
		if (k == 0) {
			return 1;
		} else if (k == 1) {
			return 2;
		} else if (k == 2) {
			return 3;
		}
	}
	if ((int)s.size() == 2) {
		if (k == 0) {
			return 1;
		} else if (k == 1) {
			return s[0] != s[1] ? 2 : 1;
		}
	}
	if ((int)s.size() == 3) {
		if (k == 0) {
			return s[0] != s[1] || s[1] != s[2];
		}
	}
	State st(s, k);
	if (f.count(st)) {
		return f[st];
	}
	int ans = 0;
	for (int r = 0; r < 2 && r <= (int)s.size(); ++r) {
		std::string ne;
		bool flag = 1;
		int p = 0;
		if (p < r) {
			ne += s[p] ^ 1;
			++p;
		}
		while (p < (int)s.size()) {
			if (p + 1 < (int)s.size() && s[p] == s[p + 1]) {
				flag = false;
				break;
			}
			ne += s[p];
			p += 2;
		}
		if (flag) {
			p -= (int)s.size();
			ans += solve(ne, (k - p + 1) / 2);
		}
	}
	return f[st] = ans % P;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int T = 1;
	std::cin >> T;
	while (T--) {
		std::string s;
		long long k;
		std::cin >> s >> k;
		std::cout << solve(s, k) << "\n";
	}
}