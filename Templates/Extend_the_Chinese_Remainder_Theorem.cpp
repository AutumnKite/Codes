#include <cstdio>
#include <cctype>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
long long gcd(long long a, long long b){
	return b ? gcd(b, a % b) : a;
}
long long exgcd(long long a, long long b, long long &x, long long &y){
	if (!b) return x = 1, y = 0, a;
	long long x0, y0, g = exgcd(b, a % b, x0, y0);
	return x = y0, y = x0 - a / b * y0, g;
}
#define N 100005
int n;
long long a[100005], p[100005];
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
	n = read();
	for (register int i = 1; i <= n; ++i) p[i] = read(), a[i] = read();
	for (register int i = 2; i <= n; ++i){
		long long a1 = a[i - 1], a2 = a[i], p1 = p[i - 1], p2 = p[i], g = gcd(p1, p2);
		if ((a2 - a1) % g) return printf("-1\n"), 0;
		p[i] = p1 / g * p2;
		a[i] = (qmul(qmul((a2 - a1) / g % p[i], inv(p1 / g, p2 / g), p[i]), p1, p[i]) + a1) % p[i];
		a[i] = (a[i] + p[i]) % p[i];
	}
	printf("%lld", a[n]);
	// getchar(), getchar();
}
