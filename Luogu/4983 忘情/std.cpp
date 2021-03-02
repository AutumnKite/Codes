#include <bits/stdc++.h>

const int N = 500005;

int n, m;
int a[N];

long long f[N];
int c[N];

long long X(int i) {
	return a[i];
}

long long Y(int i) {
	return f[i] + 1ll * a[i] * a[i];
}

bool check(int i, int j, int k) {
	return (__int128_t)(Y(j) - Y(i)) * (X(k) - X(j)) < (__int128_t)(Y(k) - Y(j)) * (X(j) - X(i));
}

void DP(long long x) {
	static int Q[N];
	int h = 1, t = 0;
	f[0] = 0;
	c[0] = 0;
	Q[++t] = 0;
	for (int i = 1; i <= n; ++i) {
		while (h < t && (Y(Q[h + 1]) - Y(Q[h])) <= 2 * (a[i] + 1) * (X(Q[h + 1]) - X(Q[h]))) {
			++h;
		}
		f[i] = f[Q[h]] + 1ll * (a[i] + 1 - a[Q[h]]) * (a[i] + 1 - a[Q[h]]) + x;
		c[i] = c[Q[h]] + 1;
		while (h < t && !check(Q[t - 1], Q[t], i)) {
			--t;
		}
		Q[++t] = i;
	}
}

bool check(long long x) {
	DP(x);
	return c[n] >= m;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		a[i] += a[i - 1];
	}

	long long l = 0, r = 1e18, ans = 0;
	while (l <= r) {
		long long mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}

	DP(ans);
	std::cout << f[n] - m * ans << "\n";
}