#include <bits/stdc++.h>

const int N = 6;
const int P = 1000000007;
const int INF = 0x3f3f3f3f;

int n, a[N];
int inv[N + 1];
int c[N];

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

void init() {
	inv[1] = 1;
	for (int i = 2; i <= n; ++i) {
		inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	}
}

int LIS() {
	static int f[N];
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		f[i] = 1;
		for (int j = 0; j < i; ++j) {
			if (c[j] < c[i]) {
				f[i] = std::max(f[i], f[j] + 1);
			}
		}
		ans = std::max(ans, f[i]);
	}
	return ans;
}

int m, R[N];
int f[N][N];

int calc() {
	for (int i = 0; i < n; ++i) {
		R[i] = INF;
	}
	m = 0;
	for (int i = 0; i < n; ++i) {
		R[c[i]] = std::min(R[c[i]], a[i]);
		m = std::max(m, c[i] + 1);
	}
	for (int i = 0; i < m; ++i) {
		if (R[i] == INF) {
			return 0;
		}
	}
	for (int i = m - 2; i >= 0; --i) {
		R[i] = std::min(R[i], R[i + 1]);
	}
	std::vector<int> v(R, R + m);
	v.insert(v.begin(), 0);
	v.erase(std::unique(v.begin(), v.end()), v.end());
	for (int i = 0; i < m; ++i) {
		R[i] = std::lower_bound(v.begin(), v.end(), R[i]) - v.begin();
	}
	int mv = v.size();
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < mv - 1; ++j) {
			f[i][j] = 0;
		}
	}
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < mv - 1; ++j) {
			int coef = 1;
			for (int k = 0; k <= i + 1; ++k) {
				if (k) {
					coef = 1ll * coef * (v[j + 1] - v[j] - k + 1) % P * inv[k] % P;
				}
				f[i][j] = (f[i][j] + 1ll * coef * (i - k < 0 ? 1 : (j == 0 ? 0 : f[i - k][j - 1]))) % P;
				if (k <= i && j >= R[i - k]) {
					break;
				}
			}
		}
	}
	return f[m - 1][mv - 2];
}

int ans;

void dfs(int k) {
	if (k == n) {
		ans = (ans + 1ll * calc() * LIS()) % P;
		return;
	}
	for (int i = 0; i < n; ++i) {
		c[k] = i;
		dfs(k + 1);
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}
	init();
	dfs(0);
	for (int i = 0; i < n; ++i) {
		ans = 1ll * ans * qpow(a[i], P - 2) % P;
	}
	std::cout << ans << "\n";
}
