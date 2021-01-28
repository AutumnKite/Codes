#include <bits/stdc++.h>

const int N = 5000005, M = 2005;
const int P = 1000000007, Inv2 = 500000004, Inv6 = 166666668;

int cnt, prime[N];
bool vis[N];
int f[N];
int sum[N];

void init() {
	vis[1] = true;
	f[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!vis[i]) {
			prime[++cnt] = i;
			f[i] = (i - 1ll * i * i) % P;
		}
		for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				f[i * prime[j]] = 1ll * f[i] * prime[j] % P;
				break;
			} else {
				f[i * prime[j]] = 1ll * f[i] * f[prime[j]] % P;
			}
		}
	}
	for (int i = 1; i < N; ++i) {
		sum[i] = (sum[i - 1] + f[i]) % P;
	}
}

long long all;

bool ok[M];
int S[M];

int sum1(long long n) {
	n %= P;
	return 1ll * n * (n + 1) % P * Inv2 % P;
}

int sum2(long long n) {
	n %= P;
	return 1ll * n * (n + 1) % P * (2 * n + 1) % P * Inv6 % P;
}

int calc(long long n) {
	if (n < N) {
		return sum[n];
	}
	if (ok[all / n]) {
		return S[all / n];
	}
	int res = sum1(n);
	int lst = sum2(1);
	for (long long l = 2, r; l <= n; l = r + 1) {
		long long t = n / l;
		r = n / t;
		int v = sum2(r);
		res = (res - 1ll * (v - lst) * calc(t)) % P;
		lst = v;
	}
	ok[all / n] = true;
	S[all / n] = res;
	return res;
}

int solve(long long n) {
	all = n;
	for (int i = 1; i <= n / N; ++i) {
		ok[i] = false;
	}
	int ans = 0;
	int lst = 0;
	for (long long l = 1, r; l <= n; l = r + 1) {
		long long t = n / l;
		r = n / t;
		int v = calc(r);
		int st = sum1(t);
		ans = (ans + 1ll * (v - lst) * st % P * st) % P;
		lst = v;
	}
	return (ans + P) % P;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init();

	long long n;
	std::cin >> n;
	std::cout << solve(n) << "\n";
}
