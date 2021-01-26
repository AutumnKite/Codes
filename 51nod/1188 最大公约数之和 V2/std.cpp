#include <bits/stdc++.h>

const int N = 5000005;

int n;

int cnt, prime[N];
bool vis[N];
int phi[N];
long long f[N];

void init(int n) {
	vis[1] = true;
	phi[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) {
			prime[++cnt] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			} else {
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n / i; ++j) {
			f[i * j] += phi[i] * j;
		}
	}
	for (int i = 1; i <= n; ++i) {
		f[i] += f[i - 1];
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init(5000000);
	int T = 1;
	std::cin >> T;
	while (T--) {
		int n;
		std::cin >> n;
		std::cout << f[n] - 1ll * n * (n + 1) / 2 << "\n";
	}
}