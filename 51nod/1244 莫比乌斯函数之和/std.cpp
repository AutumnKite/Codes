#include <bits/stdc++.h>

const int N = 5000005, M = 2005;

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

long long n;

bool ok[M];
long long S[M];

long long calc(long long n) {
	if (n < N) {
		return sum[n];
	}
	if (ok[::n / n]) {
		return S[::n / n];
	}
	long long res = 1;
	for (long long l = 2, r; l <= n; l = r + 1) {
		long long t = n / l;
		r = n / t;
		res -= (r - l + 1) * calc(t);
	}
	ok[::n / n] = true;
	S[::n / n] = res;
	return res;
}

long long solve(long long _n) {
	n = _n;
	for (int i = 1; i <= n / N; ++i) {
		ok[i] = false;
	}
	return calc(n);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init();

	long long a, b;
	std::cin >> a >> b;
	std::cout << solve(b) - solve(a - 1) << "\n";
}
