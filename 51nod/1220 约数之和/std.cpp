#include <bits/stdc++.h>

const int N = 2000005, M = 505, P = 1000000007;

int cnt, prime[N];
bool vis[N];
int mu[N];
int sum[N];

int minp[N];
int d[N];
int sumd[N];

void init() {
	vis[1] = true;
	mu[1] = 1;
	d[1] = 1;
	for (int i = 2; i < N; ++i) {
		if (!vis[i]) {
			prime[++cnt] = i;
			mu[i] = -1;
			minp[i] = i;
			d[i] = 1 + i;
		}
		for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				minp[i * prime[j]] = 1ll * minp[i] * prime[j];
				d[i * prime[j]] = (d[i] + 1ll * d[i / minp[i]] * minp[i * prime[j]]) % P;
				mu[i * prime[j]] = 0;
				break;
			} else {
				minp[i * prime[j]] = prime[j];
				d[i * prime[j]] = 1ll * d[i] * d[prime[j]] % P;
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
	for (int i = 1; i < N; ++i) {
		sum[i] = (sum[i - 1] + 1ll * mu[i] * i) % P;
		sumd[i] = (sumd[i - 1] + d[i]) % P;
	}
}

int all;

bool ok[M];
int S[M];

int calc(int n) {
	if (n < N) {
		return sum[n];
	}
	if (ok[all / n]) {
		return S[all / n];
	}
	int res = 1;
	for (int l = 2, r; l <= n; l = r + 1) {
		int t = n / l;
		r = n / t;
		res = (res - 1ll * (l + r) * (r - l + 1) / 2 % P * calc(t)) % P;
	}
	ok[all / n] = true;
	S[all / n] = res;
	return res;
}

int F(int n) {
	if (n < N) {
		return sumd[n];
	}
	int res = 0;
	for (int l = 1, r; l <= n; l = r + 1) {
		int t = n / l;
		r = n / t;
		res = (res + 1ll * (l + r) * (r - l + 1) / 2 % P * t) % P;
	}
	return res;
}

int solve(int n) {
	all = n;
	for (int i = 1; i <= n / N; ++i) {
		ok[i] = false;
	}
	int ans = 0;
	int lst = 0;
	for (int l = 1, r; l <= n; l = r + 1) {
		int t = n / l;
		r = n / t;
		int v = calc(r);
		int Ft = F(t);
		ans = (ans + 1ll * (v - lst) * Ft % P * Ft) % P;
		lst = v;
	}
	return (ans + P) % P;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init();

	int n;
	std::cin >> n;
	std::cout << solve(n) << "\n";
}
