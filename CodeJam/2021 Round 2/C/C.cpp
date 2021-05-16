#include <bits/stdc++.h>

const int P = 1000000007;

int qpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = 1ll * s * a % P;
		}
		a = 1ll * a * a % P;
	}
	return s;
}

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> sta;
	std::vector<int> ls(n, -1), rs(n, -1);
	bool flag = true;
	for (int i = 0; i < n; ++i) {
		int v;
		std::cin >> v;
		flag &= (int)sta.size() >= v - 1;
		int nx = -1;
		while ((int)sta.size() >= v) {
			nx = sta.back();
			sta.pop_back();
		}
		ls[i] = nx;
		if (!sta.empty()) {
			rs[sta.back()] = i;
		}
		sta.push_back(i);
	}

	if (!flag) {
		std::cout << 0 << "\n";
		return;
	}

	std::vector<int> fac(n + 1), inv(n + 1);
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	inv[n] = qpow(fac[n], P - 2);
	for (int i = n; i >= 1; --i) {
		inv[i - 1] = 1ll * inv[i] * i % P;
	}

	auto C = [&](int n, int m) -> int {
		if (m < 0 || m > n) {
			return 0;
		}
		return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
	};
	
	std::vector<int> sz(n);

	auto get_sz = [&](int u) {
		if (u == -1) {
			return 0;
		} else {
			return sz[u];
		}
	};

	std::function<int(int)> dfs = [&](int u) -> int {
		if (u == -1) {
			return 1;
		}
		int ans = 1ll * dfs(ls[u]) * dfs(rs[u]) % P;
		sz[u] = get_sz(ls[u]) + get_sz(rs[u]) + 1;
		return 1ll * ans * C(sz[u] - 1, get_sz(ls[u])) % P;
	};

	std::cout << dfs(sta[0]) << "\n";
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