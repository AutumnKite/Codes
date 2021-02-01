#include <bits/stdc++.h>

const int N = 100005, M = 10000005, P = 1000000007;

int n;
int a[N];

int cnt, prime[M];
bool vis[M];
int minp[M];

int inv[M], ans[M];

void init() {
	vis[1] = true;
	for (int i = 2; i < M; ++i) {
		if (!vis[i]) {
			prime[++cnt] = i;
			vis[i] = true;
			minp[i] = i;
		}
		for (int j = 1; j <= cnt && i * prime[j] < M; ++j) {
			vis[i * prime[j]] = true;
			minp[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) {
				break;
			}
		}
	}
	inv[1] = 1;
	for (int i = 2; i < M; ++i) {
		inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
		ans[i] = 1;
	}
}

void work(int n) {
	std::vector<std::pair<int, int>> p;
	while (n > 1) {
		if (!p.empty() && minp[n] == p.back().first) {
			++p.back().second;
		} else {
			p.emplace_back(minp[n], 1);
		}
		n /= minp[n];
	}
	for (auto v : p) {
		int sum = 0, pw = 1;
		for (int i = 0; i <= v.second; ++i) {
			sum = (sum + pw) % P;
			pw = 1ll * pw * v.first % P;
		}
		ans[v.first] = 1ll * ans[v.first] * sum % P;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init();

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		work(a[i]);
	}

	int sum = 1;
	for (int i = 1; i <= cnt; ++i) {
		sum = 1ll * (1ll * (prime[i] - 1) * inv[prime[i]] % P * (ans[prime[i]] + P - 1) + 1) % P * sum % P;
	}
	std::cout << sum << "\n";
}