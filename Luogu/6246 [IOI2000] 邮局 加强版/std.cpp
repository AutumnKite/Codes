#include <bits/stdc++.h>

const int N = 500005;

int n, m;
int a[N];
long long sum[N];

std::pair<long long, int> f[N];

void DP(long long K) {
	static int h, t;
	static std::pair<int, int> q[N];

	auto trans = [&](int j, int i) {
		int l = (i - j) / 2;
		return std::make_pair(f[j].first + (sum[i] - sum[i - l]) - (sum[j + l] - sum[j]) + K, f[j].second + 1);
	};

	f[0] = std::make_pair(0ll, 0);
	h = 1, t = 0;
	q[0] = std::make_pair(0, 0);
	q[++t] = std::make_pair(n, 0);
	for (int i = 1; i <= n; ++i) {
		while (h < t && q[h].first < i) {
			++h;
		}
		f[i] = trans(q[h].second, i);
		while (h < t && trans(i, q[t - 1].first + 1) < trans(q[t].second, q[t - 1].first + 1)) {
			--t;
		}
		int l = std::max(i + 1, q[t - 1].first + 1), r = q[t].first;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (trans(i, mid) < trans(q[t].second, mid)) {
				q[t].first = mid - 1;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		if (q[t].first < n) {
			q[++t] = std::make_pair(n, i);
		}
	}
}

bool check(long long K) {
	DP(K);
	return f[n].second <= m;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	std::sort(a + 1, a + 1 + n);

	DP(0);

	long long l = 0, r = 1e12, ans = 0;
	while (l <= r) {
		long long mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}

	DP(ans);
	std::cout << f[n].first - ans * m << "\n";
}