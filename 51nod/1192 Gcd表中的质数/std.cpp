#include <bits/stdc++.h>

const int N = 5000005;

int cnt, prime[N];
bool vis[N];
int mu[N];
int f[N];
long long sum[N];

void init() {
	vis[1] = true;
	mu[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!vis[i]) {
			prime[++cnt] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			} else {
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
	for (int i = 1; i <= cnt; ++i) {
		for (int j = 1; prime[i] * j < N; ++j) {
			f[prime[i] * j] += mu[j];
		}
	}
	for (int i = 1; i < N; ++i) {
		sum[i] = sum[i - 1] + f[i];
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init();
	int T = 1;
	std::cin >> T;
	while (T--) {
		int n, m;
		std::cin >> n >> m;
		std::vector<int> pn, pm;
		for (int l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			pn.push_back(r);
		}
		for (int l = 1, r; l <= m; l = r + 1) {
			r = m / (m / l);
			pm.push_back(r);
		}
		std::vector<int> pos(pn.size() + pm.size());
		std::merge(pn.begin(), pn.end(), pm.begin(), pm.end(), pos.begin());
		pos.erase(std::unique(pos.begin(), pos.end()), pos.end());
		int lst = 0;
		long long ans = 0;
		for (int i : pos) {
			ans += (sum[i] - sum[lst]) * (n / i) * (m / i);
			lst = i;
		}
		std::cout << ans << "\n";
	}
}