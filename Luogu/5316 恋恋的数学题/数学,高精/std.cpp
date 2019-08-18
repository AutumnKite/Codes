#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
__int128 read(){
	register __int128 x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int T, n, m;
__int128 a[6], b[6], d[6];
long long c[6];
__int128 gcd(__int128 a, __int128 b){
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
__int128 my_div(__int128 x, __int128 y, __int128 z){
	__int128 g = gcd(x, z);
	x /= g, z /= g;
	g = gcd(y, z), y /= g, z /= g;
	if (z != 1 || 1e36 / x < y) return -1;
	else return x * y;
}
__int128 my_sqrt(__int128 x){
	if (x == -1) return -1;
	__int128 l = 1, r = 1e18, md, ans = 0;
	while (l <= r) if (md = (l + r) >> 1, md * md <= x) ans = md, l = md + 1; else r = md - 1;
	return ans * ans == x ? ans : -1;
}
bool solve(){
	for (register int i = 0; i < m; ++i) d[i] = a[i] * b[i];
	__int128 tmp;
	if (n == 3){
		tmp = my_sqrt(my_div(d[0], d[1], d[2])); if (tmp == -1) return 0; c[0] = tmp;
		tmp = my_sqrt(my_div(d[0], d[2], d[1])); if (tmp == -1) return 0; c[1] = tmp;
		tmp = my_sqrt(my_div(d[1], d[2], d[0])); if (tmp == -1) return 0; c[2] = tmp;
		return check3();
	}
	if (n == 4){
		tmp = my_sqrt(my_div(d[0], d[1], d[3])); if (tmp == -1) return 0; c[0] = tmp;
		tmp = my_sqrt(my_div(d[0], d[3], d[1])); if (tmp == -1) return 0; c[1] = tmp;
		tmp = my_sqrt(my_div(d[1], d[3], d[0])); if (tmp == -1) return 0; c[2] = tmp;
		tmp = my_sqrt(my_div(d[4], d[5], d[3])); if (tmp == -1) return 0; c[3] = tmp;
		return check4();
	}
	return 0;
}
int main(){
	scanf("%d%d", &T, &n), m = n * (n - 1) >> 1;
	while (T--){
		for (register int i = 0; i < m; ++i) a[i] = read();
		for (register int i = 0; i < m; ++i) b[i] = read();
		if (n == 2){ printf("%lld %lld\n", (long long)a[0], (long long)b[0]); continue; }
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
		// printf("%d\n", flag);
		for (register int i = 0; i < n; ++i) printf("%lld ", c[i]); putchar('\n');
	}
}
