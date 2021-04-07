#include <bits/stdc++.h>

const int N = 30, MX = 152501;
const int P = 998244353;

int n, m, mx;

struct Edge {
	int u, v, w;
} E[N * (N - 1) / 2];

int phi[MX + 1];

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

struct poly {
	int x, y;

	poly() : x(0), y(0) {}
	poly(int _x, int _y) : x(_x), y(_y) {}

	void operator+=(const poly &rhs) {
		x = (x + rhs.x) % P;
		y = (y + rhs.y) % P;
	}

	void operator-=(const poly &rhs) {
		x = (x + P - rhs.x) % P;
		y = (y + P - rhs.y) % P;
	}

	poly operator+(const poly &rhs) const {
		return poly((x + rhs.x) % P, (y + rhs.y) % P);
	}

	poly operator*(const poly &rhs) const {
		return poly((1ll * x * rhs.y + 1ll * y * rhs.x) % P, 1ll * y * rhs.y % P);
	}

	poly inv() const {
		int t = qpow(y, P - 2);
		return poly(1ll * (P - x) * t % P * t % P, t);
	}

	poly neg() const {
		return poly((P - x) % P, (P - y) % P);
	}
};

poly a[N][N];

poly det(int n) {
	poly ans(0, 1);
	for (int i = 0; i < n; ++i) {
		int k = -1;
		for (int j = i; j < n; ++j) {
			if (a[j][i].y) {
				k = j;
				break;
			}
		}
		if (k == -1) {
			for (int j = i; j < n; ++j) {
				if (a[j][i].x) {
					k = j;
					break;
				}
			}
			if (k == -1) {
				return poly(0, 0);
			}
		}
		bool flag = false;
		if (k != i) {
			for (int j = i; j < n; ++j) {
				std::swap(a[i][j], a[k][j]);
			}
			ans = ans.neg();
		}
		if (!a[i][i].y) {
			for (int j = i; j < n; ++j) {
				a[j][i].y = a[j][i].x;
				a[j][i].x = 0;
			}
			flag = true;
		}
		poly inv = a[i][i].inv();
		for (int j = i + 1; j < n; ++j) {
			if (a[j][i].x || a[j][i].y) {
				poly t = a[j][i].neg() * inv;
				for (int k = i; k < n; ++k) {
					a[j][k] += a[i][k] * t;
				}
			}
		}
		if (flag) {
			a[i][i].x = a[i][i].y;
			a[i][i].y = 0;
		}
		ans = ans * a[i][i];
	}
	return ans;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	mx = 0;
	for (int i = 0; i < m; ++i) {
		--E[i].u, --E[i].v;
		std::cin >> E[i].u >> E[i].v >> E[i].w;
		mx = std::max(mx, E[i].w);
	}
	for (int i = 1; i <= mx; ++i) {
		phi[i] += i;
		for (int j = i + i; j <= mx; j += i) {
			phi[j] -= phi[i];
		}
	}

	int ans = 0;
	for (int d = 1; d <= mx; ++d) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				a[i][j] = poly(0, 0);
			}
		}
		int cnt = 0;
		for (int i = 0; i < m; ++i) {
			if (E[i].w % d == 0) {
				a[E[i].u][E[i].v] -= poly(E[i].w, 1);
				a[E[i].v][E[i].u] -= poly(E[i].w, 1);
				a[E[i].u][E[i].u] += poly(E[i].w, 1);
				a[E[i].v][E[i].v] += poly(E[i].w, 1);
				++cnt;
			}
		}
		ans = (ans + 1ll * det(n - 1).x * phi[d]) % P;
	}
	std::cout << ans << "\n";
}
