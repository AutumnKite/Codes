#include <bits/stdc++.h>

const int N = 100005;
const long long INF = 1000000000000000001ll;

int n, L, p;
std::string s[N];
int a[N];

int h, t;
std::pair<int, int> q[N];
long long f[N];
int lst[N];

long long mul(long long a, long long b) {
	return b == 0 || a <= INF / b ? a * b : INF;
}

long long plus(long long a, long long b) {
	return a <= INF - b ? a + b : INF;
}

long long qpow(long long a, int b) {
	long long s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = mul(s, a);
		}
		a = mul(a, a);
	}
	return s;
}

long long trans(int j, int i) {
	return plus(f[j], qpow(abs(a[i] - a[j] + i - j - 1 - L), p));
}

void arrange(int n) {
	if (n == 0) {
		return;
	}
	arrange(lst[n]);
	for (int i = lst[n] + 1; i <= n; ++i) {
		std::cout << s[i] << " \n"[i == n];
	}
}

void solve() {
	std::cin >> n >> L >> p;
	for (int i = 1; i <= n; ++i) {
		std::cin >> s[i];
		a[i] = a[i - 1] + s[i].size();
	}

	f[0] = 0;
	h = 1, t = 0;
	q[0] = std::make_pair(0, 0);
	q[++t] = std::make_pair(n, 0);
	for (int i = 1; i <= n; ++i) {
		while (h < t && q[h].first < i) {
			++h;
		}
		f[i] = trans(q[h].second, i);
		lst[i] = q[h].second;
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
	if (f[n] == INF) {
		std::cout << "Too hard to arrange\n";
	} else {
		std::cout << f[n] << "\n";
		arrange(n);
	}
	std::cout << "--------------------\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int T;
	std::cin >> T;
	while (T--) {
		solve();
	}
}