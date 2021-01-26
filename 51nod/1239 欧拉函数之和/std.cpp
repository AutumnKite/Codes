#include <bits/stdc++.h>

const int N = 5000005, M = 2005;
const int P = 1000000007, Inv2 = (P + 1) >> 1;

int cnt, prime[N];
bool vis[N];
int phi[N];
int sum[N];

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
		sum[i] = (sum[i - 1] + phi[i]) % P;
	}
}

long long n;

bool ok[M];
int S[M];

int calc(long long n) {
	if (n < N) {
		return sum[n];
	}
	if (ok[::n / n]) {
		return S[::n / n];
	}
	int res = (n % P) * ((n + 1) % P) % P * Inv2 % P;
	for (long long l = 2, r; l <= n; l = r + 1) {
		long long t = n / l;
		r = n / t;
		res = (res + (r - l + 1) % P * (P - calc(t))) % P;
	}
	ok[::n / n] = true;
	S[::n / n] = res;
	return res;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init();

	std::cin >> n;
	std::cout << calc(n) << "\n";
}