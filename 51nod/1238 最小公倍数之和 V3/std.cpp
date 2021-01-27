#include <bits/stdc++.h>

const int N = 5000005, M = 2005, P = 1000000007, Inv2 = (P + 1) / 2;

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
			f[i] = 1 - i;
		}
		for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0) {
				f[i * prime[j]] = f[i];
				break;
			} else {
				f[i * prime[j]] = f[i] * f[prime[j]];
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

int calc(long long n) {
	if (n < N) {
		return sum[n];
	}
	if (ok[all / n]) {
		return S[all / n];
	}
	int res = n;
	for (long long l = 2, r; l <= n; l = r + 1) {
		long long t = n / l;
		r = n / t;
		res = (res - 1ll * (l + r) * (r - l + 1) / 2 % P * calc(t)) % P;
	}
	ok[all / n] = true;
	S[all / n] = res;
	return res;
}

int F(int n) {
	return 1ll * n * (n + 1) % P * (n + 2) % P * Inv6 % P;
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
		ans = (ans + 1ll * (v - lst) * F(t)) % P;
		lst = v;
	}
	return (ans + P) % P;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init();

	int a, b;
	std::cin >> a >> b;
	std::cout << (solve(b) + P - solve(a - 1)) % P << "\n";
}
