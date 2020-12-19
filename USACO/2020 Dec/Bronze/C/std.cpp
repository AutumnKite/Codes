#include <bits/stdc++.h>

const int N = 55, INF = 0x3f3f3f3f;

int n;
char d[N];
int x[N], y[N];
int ans[N], Ans[N];

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; ++i) {
		std::cin >> d[i] >> x[i] >> y[i];
		Ans[i] = INF;
	}
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			ans[i] = Ans[i];
		}
		for (int i = 1; i <= n; ++i) {
			if (d[i] == 'N') {
				for (int j = 1; j <= n; ++j) {
					if (d[j] == 'E') {
						int d1 = x[i] - x[j], d2 = y[j] - y[i];
						if (d1 < 0 || d1 > ans[j] || d2 < 0 || d2 > ans[i] || d1 == d2) {
							continue;
						}
						if (d1 < d2) {
							ans[i] = std::min(ans[i], d2);
						} else {
							ans[j] = std::min(ans[j], d1);
						}
					}
				}
			}
		}
		int id = 0;
		for (int i = 1; i <= n; ++i) {
			if (Ans[i] == INF && (!id || ans[i] < ans[id])) {
				id = i;
			}
		}
		Ans[id] = ans[id];
	}
	for (int i = 1; i <= n; ++i) {
		if (Ans[i] == INF) {
			std::cout << "Infinity\n";
		} else {
			std::cout << Ans[i] << "\n";
		}
	}
}