#include <bits/stdc++.h>

const int N = 100005, B = 200, C = N / B + 5;

int n, q;
int a[N];

int tot, L[C], R[C], bel[N];

int tag[N];
int cnt[C][N];

int id[N], val[N];

int spre[N], ssuf[N];

long long sum[C][C];

int count(register int b1, register int l1, register int r1, register int b2, register int l2, register int r2) {
	register int now = r1 - l1 + 1;
	register int p = L[b1];
	register int ans = 0;
	for (register int i = L[b2]; i <= R[b2]; ++i) {
		if (l2 <= id[i] && id[i] <= r2) {
			while (p <= R[b1] && (id[p] < l1 || r1 < id[p] || val[p] <= val[i])) {
				now -= (l1 <= id[p] && id[p] <= r1);
				++p;
			}
			ans += now;
		}
	}
	return ans;
}

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
} T;

bool cmp(int x, int y) {
	return a[x] < a[y];
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}

	for (int i = 1; i <= n; ++i) {
		id[i] = i;
	}
	tot = (n - 1) / B + 1;
	for (int k = 1; k <= tot; ++k) {
		L[k] = (k - 1) * B + 1;
		R[k] = std::min(n, k * B);
		std::fill(tag + 1, tag + 1 + n, 0);
		for (int i = L[k]; i <= R[k]; ++i) {
			bel[i] = k;
			++tag[a[i]];
		}
		int t = 0;
		for (int i = 1; i <= n; ++i) {
			t += tag[i];
			cnt[k][i] = cnt[k - 1][i] + t;
		}
		std::sort(id + L[k], id + R[k] + 1, cmp);
		for (int i = L[k]; i <= R[k]; ++i) {
			val[i] = a[id[i]];
		}
		for (int i = L[k]; i <= R[k]; ++i) {
			spre[i] = i - L[k] - T.query(a[i]);
			T.add(a[i], 1);
		}
		for (int i = L[k]; i <= R[k]; ++i) {
			T.add(a[i], -1);
			ssuf[i] = T.query(a[i] - 1);
		}
		for (int i = L[k] + 1; i <= R[k]; ++i) {
			spre[i] += spre[i - 1];
		}
		for (int i = R[k] - 1; i >= L[k]; --i) {
			ssuf[i] += ssuf[i + 1];
		}
	}

	for (register int i = 1; i <= tot; ++i) {
		sum[i + 1][i] = 0;
		for (register int j = i; j; --j) {
			sum[j][i] = sum[j + 1][i] + spre[R[j]];
			for (register int k = L[j]; k <= R[j]; ++k) {
				sum[j][i] += cnt[i][a[k]] - cnt[j][a[k]];
			}
		}
	}

	long long ans = 0;
	while (q--) {
		long long _l, _r;
		std::cin >> _l >> _r;
		register int l = _l ^ ans, r = _r ^ ans;
		if (l > r) {
			std::swap(l, r);
		}
		register int bl = bel[l], br = bel[r];
		if (bl == br) {
			if (l == L[bl]) {
				ans = spre[r];
			} else {
				ans = spre[r] - spre[l - 1] - count(bl, L[bl], l - 1, bl, l, r);
			}
		} else {
			ans = ssuf[l] + spre[r] + sum[bl + 1][br - 1];
			for (register int i = R[bl]; i >= l; --i) {
				ans += cnt[br - 1][a[i]] - cnt[bl][a[i]];
			}
			ans += 1ll * (r - L[br] + 1) * (R[br - 1] - L[bl + 1] + 1);
			for (register int i = L[br]; i <= r; ++i) {
				ans -= cnt[br - 1][a[i]] - cnt[bl][a[i]];
			}
			ans += count(bl, l, R[bl], br, L[br], r);
		}
		std::cout << ans << "\n";
	}
}