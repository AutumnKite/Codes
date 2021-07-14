#include <bits/stdc++.h>

const int P = 1000000007;
const long long P2 = 4ll * P * P;

std::vector<int> inv;

void init(int n) {
	inv.resize(n + 1);
	inv[1] = 1;
	for (int i = 2; i <= n; ++i) {
		inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	}
}

int main() {
	freopen("robot.in", "r", stdin);
	freopen("robot.out", "w", stdout);

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n;
	std::cin >> n;
	init(n + 1);
	std::vector<int> v;
	std::vector<int> vl(n), vr(n);
	for (int i = 0; i < n; ++i) {
		std::cin >> vl[i] >> vr[i];
		--vl[i];
		v.push_back(vl[i]);
		v.push_back(vr[i]);
	}
	std::sort(v.begin(), v.end());
	v.erase(std::unique(v.begin(), v.end()), v.end());

	int tot = 0;
	std::vector<std::vector<int>> id(n, std::vector<int>(n, -1));
	std::function<void(int, int)> init = [&](int l, int r) {
		if (l > r || id[l][r] != -1) {
			return;
		}
		id[l][r] = tot++;
		for (int i = l; i <= r; ++i) {
			if (abs((i - l) - (r - i)) <= 2) {
				init(l, i - 1);
				init(i + 1, r);
			}
		}
	};
	init(0, n - 1);
	++tot;

	std::vector<long long> lst(tot);
	std::vector<std::vector<long long>> f(tot, std::vector<long long>(n + 2));
	lst[tot - 1] = 1;
	for (int k = 0; k + 1 < (int)v.size(); ++k) {
		int L = std::min(v[k + 1] - v[k], n + 1);
		std::fill(f[tot - 1].begin(), f[tot - 1].end(), 1);
		std::vector<bool> vis(tot);
		std::function<void(int, int)> DP = [&](int l, int r) {
			if (l > r) {
				return;
			}
			if (vis[id[l][r]]) {
				return;
			}
			vis[id[l][r]] = true;
			std::vector<long long> ans(L + 1);
			for (int i = l; i <= r; ++i) {
				if (abs((i - l) - (r - i)) <= 2) {
					DP(l, i - 1);
					DP(i + 1, r);
					if (vl[i] <= v[k] && vr[i] >= v[k + 1]) {
						int ls = l == i ? tot - 1 : id[l][i - 1];
						int rs = r == i ? tot - 1 : id[i + 1][r];
						for (int j = 1; j <= L; ++j) {
							ans[j] += f[ls][j] * f[rs][j - 1];
							if (ans[j] >= P2) {
								ans[j] -= P2;
							}
						}
					}
				}
			}
			auto &tmp = f[id[l][r]];
			tmp[0] = lst[id[l][r]] % P;
			for (int i = 1; i <= L; ++i) {
				tmp[i] = (tmp[i - 1] + ans[i]) % P;
			}
		};
		DP(0, n - 1);

		int x = v[k + 1] - v[k];
		std::vector<int> pre(L + 1), suf(L + 1);
		pre[0] = 1;
		for (int i = 0; i < L; ++i) {
			pre[i + 1] = 1ll * pre[i] * (x - i) % P * inv[i + 1] % P;
		}
		suf[L] = 1;
		for (int i = L; i > 0; --i) {
			suf[i - 1] = P - 1ll * suf[i] * (x - i) % P * inv[L + 1 - i] % P;
		}
		std::fill(lst.begin(), lst.end(), 0);
		for (int i = 0; i <= L; ++i) {
			long long t = 1ll * pre[i] * suf[i] % P;
			for (int j = 0; j < tot; ++j) {
				lst[j] += t * f[j][i];
				if (lst[j] >= P2) {
					lst[j] -= P2;
				}
			}
		}
	}
	std::cout << lst[id[0][n - 1]] % P << "\n";
}
