#include <cstdio>
long long fac[21], su[21][21], ans;
int T, n, k;
int main(){
	fac[0] = 1;
	for (register int i = 1; i <= 20; ++i) fac[i] = fac[i - 1] * i;
	su[0][0] = 1;
	for (register int i = 1; i <= 20; ++i)
		for (register int j = 1; j <= i; ++j)
			su[i][j] = su[i - 1][j - 1] + (i - 1) * su[i - 1][j];
	scanf("%d", &T);
	while (T--){
		scanf("%d%d", &n, &k);
		ans = 0;
		for (register int i = 1; i <= k; ++i) ans += su[n][i] - su[n - 1][i - 1];
		printf("%.4lf\n", 1.0 * ans / fac[n]);
	}
}