#include <bits/stdc++.h>

int n;
int cnt[60][30];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		double x;
		scanf("%lf", &x);
		long long v = x * 1e9 + 0.5;
		int a = 0, b = 0;
		while (v % 2 == 0) {
			++a;
			v /= 2;
		}
		while (v % 5 == 0) {
			++b;
			v /= 5;
		}
		++cnt[a][b];
	}
	long long ans = 0;
	for (int i = 0; i < 60; ++i) {
		for (int j = 0; j < 30; ++j) {
			for (int k = 0; k < 60; ++k) {
				for (int l = 0; l < 30; ++l) {
					if (i + k >= 18 && j + l >= 18) {
						ans += 1ll * cnt[i][j] * cnt[k][l];
					}
				}
			}
			if (i + i >= 18 && j + j >= 18) {
				ans -= cnt[i][j];
			}
		}
	}
	printf("%lld\n", ans / 2);
}