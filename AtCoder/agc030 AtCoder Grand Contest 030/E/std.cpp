#include <bits/stdc++.h>

const int N = 5005, INF = 0x3f3f3f3f;

int n;
char s[N], t[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	std::cin >> n;
	std::cin >> (s + 1);
	std::cin >> (t + 1);

	std::vector<int> ps(n, 0), pt(n, 0);
	if (s[1] != t[1]) {
		pt.push_back(0);
	}
	for (int i = 1; i < n; ++i) {
		if (s[i] != s[i + 1]) {
			ps.push_back(i);
		}
		if (t[i] != t[i + 1]) {
			pt.push_back(i);
		}
	}
	int m = std::max(ps.size(), pt.size()) + n;
	while ((int)ps.size() < m) {
		ps.push_back(n);
	}
	while ((int)pt.size() < m) {
		pt.push_back(n);
	}
	int ans = INF;
	for (int i = -n; i <= n; ++i) {
		if (!(i & 1)) {
			int s = 0;
			for (int j = std::max(0, -i); j < std::min(m, m - i); ++j) {
				s += abs(ps[j] - pt[i + j]);
			}
			ans = std::min(ans, s);
		}
	}
	std::cout << ans << std::endl;
}
