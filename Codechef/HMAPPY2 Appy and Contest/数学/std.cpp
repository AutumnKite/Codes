#include <cstdio>
int T;
long long n, a, b, k, l, s;
long long gcd(long long a, long long b){
	return b ? gcd(b, a % b) : a;
}
long long lcm(long long a, long long b){
	return a / gcd(a, b) * b;
}
int main(){
	scanf("%d", &T);
	while (T--){
		scanf("%lld%lld%lld%lld", &n, &a, &b, &k);
		l = lcm(a, b);
		s = n / a - n / l + n / b - n / l;
		if (s >= k) printf("Win\n"); else printf("Lose\n");
	}
}
