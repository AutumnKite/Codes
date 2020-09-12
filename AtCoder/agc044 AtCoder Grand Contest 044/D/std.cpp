#include <bits/stdc++.h>

int Query(const std::string &a) {
	std::cout << "? " << a << std::endl;
	int x;
	std::cin >> x;
	return x;
}

const char C[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

int L, cnt[62];

std::string solve(int l, int r) {
	if (l + 1 == r) {
		return std::string(cnt[l], C[l]);
	}
	int md = (l + r + 1) >> 1;
	std::string s1(solve(l, md)), s2(solve(md, r));
	std::string s;
	int p1 = 0, p2 = 0;
	while (p1 < (int)s1.size() && p2 < (int)s2.size()) {
		std::string t = s + s1[p1] + std::string(s2.begin() + p2, s2.end());
		if (Query(t) == L - (int)t.size()) {
			s += s1[p1++];
		} else {
			s += s2[p2++];
		}
	}
	while (p1 < (int)s1.size()) {
		s += s1[p1++];
	}
	while (p2 < (int)s2.size()) {
		s += s2[p2++];
	}
	return s;
}

int main() {
	for (int i = 0; i < 62; ++i) {
		cnt[i] = 128 - Query(std::string(128, C[i]));
	}
	for (int i = 0; i < 62; ++i) {
		L += cnt[i];
	}
	std::string ans = solve(0, 62);
	std::cout << "! " << ans << std::endl;
}
