#include <bits/stdc++.h>

const int N = 500005;

int n;
int a[N];

double f1[N], f2[N];

double trans(int j, int i) {
	return a[j] + sqrt(i - j);
}

void DP(double *f) {
	static int h, t;
	static std::pair<int, int> q[N];
	f[1] = a[1];
	h = 1, t = 0;
	q[0] = std::make_pair(1, 0);
	q[++t] = std::make_pair(n, 1);
	for (int i = 2; i <= n; ++i) {
		while (h < t && q[h].first < i) {
			++h;
		}
		f[i] = trans(q[h].second, i);
		while (h < t && trans(i, q[t - 1].first + 1) > trans(q[t].second, q[t - 1].first + 1)) {
			--t;
		}
		int l = std::max(i + 1, q[t - 1].first + 1), r = q[t].first;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (trans(i, mid) > trans(q[t].second, mid)) {
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

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}

	DP(f1);
	std::reverse(a + 1, a + 1 + n);
	DP(f2);
	std::reverse(f2 + 1, f2 + 1 + n);
	std::reverse(a + 1, a + 1 + n);
	
	for (int i = 1; i <= n; ++i) {
		std::cout << std::max(0, (int)ceil(std::max(f1[i], f2[i])) - a[i]) << "\n";
	}
}