#include <bits/stdc++.h>

bool check(std::string a, std::string b) {
	return a.size() < b.size() || (a.size() == b.size() && a < b);
}

void upd(std::string &a, std::string b) {
	if (check(b, a)) {
		a = b;
	}
}

void solve() {
	std::string s;
	std::cin >> s;
	int len = s.size();
	std::string ans(len + 2, '0');
	for (int r = 2; r <= len + 1; ++r) {
		int d = (len + 1) / r, t = (len + 1) % r;
		if (t) {
			unsigned long long pw = 1;
			for (int i = 0; i < d; ++i) {
				pw *= 10;
			}
			if (pw <= (unsigned long long)(r - t)) {
				continue;
			}
			std::string tmp;
			for (int i = t - r; i < t; ++i) {
				tmp += std::to_string(pw + i);
			}
			upd(ans, tmp);
		} else {
			unsigned long long pw = 1;
			for (int i = 0; i < d - 1; ++i) {
				pw *= 10;
			}
			std::string tmp;
			for (int i = 0; i < r; ++i) {
				tmp += std::to_string(pw + i);
			}
			upd(ans, tmp);
		}
	}
	for (int r = 2; r <= len; ++r) {
		int d = len / r, t = len % r;
		if (t) {
			unsigned long long pw = 1;
			for (int i = 0; i < d; ++i) {
				pw *= 10;
			}
			if (pw <= (unsigned long long)(r - t)) {
				continue;
			}
			std::string tmp;
			for (int i = t - r; i < t; ++i) {
				tmp += std::to_string(pw + i);
			}
			if (check(s, tmp)) {
				upd(ans, tmp);
			}
		} else {
			unsigned long long pw = 0;
			for (int i = 0; i < d; ++i) {
				pw = pw * 10 + s[i] - '0';
			}
			std::string tmp;
			for (int i = 0; i < r; ++i) {
				tmp += std::to_string(pw + i);
			}
			if (check(s, tmp)) {
				upd(ans, tmp);
			}
			tmp.clear();
			for (int i = 1; i <= r; ++i) {
				tmp += std::to_string(pw + i);
			}
			if (check(s, tmp)) {
				upd(ans, tmp);
			}
		}
	}
	std::cout << ans << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int T;
	std::cin >> T;
	for (int test = 1; test <= T; ++test) {
		std::cout << "Case #" << test << ": ";
		solve();
	}
}