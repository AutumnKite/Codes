#include <cstdio>
#include <cstring>
#include <algorithm>
int n, m, x[100005];
long long A, B, ans;
long long get(int n, int x){
	if (x > n) return 0;
	int m = n / x - 1;
	return ((A + A - (m - 1) * B) * m >> 1) * x + (A - m * B) * (n % x);
}
long long solve(int n){
	int l = 1, r = n, ans = 0;
	while (l <= r){
		int md = (l + r) >> 1;
		if (get(n, md) >= get(n, md + 1)) ans = md, r = md - 1;
		else l = md + 1;
	}
	return get(n, ans);
}
int main(){
	scanf("%d%lld%lld%d", &n, &A, &B, &m), x[m + 1] = n + 1;
	for (register int i = 1; i <= m; ++i) scanf("%d", x + i);
	for (register int i = 0; i <= m; ++i) ans += solve(x[i + 1] - x[i]);
	printf("%lld\n", ans);
}