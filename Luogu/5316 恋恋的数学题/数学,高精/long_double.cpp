#include <cstdio>
#include <cmath>
#include <algorithm>
int T, n, m;
long long a[6], b[6], c[6];
long double d[6];
long long gcd(long long a, long long b){
	return b ? gcd(b, a % b) : a;
}
bool check3(){
	long long x;
	if (x = gcd(c[0], c[1]), x == a[0] && b[0] % c[1] == 0 && c[0] / x == b[0] / c[1]) ; else return 0;
	if (x = gcd(c[0], c[2]), x == a[1] && b[1] % c[2] == 0 && c[0] / x == b[1] / c[2]) ; else return 0;
	if (x = gcd(c[1], c[2]), x == a[2] && b[2] % c[2] == 0 && c[1] / x == b[2] / c[2]) ; else return 0;
	return 1;
}
bool check4(){
	long long x;
	if (x = gcd(c[0], c[1]), x == a[0] && b[0] % c[1] == 0 && c[0] / x == b[0] / c[1]) ; else return 0;
	if (x = gcd(c[0], c[2]), x == a[1] && b[1] % c[2] == 0 && c[0] / x == b[1] / c[2]) ; else return 0;
	if (x = gcd(c[0], c[3]), x == a[2] && b[2] % c[3] == 0 && c[0] / x == b[2] / c[3]) ; else return 0;
	if (x = gcd(c[1], c[2]), x == a[3] && b[3] % c[2] == 0 && c[1] / x == b[3] / c[2]) ; else return 0;
	if (x = gcd(c[1], c[3]), x == a[4] && b[4] % c[3] == 0 && c[1] / x == b[4] / c[3]) ; else return 0;
	if (x = gcd(c[2], c[3]), x == a[5] && b[5] % c[3] == 0 && c[2] / x == b[5] / c[3]) ; else return 0;
	return 1;
}
bool solve(){
	for (register int i = 0; i < m; ++i) d[i] = sqrt(a[i]) * sqrt(b[i]);
	long double tmp;
	if (n == 3){
		tmp = d[0] / d[2] * d[1] + 0.5; if (tmp > 1e18) return 0; c[0] = tmp;
		tmp = d[0] / d[1] * d[2] + 0.5; if (tmp > 1e18) return 0; c[1] = tmp;
		tmp = d[1] / d[0] * d[2] + 0.5; if (tmp > 1e18) return 0; c[2] = tmp;
		return check3();
	}
	if (n == 4){
		tmp = d[0] / d[3] * d[1] + 0.5; if (tmp > 1e18) return 0; c[0] = tmp;
		tmp = d[0] / d[1] * d[3] + 0.5; if (tmp > 1e18) return 0; c[1] = tmp;
		tmp = d[1] / d[0] * d[3] + 0.5; if (tmp > 1e18) return 0; c[2] = tmp;
		tmp = d[4] / d[3] * d[5] + 0.5; if (tmp > 1e18) return 0; c[3] = tmp;
		return check4();
	}
}
int main(){
	scanf("%d%d", &T, &n), m = n * (n - 1) >> 1;
	while (T--){
		for (register int i = 0; i < m; ++i) scanf("%lld", a + i);
		for (register int i = 0; i < m; ++i) scanf("%lld", b + i);
		if (n == 2){ printf("%lld %lld\n", a[0], b[0]); continue; }
		bool flag = 0;
		std :: sort(a , a + m);
		while (1){
			std :: sort(b, b + m);
			while (1){
				if (solve()) { flag = 1; break; };
				if (!std :: next_permutation(b, b + m)) break;
			}
			if (flag) break;
			if (!std :: next_permutation(a, a + m)) break;
		}
		for (register int i = 0; i < n; ++i) printf("%lld ", c[i]); putchar('\n');
	}
}
