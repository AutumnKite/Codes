#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

std::vector<int> part(std::string s) {
	std::vector<int> res;
	int cnt = 0;
	for (int i = 0; i < (int)s.size(); ++i) {
		++cnt;
		if (i + 1 == (int)s.size() || s[i] != s[i + 1]) {
			res.push_back(cnt);
			cnt = 0;
		}
	}
	return res;
}

void solve() {
	std::string s, t;
	std::cin >> s >> t;
	std::vector<int> a(part(s)), b(part(t));
	if (s == "0" && t == "0") {
		std::cout << 0 << "\n";
		return;
	}
	if (t == "0") {
		std::cout << a.size() << "\n";
		return;
	}
	int ans = INF;
	int sum = a.size() + t.size();
	if (a.size() & 1) {
		if (a.size() + 1 >= b.size()) {
			ans = std::min(ans, sum);
		}
	} else {
		if (a.size() >= b.size()) {
			ans = std::min(ans, sum);
		}
	}
	for (int i = 0; i < (int)a.size() && i < (int)b.size(); ++i) {
		bool flag = true;
		for (int j = 0; j < i; ++j) {
			flag &= a[a.size() - i - 1 + j] == b[j];
		}
		flag &= a.back() <= b[i];
		if (!flag) {
			continue;
		}
		if (a.back() == b[i]) {
			if (a.size() & 1) {
				flag &= a.size() + 1 >= b.size();
			} else {
				flag &= a.size() >= b.size();
			}
		} else {
			if (a.size() & 1) {
				flag &= a.size() >= b.size() + 1;
			} else {
				flag &= a.size() >= b.size();
			}
		}
		if (flag) {
			int sum = t.size();
			for (int j = 0; j <= i; ++j) {
				sum -= a[a.size() - j - 1];
			}
			sum += a.size() - i - 1;
			ans = std::min(ans, sum);
		}
	}
	if (s == "0") {
		++ans;
	}
	if (ans >= INF) {
		std::cout << "IMPOSSIBLE\n";
	} else {
		std::cout << ans << "\n";
	}
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