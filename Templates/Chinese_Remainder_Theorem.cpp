#include <cstdio>
long long exgcd(long long a, long long b, long long &x, long long &y){
	if (!b) return x = 1, y = 0, a;
	long long x0, y0, g = exgcd(b, a % b, x0, y0);
	return x = y0, y = x0 - a / b * y0, g;
}
int n, a[15], p[15];
long long inv(long long a, long long p){
	long long x, y, g = exgcd(a, p, x, y);
	if (g != 1) return -1;
	return (x % p + p) % p;
}
long long qmul(long long a, long long b, long long p){
	long long s = 0;
	for (a %= p, b %= p; b; b >>= 1, a = (a + a) % p) b & 1 ? s = (s + a) % p : 0;
	return s; 
}
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1; i <= n; ++i) scanf("%d", p + i);
	for (register int i = 1; i <= n; ++i) a[i] = (a[i] % p[i] + p[i]) % p[i];
	long long m = 1, ans = 0;
	for (register int i = 1; i <= n; ++i) m = m * p[i];
	for (register int i = 1; i <= n; ++i){
		long long d = m / p[i], d_ = inv(d, p[i]);
		(ans += qmul(qmul(d, d_, m), a[i], m)) %= m;
	}
	printf("%lld", ans);
}
