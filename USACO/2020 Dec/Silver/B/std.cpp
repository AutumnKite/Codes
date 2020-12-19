#include <bits/stdc++.h>

const int N = 2505;

int n;
int x[N];
int y[N];

struct Node {
	int x, y;

	bool operator < (const Node &rhs) const {
		return x < rhs.x;
	}
} a[N];

struct BIT {
	int c[N];

	void clear() {
		for (int i = 1; i <= n; ++i) {
			c[i] = 0;
		}
	}

	void add(int x, int v) {
		for (; x <= n; x += x & -x) {
			c[x] += v;
		}
	}

	int query(int x) {
		int s = 0;
		for (; x; x ^= x & -x) {
			s += c[x];
		}
		return s;
	}
} T;

long long ans;

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i].x >> a[i].y;
		x[i] = a[i].x;
		y[i] = a[i].y;
	}
	std::sort(x + 1, x + n + 1);
	std::sort(y + 1, y + n + 1);
	std::sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; ++i) {
		a[i].x = std::lower_bound(x + 1, x + 1 + n, a[i].x) - x;
		a[i].y = std::lower_bound(y + 1, y + 1 + n, a[i].y) - y;
	}
	for (int i = 1; i <= n; ++i) {
		T.clear();
		for (int j = i; j <= n; ++j) {
			T.add(a[j].y, 1);
			int mn = std::min(a[i].y, a[j].y);
			int mx = std::max(a[i].y, a[j].y);
			ans += 1ll * T.query(mn) * (j - i + 1 - T.query(mx - 1));
		}
	}
	std::cout << ans + 1 << "\n";
}