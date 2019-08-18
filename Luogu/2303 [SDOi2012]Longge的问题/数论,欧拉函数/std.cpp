#include <cstdio>
long long n, ans;
int main(){
	scanf("%lld", &n), ans = n;
	for (register int i = 2; 1ll * i * i <= n; ++i)
		if (n % i == 0){
			int s = 0;
			while (n % i == 0) n /= i, ++s;
			ans /= i, ans *= s * (i - 1) + i;
		}
	if (n > 1) ans /= n, ans *= n - 1 + n;
	printf("%lld\n", ans);
}
//http://www.cnblogs.com/PinkRabbit/p/8278728.html