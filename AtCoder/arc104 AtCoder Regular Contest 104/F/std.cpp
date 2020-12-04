#include <bits/stdc++.h>

const int N = 105, P = 1000000007;

int n;
int a[N];
bool vis[N][N][N];
int f[N][N][N];

int solve(int l, int r, int x) {
	if (x < 0) {
		return 0;
	}
	if (l > r) {
		return 1;
	}
	if (vis[l][r][x]) {
		return f[l][r][x];
	}
	vis[l][r][x] = 1;
	int res = 0;
	for (int i = l; i <= r; ++i) {
		res = (res + 1ll * solve(l, i - 1, std::min(x, a[i])) * solve(i + 1, r, std::min(x, a[i]) - 1)) % P;
	}
	return f[l][r][x] = res;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		a[i] = std::min(a[i], n);
	}

	std::cout << solve(1, n, n) << "\n";
}
