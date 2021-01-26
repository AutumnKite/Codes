#include <bits/stdc++.h>

const int N = 5000005, P = 1000000007;

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

long long calc(long long n) {
	if (n < N) {
		return sum[n];
	}
	long long res = n * (n )
	for (long long l = 1, r; l <= n; l = r + 1) {
		r = n / (n / l);

	}
}