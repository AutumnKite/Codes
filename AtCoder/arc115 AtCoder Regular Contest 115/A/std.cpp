#include <bits/stdc++.h>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int t, n;
	std::cin >> t >> n;
	std::vector<bool> vis(100 + t + 1);
	for (int i = 1; i <= 100; ++i) {
		vis[i * (100 + t) / 100] = true;
	}
	int cnt = 0;
	for (int i = 1; i <= 100 + t; ++i) {
		cnt += !vis[i];
	}
	long long ans = 1ll * (n - 1) / cnt * (100 + t);
	n -= (n - 1) / cnt * cnt;
	for (int i = 1; i <= 100 + t && n; ++i) {
		n -= !vis[i];
		++ans;
	}
	std::cout << ans << "\n";
}
