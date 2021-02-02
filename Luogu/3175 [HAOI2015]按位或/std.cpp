#include <bits/stdc++.h>

const int N = 20;

int n;
double p[1 << N];
int bitcnt[1 << N];

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	std::cout.setf(std::ios::fixed);
	std::cout.precision(12);

	std::cin >> n;
	for (int S = 0; S < (1 << n); ++S) {
		std::cin >> p[S];
	}

	for (int i = 0; i < n; ++i) {
		for (int S = 0; S < (1 << n); ++S) {
			if (S >> i & 1) {
				p[S] += p[S ^ (1 << i)];
			}
		}
	}

	int all = (1 << n) - 1;
	double ans = 0;
	bitcnt[0] = 0;
	for (int S = 1; S < (1 << n); ++S) {
		bitcnt[S] = bitcnt[S >> 1] + (S & 1);
		if (fabs(1 - p[all ^ S]) < 1e-6) {
			std::cout << "INF\n";
			return 0;
		}
		ans += (bitcnt[S] & 1 ? 1 : -1) * (1 / (1 - p[all ^ S]));
	}
	std::cout << ans << "\n";
}
