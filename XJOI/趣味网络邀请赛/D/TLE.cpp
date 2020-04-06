#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#include <cstdio>
#include <ctime>

const int P = 998244353;

long long n;

inline long long count(register long long l, register long long r) {
	if (r - l <= 30) {
		register long long res = 0;
		while (r > l) res += r & -r, --r;
		return res;
	}
	register long long res = r - l, p = 1;
	while (r >>= 1) {
		l >>= 1;
		res += (r - l) * p;
		p <<= 1;
	}
	return res;
}

int main() {
	scanf("%lld", &n);
	int t = clock();
	register long long ans = 0;
	for (register long long i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		ans = (ans + count(i - 1, j) * (n / i)) % P;
	}
	printf("%lld\n", ans);
	fprintf(stderr, "%.10lf\n", 1.0 * (clock() - t) / CLOCKS_PER_SEC);
}
/*
1000000000000000
*/
