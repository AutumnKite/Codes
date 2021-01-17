#include <bits/stdc++.h>

const int N = 8000, B = 8;

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

struct Bitset {
	static const int N = ::N / 64 + 1;

	int sz;
	unsigned long long bit[N];

	void resize(int _sz) {
		sz = (_sz + 63) >> 6;
	}

	void operator|=(const Bitset &a) {
		sz = std::max(sz, a.sz);
		for (int i = 0; i < a.sz; ++i) {
			bit[i] |= a.bit[i];
		}
	}

	void set(int x) {
		bit[x >> 6] |= 1ull << (x & 63);
	}

	void operator=(const Bitset &a) {
		sz = a.sz;
		for (int i = 0; i < sz; ++i) {
			bit[i] = a.bit[i];
		}
	}

	bool get(int x) {
		return bit[x >> 6] >> (x & 63) & 1;
	}
} f[N], st[1 << B];

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
		f[i].resize(i + 1);
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
			if (f[i].get(j)) {
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
					if (f[j].get(s + k)) {
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
			if (col[i] >= col[j] && f[col[i]].get(col[j])) {
				ans ^= w[j];
			}
		}
		std::cout << ans << "\n";
	}
}
