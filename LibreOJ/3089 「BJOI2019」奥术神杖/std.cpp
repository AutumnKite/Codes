#include <bits/stdc++.h>

const int N = 1505;

int n, m;
char a[N], b[N];

struct AC_Automaton {
	int cnt, rt;
	int trans[N][10];
	int fail[N];

	int c[N];
	double val[N];

	int new_node() {
		++cnt;
		std::fill(trans[cnt], trans[cnt] + 10, 0);
		fail[cnt] = 0;
		val[cnt] = 0;
		c[cnt] = 0;
		return cnt;
	}

	AC_Automaton() : cnt(0) {
		rt = new_node();
	}

	void insert(int n, char *a, double v) {
		int u = rt;
		for (int i = 1; i <= n; ++i) {
			if (!trans[u][a[i] - '0']) {
				trans[u][a[i] - '0'] = new_node();
			}
			u = trans[u][a[i] - '0'];
		}
		val[u] += v;
		++c[u];
	}

	void build() {
		std::vector<int> Q;
		for (int i = 0; i < 10; ++i) {
			if (!trans[rt][i]) {
				trans[rt][i] = rt;
			} else {
				fail[trans[rt][i]] = rt;
				Q.push_back(trans[rt][i]);
			}
		}
		for (int k = 0; k < (int)Q.size(); ++k) {
			int u = Q[k];
			val[u] += val[fail[u]];
			c[u] += c[fail[u]];
			for (int i = 0; i < 10; ++i) {
				int v = trans[u][i];
				if (v) {
					fail[v] = trans[fail[u]][i];
					Q.push_back(v);
				} else {
					trans[u][i] = trans[fail[u]][i];
				}
			}
		}
	}
} T;

double val[N];
double f[N][N];

bool check(double mid) {
	for (int i = 1; i <= T.cnt; ++i) {
		val[i] = T.val[i] - T.c[i] * mid;
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 1; j <= T.cnt; ++j) {
			f[i][j] = -1e100;
		}
	}
	f[0][1] = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i + 1] != '.') {
			for (int j = 1; j <= T.cnt; ++j) {
				int t = T.trans[j][a[i + 1] - '0'];
				if (f[i][j] > f[i + 1][t]) {
					f[i + 1][t] = f[i][j];
				}
			}
		} else {
			for (int j = 1; j <= T.cnt; ++j) {
				for (int k = 0; k < 10; ++k) {
					int t = T.trans[j][k];
					if (f[i][j] > f[i + 1][t]) {
						f[i + 1][t] = f[i][j];
					}
				}
			}
		}
		for (int j = 1; j <= T.cnt; ++j) {
			f[i + 1][j] += val[j];
		}
	}
	for (int j = 1; j <= T.cnt; ++j) {
		if (f[n][j] > 0) {
			return true;
		}
	}
	return false;
}

int g[N][N], pre[N][N];

void get_ans(int k, int st) {
	if (k == 0) {
		return;
	}
	get_ans(k - 1, pre[k][st]);
	std::cout << g[k][st];
}

int main() {
	std::ios_base::sync_with_stdio(false);

	std::cin >> n >> m;
	std::cin >> (a + 1);
	for (int i = 1; i <= m; ++i) {
		int val;
		std::cin >> (b + 1) >> val;
		T.insert(strlen(b + 1), b, log(val));
	}
	T.build();

	double l = 0, r = 30, ans = 0;
	for (int i = 1; i <= 40; ++i) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
			ans = mid;
		} else {
			r = mid;
		}
	}

	for (int i = 1; i <= T.cnt; ++i) {
		val[i] = T.val[i] - T.c[i] * ans;
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 1; j <= T.cnt; ++j) {
			f[i][j] = -1e100;
		}
	}
	f[0][1] = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i + 1] != '.') {
			for (int j = 1; j <= T.cnt; ++j) {
				int t = T.trans[j][a[i + 1] - '0'];
				if (f[i][j] > f[i + 1][t]) {
					f[i + 1][t] = f[i][j];
					g[i + 1][t] = a[i + 1] - '0';
					pre[i + 1][t] = j;
				}
			}
		} else {
			for (int j = 1; j <= T.cnt; ++j) {
				for (int k = 0; k < 10; ++k) {
					int t = T.trans[j][k];
					if (f[i][j] > f[i + 1][t]) {
						f[i + 1][t] = f[i][j];
						g[i + 1][t] = k;
						pre[i + 1][t] = j;
					}
				}
			}
		}
		for (int j = 1; j <= T.cnt; ++j) {
			f[i + 1][j] += val[j];
		}
	}
	for (int j = 1; j <= T.cnt; ++j) {
		if (f[n][j] > 0) {
			get_ans(n, j);
			std::cout << "\n";
			return 0;
		}
	}
}