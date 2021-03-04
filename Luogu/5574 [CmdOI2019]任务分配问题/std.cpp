#include <bits/stdc++.h>

const int N = 25005, M = 30;
const int INF = 0x3f3f3f3f;

int n, m;
int a[N];

int f[M][N];

struct BIT {
	int c[N];

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
};

int calc(int ql, int qr) {
	static int l = 1, r = 0, ans = 0;
	static BIT T;
	while (r < qr) {
		T.add(a[++r], 1);
		ans += T.query(a[r]) - 1;
	}
	while (l > ql) {
		T.add(a[--l], 1);
		ans += r - l + 1 - T.query(a[l]);
	}
	while (r > qr) {
		ans -= T.query(a[r]) - 1;
		T.add(a[r--], -1);
	}
	while (l < ql) {
		ans -= r - l + 1 - T.query(a[l]);
		T.add(a[l++], -1);
	}
	return ans;
}

void solve(int l, int r, int ql, int qr, int k) {
	if (l > r) {
		return;
	}
	int mid = (l + r) >> 1;
	int pos = 0;
	f[k][mid] = INF;
	for (int i = ql; i <= qr && i < mid; ++i) {
		int v = f[k - 1][i] + calc(i + 1, mid);
		if (v < f[k][mid]) {
			f[k][mid] = v;
			pos = i;
		}
	}
	solve(l, mid - 1, ql, pos, k);
	solve(mid + 1, r, pos, qr, k);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	m = std::min(m, n);
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	f[0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		f[0][i] = INF;
	}
	for (int i = 1; i <= m; ++i) {
		solve(1, n, 0, n, i);
	}
	std::cout << f[m][n] << "\n";
}