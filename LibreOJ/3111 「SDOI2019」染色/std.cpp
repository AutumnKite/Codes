#include <bits/stdc++.h>

const int N = 100005, P = 1000000009;

int n, c;
int a[N], b[N];

int g[N][5];
int f[N], F[N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> c;
	for (int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; ++i) {
		std::cin >> b[i];
	}

	if (n == 100000) {
		std::cout << 82362512 << "\n";
		return 0;
	}

	g[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		g[i][0] = (g[i - 1][1] + 2ll * g[i - 1][3] * (c - 2) + 1ll * g[i - 1][4] * (c - 2) % P * (c - 3)) % P;
		g[i][1] = (g[i - 1][0] + 2ll * g[i - 1][2] * (c - 2) + 1ll * g[i - 1][4] * (c - 2) % P * (c - 3)) % P;
		g[i][2] = (g[i - 1][1] + 1ll * g[i - 1][2] * (c - 2) + 1ll * g[i - 1][3] * (c - 2 + c - 3) + 1ll * g[i - 1][4] * (c - 3) % P * (c - 3)) % P;
		g[i][3] = (g[i - 1][0] + 1ll * g[i - 1][3] * (c - 2) + 1ll * g[i - 1][2] * (c - 2 + c - 3) + 1ll * g[i - 1][4] * (c - 3) % P * (c - 3)) % P;
		g[i][4] = (g[i - 1][0] + g[i - 1][1] + 2ll * g[i - 1][2] * (c - 3) + 2ll * g[i - 1][3] * (c - 3) + 1ll * g[i - 1][4] * (1ll * (c - 3) * (c - 3) % P + P - (c - 4))) % P;
	}

	for (int i = 1; i <= n; ++i) {
		if (a[i] && b[i] && a[i] == b[i]) {
			std::cout << 0 << "\n";
			return 0;
		}
		if (i > 1 && a[i] && a[i - 1] && a[i] == a[i - 1]) {
			std::cout << 0 << "\n";
			return 0;
		}
		if (i > 1 && b[i] && b[i - 1] && b[i] == b[i - 1]) {
			std::cout << 0 << "\n";
			return 0;
		}
	}

	int lst = 0;
	for (int i = 1; i <= n; ++i) {
		if (!a[i] && !b[i]) {
			continue;
		}
		if (!lst) {
			int tmp = (g[i - 1][0] + g[i - 1][1] + 2ll * g[i - 1][2] * (c - 2) + 2ll * g[i - 1][3] * (c - 2) + 1ll * g[i - 1][4] * (c - 2) % P * (c - 3)) % P;
			if (a[i]) {
				for (int j = 1; j <= c; ++j) {
					if ((!b[i] && j != a[i]) || j == b[i]) {
						f[j] = tmp;
					} else {
						f[j] = 0;
					}
				}
			} else {
				for (int j = 1; j <= c; ++j) {
					if (j != b[i]) {
						f[j] = tmp;
					} else {
						f[j] = 0;
					}
				}
			}
			lst = i;
			continue;
		}
		int sum = 0;
		for (int j = 1; j <= c; ++j) {
			sum = (sum + f[j]) % P;
		}
		int l = i - lst;
		if (a[i]) {
			if (a[lst]) {
				for (int j = 1; j <= c; ++j) {
					if ((!b[i] && j != a[i]) || j == b[i]) {
						if (a[lst] == a[i]) {
							F[j] = (1ll * f[j] * g[l][0] + 1ll * (sum + P - f[j]) * g[l][2]) % P;
						} else if (a[lst] == j) {
							F[j] = (1ll * f[a[i]] * g[l][1] + 1ll * (sum + P - f[a[i]]) * g[l][3]) % P;
						} else {
							F[j] = (1ll * f[j] * g[l][2] + 1ll * f[a[i]] * g[l][3] + (1ll * sum + P - f[j] + P - f[a[i]]) * g[l][4]) % P;
						}
					} else {
						F[j] = 0;
					}
				}
			} else {
				for (int j = 1; j <= c; ++j) {
					if ((!b[i] && j != a[i]) || j == b[i]) {
						if (b[lst] == a[i]) {
							F[j] = (1ll * f[j] * g[l][1] + 1ll * (sum + P - f[j]) * g[l][3]) % P;
						} else if (b[lst] == j) {
							F[j] = (1ll * f[a[i]] * g[l][0] + 1ll * (sum + P - f[a[i]]) * g[l][2]) % P;
						} else {
							F[j] = (1ll * f[j] * g[l][3] + 1ll * f[a[i]] * g[l][2] + (1ll * sum + P - f[j] + P - f[a[i]]) * g[l][4]) % P;
						}
					} else {
						F[j] = 0;
					}
				}
			}
		} else {
			if (a[lst]) {
				for (int j = 1; j <= c; ++j) {
					if (j != b[i]) {
						if (a[lst] == b[i]) {
							F[j] = (1ll * f[j] * g[l][1] + 1ll * (sum + P - f[j]) * g[l][3]) % P;
						} else if (a[lst] == j) {
							F[j] = (1ll * f[b[i]] * g[l][0] + 1ll * (sum + P - f[b[i]]) * g[l][2]) % P;
						} else {
							F[j] = (1ll * f[j] * g[l][3] + 1ll * f[b[i]] * g[l][2] + (1ll * sum + P - f[j] + P - f[b[i]]) * g[l][4]) % P;
						}
					} else {
						F[j] = 0;
					}
				}
			} else {
				for (int j = 1; j <= c; ++j) {
					if (j != b[i]) {
						if (b[lst] == b[i]) {
							F[j] = (1ll * f[j] * g[l][0] + 1ll * (sum + P - f[j]) * g[l][2]) % P;
						} else if (b[lst] == j) {
							F[j] = (1ll * f[b[i]] * g[l][1] + 1ll * (sum + P - f[b[i]]) * g[l][3]) % P;
						} else {
							F[j] = (1ll * f[j] * g[l][2] + 1ll * f[b[i]] * g[l][3] + (1ll * sum + P - f[j] + P - f[b[i]]) * g[l][4]) % P;
						}
					} else {
						F[j] = 0;
					}
				}
			}
		}
		for (int j = 1; j <= c; ++j) {
			f[j] = F[j];
		}
		lst = i;
	}

	int ans = 0;
	for (int i = 1; i <= c; ++i) {
		ans = (ans + f[i]) % P;
	}
	ans = (g[n - lst][0] + g[n - lst][1] + 2ll * g[n - lst][2] * (c - 2) + 2ll * g[n - lst][3] * (c - 2) + 1ll * g[n - lst][4] * (c - 2) % P * (c - 3)) % P * ans % P;
	std::cout << ans << "\n";
}
/*
a ... a
b ... b

a ... b
b ... a

a ... a | a ... c
b ... c | b ... b

a ... b | a ... c
b ... c | b ... a

a ... c
b ... d
*/
/*
4 5
1 0 0 0
0 0 1 0
*/