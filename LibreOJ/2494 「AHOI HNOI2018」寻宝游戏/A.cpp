#include <bits/stdc++.h>

const int P = 1000000007;

int n, m, q;
char a[1005][5005];

int id[5005], nid[5005];

int res[5005];

char qry[5005];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	
	std::cin >> n >> m >> q;
	for (int i = 0; i < n; ++i) {
		std::cin >> a[i];
	}

	for (int i = 0; i < m; ++i) {
		id[i] = i;
	}
	for (int i = 0; i < n; ++i) {
		int cnt = 0;
		for (int j = 0; j < m; ++j) {
			if (a[i][id[j]] == '0') {
				nid[cnt++] = id[j];
			}
		}
		for (int j = 0; j < m; ++j) {
			if (a[i][id[j]] == '1') {
				nid[cnt++] = id[j];
			}
		}
		for (int j = 0; j < m; ++j) {
			id[j] = nid[j];
		}
	}

	for (int j = 0; j < m; ++j) {
		res[j] = 0;
		for (int i = n - 1; i >= 0; --i) {
			res[j] = (res[j] * 2 + a[i][j] - '0') % P;
		}
	}
	id[m] = m;
	res[m] = 1;
	for (int i = 0; i < n; ++i) {
		res[m] = 2 * res[m] % P;
	}

	while (q--) {
		std::cin >> qry;
		int l = -1;
		for (int i = 0; i < m; ++i) {
			if (qry[id[i]] == '0') {
				l = i;
			}
		}
		int r = m;
		for (int i = m - 1; i >= 0; --i) {
			if (qry[id[i]] == '1') {
				r = i;
			}
		}
		if (l == -1) {
			std::cout << res[id[r]] << "\n";
		} else {
			if (l >= r) {
				std::cout << 0 << "\n";
			} else {
				std::cout << (res[id[r]] + P - res[id[l]]) % P << "\n";
			}
		}
	}
}