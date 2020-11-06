#include <bits/stdc++.h>

const int N = 200005;

int L, n, p[N];
long long sum[N];

long long get_front_even(int x, int k) {
	k = std::min(k, x) - 1;
	return 2ll * k * p[x] - 2 * (sum[x] - sum[x - k] - 1ll * (x - k) * (p[x] - p[x - k]));
}

long long get_front_odd(int x, int k) {
	return get_front_even(x, k) + p[x];
}

long long get_back_even(int x, int k) {
	k = std::min(k, n + 1 - x) - 1;
	return 2ll * k * (L - p[x + k]) + 2 * (sum[x + k] - sum[x] - 1ll * (x + 1) * (p[x + k] - p[x]));
}

long long get_back_odd(int x, int k) {
	return get_back_even(x, k) + L - p[x];
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	std::cin >> L >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> p[i];
	}
	p[n + 1] = L;
	for (int i = 1; i <= n + 1; ++i) {
		sum[i] = sum[i - 1] + 1ll * (p[i] - p[i - 1]) * i;
	}
	long long ans = 0;
	for (int i = 0; i <= n + 1; ++i) {
		int k = std::min(i, n + 1 - i);
		if (i >= 1) {
			ans = std::max(ans, get_front_even(i, k + 1) + get_back_odd(i, k));
		}
		if (i <= n) {
			ans = std::max(ans, get_front_odd(i, k) + get_back_even(i, k + 1));
		}
	}
	std::cout << ans << std::endl;
}
