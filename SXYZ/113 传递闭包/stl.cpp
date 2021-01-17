#include <bits/stdc++.h>

const int N = 8000, B = 13;

int n;
char tmp[N / 4 + 2];
std::bitset<N> E[N];
unsigned w[N];

int idx, dfn[N], low[N];
int top, sta[N];
bool vis[N];
int cnt, col[N];

void tarjan(int u) {
	dfn[u] = low[u] = idx++;
	sta[top++] = u, vis[u] = true;
	for (int v = 0; v < n; ++v) {
		if (E[u][v]) {
			if (dfn[v] == -1) {
				tarjan(v);
				low[u] = std::min(low[u], low[v]);
			} else if (vis[v]) {
				low[u] = std::min(low[u], dfn[v]);
			}
		}
	}
	if (dfn[u] == low[u]) {
		sta[top] = -1;
		while (sta[top] != u) {
			--top;
			col[sta[top]] = cnt;
			vis[sta[top]] = false;
		}
		++cnt;
	}
}

std::bitset<N> f[N], st[1 << B];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::cin >> tmp;
		int len = (n - 1) / 4 + 1;
		for (int j = 0; j < len; ++j) {
			int v = isdigit(tmp[j]) ? tmp[j] - '0' : tmp[j] - 'A' + 10;
			for (int k = 0; k < 4 && j * 4 + k < n; ++k) {
				E[i][j * 4 + k] = v >> k & 1;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		std::cin >> w[i];
	}

	for (int i = 0; i < n; ++i) {
		dfn[i] = -1;
	}
	for (int i = 0; i < n; ++i) {
		if (dfn[i] == -1) {
			tarjan(i);
		}
	}

	for (int i = 0; i < cnt; ++i) {
		f[i].set(i);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (E[i][j]) {
				f[col[i]].set(col[j]);
			}
		}
	}

	for (int i = 0; i < cnt; ++i) {
		for (int j = i / B * B; j < i; ++j) {
			if (f[i][j]) {
				f[i] |= f[j];
			}
		}
		if (i + 1 < cnt && (i + 1) % B == 0) {
			int s = i - B + 1;
			for (int j = 0; j < B; ++j) {
				st[1 << j] = f[s + j];
			}
			for (int S = 1; S < (1 << B); ++S) {
				if (S & (S - 1)) {
					st[S] = st[S & (S - 1)];
					st[S] |= st[S & -S];
				}
			}
			for (int j = i + 1; j < cnt; ++j) {
				int mask = 0;
				for (int k = 0; k < B; ++k) {
					if (f[j][s + k]) {
						mask |= 1 << k;
					}
				}
				f[j] |= st[mask];
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		unsigned ans = 0;
		for (int j = 0; j < n; ++j) {
			if (col[i] >= col[j] && f[col[i]][col[j]]) {
				ans ^= w[j];
			}
		}
		std::cout << ans << "\n";
	}
}
