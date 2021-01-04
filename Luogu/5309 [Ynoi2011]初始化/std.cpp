#include <bits/stdc++.h>

const int N = 200005, B = 300, C = N / B + 5, P = 1000000007;

int n, q;
int a[N];

int tot, L[C], R[C], bel[N];

int sum[C];

int pre[B][B], suf[B][B];

void inc(int &a, int b) {
	a + b >= P ? a += b - P : a += b;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}

	tot = (n - 1) / B + 1;
	for (int k = 1; k <= tot; ++k) {
		L[k] = (k - 1) * B + 1;
		R[k] = std::min(k * B, n);
		sum[k] = 0;
		for (int i = L[k]; i <= R[k]; ++i) {
			bel[i] = k;
			inc(sum[k], a[i]);
		}
	}

	while (q--) {
		int op;
		std::cin >> op;
		if (op == 1) {
			int x, y, z;
			std::cin >> x >> y >> z;
			if (x < B) {
				for (int i = y; i <= x; ++i) {
					inc(pre[x][i], z);
				}
				for (int i = 1; i <= y; ++i) {
					inc(suf[x][i], z);
				}
			} else {
				for (int i = y; i <= n; i += x) {
					inc(a[i], z);
					inc(sum[bel[i]], z);
				}
			}
		} else {
			int l, r;
			std::cin >> l >> r;
			int ans = 0;
			if (bel[l] == bel[r]) {
				for (int i = l; i <= r; ++i) {
					inc(ans, a[i]);
				}
			} else {
				for (int i = l; i <= R[bel[l]]; ++i) {
					inc(ans, a[i]);
				}
				for (int i = bel[l] + 1; i <= bel[r] - 1; ++i) {
					inc(ans, sum[i]);
				}
				for (int i = L[bel[r]]; i <= r; ++i) {
					inc(ans, a[i]);
				}
			}
			for (int x = 1; x < B; ++x) {
				int bl = (l - 1) / x + 1, br = (r - 1) / x + 1;
				int ql = (l - 1) % x + 1, qr = (r - 1) % x + 1;
				if (bl == br) {
					inc(ans, pre[x][qr]);
					inc(ans, P - pre[x][ql - 1]);
				} else {
					inc(ans, pre[x][qr]);
					inc(ans, suf[x][ql]);
					ans = (ans + 1ll * (br - bl - 1) * pre[x][x]) % P;
				}
			}
			std::cout << ans << "\n";
		}
	}
}