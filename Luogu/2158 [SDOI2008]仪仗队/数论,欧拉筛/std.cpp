#include <cstdio>
int n, cnt, p[40005], phi[40005];
long long sum[40005];
bool vis[40005];
int main(){
	scanf("%d", &n), --n;
	if (!n) return printf("0"), 0;
	vis[1] = 1, phi[1] = sum[1] = 1;
	for (register int i = 2; i <= n; ++i){
		if (!vis[i]) p[++cnt] = i, phi[i] = i - 1;
		for (register int j = 1; j <= cnt && i * p[j] <= n; ++j){
			vis[i * p[j]] = 1;
			if (i % p[j] == 0){ phi[i * p[j]] = phi[i] * p[j]; break; }
			else phi[i * p[j]] = phi[i] * phi[p[j]];
		}
		sum[i] = sum[i - 1] + phi[i];
	}
	printf("%lld\n", sum[n] * 2 + 1);
}
