#include <bits/stdc++.h>

template <class Tp>
class Bigraph {
	const Tp INF = std::numeric_limits<Tp>::max();

	int n;
	std::vector<std::vector<Tp>> E;
	std::vector<Tp> a, b;
	std::vector<int> p;

	void bfs(int x) {
		std::vector<bool> vis(n + 1, false);
		std::vector<Tp> d(n + 1, INF);
		std::vector<int> pre(n + 1, -1);
		p[0] = x;
		int u = 0, v = 0;
		while (p[v]) {
			u = p[v];
			vis[v] = true;
			Tp c = INF;
			int nxt = 0;
			for (int i = 1; i <= n; ++i) {
				if (!vis[i]) {
					Tp val = a[u] + b[i] - E[u - 1][i - 1];
					if (val < d[i]) {
						d[i] = val;
						pre[i] = v;
					}
					if (d[i] < c) {
						c = d[i];
						nxt = i;
					}
				}
			}
			for (int i = 0; i <= n; ++i) {
				if (vis[i]) {
					a[p[i]] -= c;
					b[i] += c;
				} else {
					d[i] -= c;
				}
			}
			v = nxt;
		}
		while (v) {
			p[v] = p[pre[v]];
			v = pre[v];
		}
	}

public:
	Bigraph(int _n, std::vector<std::vector<Tp>> _E) : n(_n), E(_E), a(n + 1), b(n + 1), p(n + 1) {}

	template <class Func>
	Bigraph(int _n, Func f) : n(_n), E(n, std::vector<int>(n, 0)), a(n + 1), b(n + 1), p(n + 1) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				E[i][j] = f(i, j);
			}
		}
	}

	std::vector<int> match() {
		for (int i = 1; i <= n; ++i) {
			a[i] = *std::max_element(E[i - 1].begin(), E[i - 1].end());
			b[i] = 0;
			p[i] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			bfs(i);
		}
		std::vector<int> res(n);
		for (int i = 1; i <= n; ++i) {
			res[i - 1] = p[i] - 1;
		}
		return res;
	}
};

const int N = 75, INF = 0x3f3f3f3f;

int n;
int a[N][N];
int b[N][N];
int ans;

int getX(const std::vector<int> &p) {
	int res = 0;
	for (int i = 0; i < n; ++i) {
		res += a[p[i]][i];
	}
	return res;
}

int getY(const std::vector<int> &p) {
	int res = 0;
	for (int i = 0; i < n; ++i) {
		res += b[p[i]][i];
	}
	return res;
}

void solve(const std::vector<int> &A, const std::vector<int> &B) {
	int Ax = getX(A), Ay = getY(A);
	int Bx = getX(B), By = getY(B);
	std::vector<int> C(Bigraph<int>(n, [&](int x, int y) {
		return (Ax - Bx) * b[x][y] - (Ay - By) * a[x][y];
	}).match());
	int Cx = getX(C), Cy = getY(C);
	if ((Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax) >= 0) {
		return;
	}
	ans = std::min(ans, Cx * Cy);
	solve(A, C), solve(C, B);
}

void solve() {
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cin >> a[i][j];
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cin >> b[i][j];
		}
	}

	std::vector<int> A(Bigraph<int>(n, [&](int x, int y) {
		return -a[x][y];
	}).match());
	std::vector<int> B(Bigraph<int>(n, [&](int x, int y) {
		return -b[x][y];
	}).match());
	ans = std::min(getX(A) * getY(A), getX(B) * getY(B));
	solve(A, B);
	std::cout << ans << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int T = 1;
	std::cin >> T;
	while (T--) {
		solve();
	}
}