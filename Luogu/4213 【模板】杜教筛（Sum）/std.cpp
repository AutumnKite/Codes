#include <bits/stdc++.h>

const int N = 8000005;

namespace sub1 {
	int cnt, prime[N];
	bool vis[N];
	int phi[N];
	long long sum[N];

	void init() {
		vis[1] = true;
		phi[1] = 1;
		for (int i = 2; i < N; ++i) {
			if (!vis[i]) {
				prime[++cnt] = i;
				phi[i] = i - 1;
			}
			for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
				vis[i * prime[j]] = true;
				if (i % prime[j] == 0) {
					phi[i * prime[j]] = phi[i] * prime[j];
					break;
				} else {
					phi[i * prime[j]] = phi[i] * (prime[j] - 1);
				}
			}
		}
		for (int i = 1; i < N; ++i) {
			sum[i] = sum[i - 1] + phi[i];
		}
	}

	std::unordered_map<unsigned, long long> S;

	long long calc(unsigned n) {
		if (n < N) {
			return sum[n];
		}
		if (S.count(n)) {
			return S[n];
		}
		long long res = 1ll * n * (n + 1) / 2;
		for (unsigned l = 2, r; l <= n; l = r + 1) {
			unsigned t = n / l;
			r = n / t;
			res -= (r - l + 1) * calc(t);
		}
		S[n] = res;
		return res;
	}

	long long solve(unsigned n) {
		return calc(n);
	}
}

namespace sub2 {
	int cnt, prime[N];
	bool vis[N];
	int mu[N];
	int sum[N];

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
		for (int i = 1; i < N; ++i) {
			sum[i] = sum[i - 1] + mu[i];
		}
	}

	std::unordered_map<unsigned, int> S;

	int calc(unsigned n) {
		if (n < N) {
			return sum[n];
		}
		if (S.count(n)) {
			return S[n];
		}
		int res = 1;
		for (unsigned l = 2, r; l <= n; l = r + 1) {
			unsigned t = n / l;
			r = n / t;
			res -= (int)(r - l + 1) * calc(t);
		}
		S[n] = res;
		return res;
	}

	int solve(unsigned n) {
		return calc(n);
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	sub1::init(), sub2::init();

	int T = 1;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		std::cout << sub1::solve(n) << " " << sub2::solve(n) << "\n";
	}
}
