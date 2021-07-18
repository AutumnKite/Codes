#include <bits/stdc++.h>

const int P = 998244353;

struct state {
	int c, r, b, b2, rb, s;

	state(int _c = 0) : c(_c), r(0), b(0), b2(0), rb(0), s(0) {}

	state add_r() const {
		state res;
		res.c = c;
		res.r = (r + c) % P;
		res.b = b;
		res.b2 = b2;
		res.rb = (rb + b) % P;
		res.s = (s + b2) % P;
		return res;
	}

	state add_b() const {
		state res;
		res.c = c;
		res.r = r;
		res.b = (b + c) % P;
		res.b2 = (b2 + 2ll * b + c) % P;
		res.rb = (rb + r) % P;
		res.s = (s + 2ll * rb + r) % P;
		return res;
	}

	state operator*(const state &rhs) const {
		state res;
		res.c = 1ll * c * rhs.c % P;
		res.r = (1ll * r * rhs.c + 1ll * c * rhs.r) % P;
		res.b = (1ll * b * rhs.c + 1ll * c * rhs.b) % P;
		res.b2 = (1ll * b2 * rhs.c + 1ll * c * rhs.b2 + 2ll * b * rhs.b) % P;
		res.rb = (1ll * rb * rhs.c + 1ll * c * rhs.rb + 1ll * r * rhs.b + 1ll * b * rhs.r) % P;
		res.s = (1ll * s * rhs.c + 1ll * c * rhs.s + 2ll * rb * rhs.b + 2ll * b * rhs.rb + 1ll * r * rhs.b2 + 1ll * b2 * rhs.r) % P;
		return res;
	}

	state operator+(const state &rhs) const {
		state res;
		res.c = (c + rhs.c) % P;
		res.r = (r + rhs.r) % P;
		res.b = (b + rhs.b) % P;
		res.b2 = (b2 + rhs.b2) % P;
		res.rb = (rb + rhs.rb) % P;
		res.s = (s + rhs.s) % P;
		return res;
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int n, cr, cb;
	std::cin >> n >> cr >> cb;
	std::vector<std::vector<int>> E(n);
	std::vector<int> fa(n, -1);
	int idx = 0, now = -1;
	for (int i = 0; i < 2 * n; ++i) {
		std::string op;
		std::cin >> op;
		if (op == "push") {
			if (now != -1) {
				E[now].push_back(idx);
			}
			fa[idx] = now;
			now = idx++;
		} else {
			now = fa[now];
		}
	}

	std::vector<int> dep(n);
	for (int i = 0; i < n; ++i) {
		if (fa[i] != -1) {
			dep[i] = dep[fa[i]] + 1;
		}
	}
	std::vector<std::vector<state>> f(n);
	for (int u = n - 1; u >= 0; --u) {
		f[u].resize(dep[u] + 1);
		for (int i = 0; i <= dep[u]; ++i) {
			if (i + 1 <= cr && dep[u] - i <= cb) {
				state tmp(1);
				tmp = tmp.add_r();
				for (int v : E[u]) {
					tmp = tmp * f[v][i + 1];
				}
				f[u][i] = f[u][i] + tmp;
			}
			if (i <= cr && dep[u] - i + 1 <= cb) {
				state tmp(1);
				tmp = tmp.add_b();
				for (int v : E[u]) {
					tmp = tmp * f[v][i];
				}
				f[u][i] = f[u][i] + tmp;
			}
		}
	}
	state ans(1);
	for (int i = 0; i < n; ++i) {
		if (fa[i] == -1) {
			ans = ans * f[i][0];
		}
	}
	std::cout << ans.s << "\n";
}
