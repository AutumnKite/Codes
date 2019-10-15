#include <cstdio>
int n, m;
long long ans;
long long C3(int x){ return 1ll * x * (x - 1) * (x - 2) / 6; }
int gcd(int a, int b){ return b ? gcd(b, a % b) : a; }
int main(){
	scanf("%d%d", &n, &m);
	ans = C3((n + 1) * (m + 1));
	for (register int i = 0; i <= n; ++i)
		for (register int j = 0; j <= m; ++j)
			ans -= 1ll * ((i > 0) + (j > 0)) * (n - i + 1) * (m - j + 1) * (gcd(i, j) - 1);
	printf("%lld\n", ans);
}