#include <bits/stdc++.h>

const int N = 100005, M = 20, INF = 0x3f3f3f3f;

int n;
std::string str;

bool vis[26];
int cnt, id[26];

int a[N];

int tot[M];
int c[M][1 << M];

int f[1 << M];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> str;
	n = str.size();
	for (int i = 0; i < n; ++i) {
		vis[str[i] - 'a'] = true;
	}
	for (int i = 0; i < 26; ++i) {
		if (vis[i]) {
			id[i] = cnt++;
		}
	}
	for (int i = 0; i < n; ++i) {
		a[i] = id[str[i] - 'a'];
		++tot[a[i]];
	}
	for (int i = 1; i < n; ++i) {
		++c[a[i]][1 << a[i - 1]];
	}
	for (int i = 0; i < cnt; ++i) {
		for (int S = 1; S < (1 << cnt); ++S) {
			c[i][S] = c[i][S & (S - 1)] + c[i][S & -S];
		}
	}

	f[0] = 0;
	for (int S = 1; S < (1 << cnt); ++S) {
		f[S] = INF;
		for (int i = 0; i < cnt; ++i) {
			if (S >> i & 1) {
				f[S] = std::min(f[S], f[S ^ (1 << i)] + tot[i] - c[i][S ^ (1 << i)]);
			}
		}
	}
	std::cout << f[(1 << cnt) - 1] << "\n";
}