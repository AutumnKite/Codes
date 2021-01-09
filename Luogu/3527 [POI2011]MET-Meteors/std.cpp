#include <bits/stdc++.h>

const int N = 300005;

int n, m, q;
std::vector<int> pos[N];

struct Event {
	int l, r, v;
} a[N];

long long w[N];

int p[N], ans[N];

struct BIT {
	long long c[N];

	void add(int x, int v) {
		for (; x <= m; x += x & -x) {
			c[x] += v;
		}
	}

	long long query(int x) {
		long long s = 0;
		for (; x; x ^= x & -x) {
			s += c[x];
		}
		return s;
	}
} T;

void solve(int l, int r, int L, int R) {
	if (l > r) {
		return;
	}
	if (L == R) {
		for (int i = l; i <= r; ++i) {
			ans[p[i]] = L;
		}
		return;
	}
	int mid = (L + R) >> 1;
	for (int i = L; i <= mid; ++i) {
		if (a[i].l <= a[i].r) {
			T.add(a[i].l, a[i].v);
			T.add(a[i].r + 1, -a[i].v);
		} else {
			T.add(a[i].l, a[i].v);
			T.add(1, a[i].v);
			T.add(a[i].r + 1, -a[i].v);
		}
	}
	static int p1[N], p2[N];
	int c1 = 0, c2 = 0;
	for (int i = l; i <= r; ++i) {
		long long sum = 0;
		bool flag = true;
		for (int j : pos[p[i]]) {
			sum += T.query(j);
			if (sum >= w[p[i]]) {
				p1[++c1] = p[i];
				flag = false;
				break;
			}
		}
		if (flag) {
			w[p[i]] -= sum;
			p2[++c2] = p[i];
		}
	}
	for (int i = L; i <= mid; ++i) {
		if (a[i].l <= a[i].r) {
			T.add(a[i].l, -a[i].v);
			T.add(a[i].r + 1, a[i].v);
		} else {
			T.add(a[i].l, -a[i].v);
			T.add(1, -a[i].v);
			T.add(a[i].r + 1, a[i].v);
		}
	}
	for (int i = 1; i <= c1; ++i) {
		p[l + i - 1] = p1[i];
	}
	for (int i = 1; i <= c2; ++i) {
		p[l + i + c1 - 1] = p2[i];
	}
	solve(l, l + c1 - 1, L, mid);
	solve(l + c1, r, mid + 1, R);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int c;
		std::cin >> c;
		pos[c].push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		std::cin >> w[i];
	}
	std::cin >> q;
	for (int i = 1; i <= q; ++i) {
		std::cin >> a[i].l >> a[i].r >> a[i].v;
	}

	for (int i = 1; i <= n; ++i) {
		p[i] = i;
	}
	solve(1, n, 1, q + 1);
	
	for (int i = 1; i <= n; ++i) {
		if (ans[i] <= q) {
			std::cout << ans[i] << "\n";
		} else {
			std::cout << "NIE\n";
		}
	}
}