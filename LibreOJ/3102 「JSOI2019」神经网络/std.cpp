#include <bits/stdc++.h>

const int M = 305, N = 5005, P = 998244353;

int m, n;
std::vector<int> E[N];

int fac[N], inv[N];

int qpow(int a, int b) {
	int s = 1;
	for (; b; b >>= 1) {
		if (b & 1) {
			s = 1ll * s * a % P;
		}
		a = 1ll * a * a % P;
	}
	return s;
}

void init(int n = N - 1) {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i) {
		fac[i] = 1ll * fac[i - 1] * i % P;
	}
	inv[n] = qpow(fac[n], P - 2);
	for (int i = n; i; --i) {
		inv[i - 1] = 1ll * inv[i] * i % P;
	}
}

int C(int n, int m) {
	if (m < 0 || m > n) {
		return 0;
	}
	return 1ll * fac[n] * inv[m] % P * inv[n - m] % P;
}

int sz[N], dp[N][N][3], sum[N][N], tmp[N][3];

void dfs(int u, int fa = 0) {
	sz[u] = 1;
	dp[u][1][0] = 1, dp[u][1][1] = dp[u][1][2] = 0;
	for (int v : E[u]) {
		if (v != fa) {
			dfs(v, u);
			for (int i = 1; i <= sz[u] + sz[v]; ++i) {
				tmp[i][0] = tmp[i][1] = tmp[i][2] = 0;
			}
			for (int i = 1; i <= sz[u]; ++i) {
				for (int j = 1; j <= sz[v]; ++j) {
					tmp[i + j][0] = (tmp[i + j][0] + 1ll * sum[v][j] * dp[u][i][0]) % P;
					tmp[i + j][1] = (tmp[i + j][1] + 1ll * sum[v][j] * dp[u][i][1]) % P;
					tmp[i + j - 1][1] = (tmp[i + j - 1][1] + 1ll * (dp[v][j][0] + dp[v][j][1]) * dp[u][i][0]) % P;
					tmp[i + j][2] = (tmp[i + j][2] + 1ll * sum[v][j] * dp[u][i][2]) % P;
					tmp[i + j - 1][2] = (tmp[i + j - 1][2] + 1ll * (dp[v][j][0] + dp[v][j][1]) * dp[u][i][1]) % P;
				}
			}
			for (int i = 1; i <= sz[u] + sz[v]; ++i) {
				dp[u][i][0] = tmp[i][0], dp[u][i][1] = tmp[i][1], dp[u][i][2] = tmp[i][2];
			}
			sz[u] += sz[v];
		}
	}
	for (int i = 0; i <= sz[u]; ++i) {
		sum[u][i] = (dp[u][i][0] + 2ll * dp[u][i][1] + 2ll * dp[u][i][2]) % P;
	}
}

int f[N], g[N], tg[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	init();

	std::cin >> m;
	int tot = 0;
	g[0] = 1;
	for (int k = 1; k <= m; ++k) {
		std::cin >> n;
		for (int i = 1; i <= n; ++i) {
			E[i].clear();
		}
		for (int i = 1; i < n; ++i) {
			int u, v;
			std::cin >> u >> v;
			E[u].push_back(v);
			E[v].push_back(u);
		}
		dfs(1);
		for (int i = 1; i <= n; ++i) {
			f[i] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < i; ++j) {
				f[i - j] = (f[i - j] + (j & 1 ? -1ll : 1ll) * C(i - 1, j) * fac[i] % P * sum[1][i]) % P;
			}
		}
		for (int i = 0; i <= tot + n; ++i) {
			tg[i] = 0;
		}
		for (int i = 0; i <= tot; ++i) {
			for (int j = 1; j <= n; ++j) {
				tg[i + j] = (tg[i + j] + 1ll * g[i] * f[j] % P * C(i + j, i)) % P;
			}
		}
		for (int i = 0; i <= tot + n; ++i) {
			g[i] = tg[i];
		}
		tot += n;
	}

	int ans = 0;
	for (int i = 1; i <= tot; ++i) {
		ans = (ans + 1ll * g[i] * fac[i - 1] % P * inv[i]) % P;
	}
	std::cout << (ans + P) % P << "\n";
}