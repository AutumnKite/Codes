#include <bits/stdc++.h>

const int N = 10000005;

int n;
int a[N];

int cnt, prime[N];
bool vis[N];
int minp[N];
int b[N];
int f[N];

void init() {
	vis[1] = true;
	f[1] = 0;
	for (int i = 2; i < N; ++i) {
		if (!vis[i]) {
			prime[++cnt] = i;
			vis[i] = true;
			minp[i] = i;
			b[i] = 1;
			f[i] = 1;
		}
		for (int j = 1; j <= cnt && i * prime[j] < N; ++j) {
			int v = i * prime[j];
			vis[v] = true;
			if (i % prime[j] == 0) {
				minp[v] = minp[i] * prime[j];
				b[v] = b[i] + 1;
				f[v] = v == minp[v] ? 1 : (b[v] == b[v / minp[v]] ? -f[v / minp[v]] : 0);
				break;
			} else {
				minp[v] = prime[j];
				b[v] = 1;
				f[v] = b[i] == 1 ? -f[i] : 0;
			}
		}
	}
	for (int i = 1; i < N; ++i) {
		f[i] += f[i - 1];
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init();

	int T = 1;
	std::cin >> T;
	while (T--) {
		int n, m;
		std::cin >> n >> m;
		std::vector<int> pn, pm;
		for (int l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			pn.push_back(r);
		}
		for (int l = 1, r; l <= m; l = r + 1) {
			r = m / (m / l);
			pm.push_back(r);
		}
		std::vector<int> pos(pn.size() + pm.size());
		std::merge(pn.begin(), pn.end(), pm.begin(), pm.end(), pos.begin());
		pos.erase(std::unique(pos.begin(), pos.end()), pos.end());
		int lst = 0;
		long long ans = 0;
		for (int i : pos) {
			ans += 1ll * (f[i] - f[lst]) * (n / i) * (m / i);
			lst = i;
		}
		std::cout << ans << "\n";
	}
}