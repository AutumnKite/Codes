#include <bits/stdc++.h>

int lim;

std::set<int> a[1000005];
std::set<int> b[1005];

std::vector<int> da[1000005];
std::vector<int> db[1005];

int ansm, ansn;

void upd(int m, int n) {
	if (m + n < ansm + ansn || (m + n == ansm + ansn && m < ansm)) {
		ansm = m, ansn = n;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int low, t;
	std::string st;
	std::cin >> low >> st >> t;

	lim = 500;
	for (int i = low; i <= lim; ++i) {
		for (int j = i; j <= lim; ++j) {
			a[i * j].insert(i);
			da[i * j].push_back(i);
			b[i + j].insert(i);
			db[i + j].push_back(i);
		}
	}

	int now = st == "Alice" ? 0 : 1;
	while (t--) {
		if (now == 0) {
			for (int i = low * low; i <= lim * lim; ++i) {
				if (a[i].size() == 1) {
					for (int x : da[i]) {
						b[x + i / x].erase(x);
					}
					a[i].clear();
				}
			}
		} else {
			for (int i = low + low; i <= lim + lim; ++i) {
				if (b[i].size() == 1) {
					for (int x : db[i]) {
						a[x * (i - x)].erase(x);
					}
					b[i].clear();
				}
			}
		}
		now ^= 1;
	}

	for (int wcr = 0; wcr < 2; ++wcr) {
		if (now == 0) {
			for (int i = low * low; i <= lim * lim; ++i) {
				if (a[i].size() > 1) {
					for (int x : da[i]) {
						b[x + i / x].erase(x);
					}
					a[i].clear();
				}
			}
		} else {
			for (int i = low + low; i <= lim + lim; ++i) {
				if (b[i].size() > 1) {
					for (int x : db[i]) {
						a[x * (i - x)].erase(x);
					}
					b[i].clear();
				}
			}
		}
		now ^= 1;
	}
	
	ansm = lim + 1, ansn = lim + 1;
	for (int i = low * low; i <= lim * lim; ++i) {
		for (int x : a[i]) {
			upd(x, i / x);
		}
	}
	std::cout << ansm << " " << ansn << "\n";
}