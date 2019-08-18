#include <cstdio>
int n;
long long x, a[70], ans;
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i){
		scanf("%lld", &x);
		for (register int j = 60; ~j; --j)
			if (x >> j & 1)
				if (!a[j]){ a[j] = x; break; }
				else x ^= a[j];
	}
	ans = 0;
	for (register int j = 60; ~j; --j)
		if ((ans ^ a[j]) > ans) ans ^= a[j];
	printf("%lld\n", ans);
}
