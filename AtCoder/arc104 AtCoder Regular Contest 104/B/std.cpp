#include <bits/stdc++.h>

int get(char c) {
	if (c == 'A') {
		return 0;
	}
	if (c == 'T') {
		return 1;
	}
	if (c == 'C') {
		return 2;
	}
	if (c == 'G') {
		return 3;
	}
	return -1;
}

int main() {
	int n;
	std::string a;
	std::cin >> n >> a;
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int cnt[4];
		memset(cnt, 0, sizeof cnt);
		for (int j = i; j < n; ++j) {
			++cnt[get(a[j])];
			if (cnt[0] == cnt[1] && cnt[2] == cnt[3]) {
				++ans;
			}
		}
	}
	std::cout << ans << "\n";
}