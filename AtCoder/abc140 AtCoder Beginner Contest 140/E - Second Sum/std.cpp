#include <cstdio>
#include <algorithm>
#define N 100005
int n, a[N], mx[N][19], l[N], nl[N], r[N], nr[N];
long long ans;
int getl(int x, int v){
	for (register int i = 18; ~i; --i)
		if (x - (1 << i) + 1 > 0 && mx[x - (1 << i) + 1][i] <= v) x -= 1 << i;
	return x;
}
int getr(int x, int v){
	for (register int i = 18; ~i; --i)
		if (x + (1 << i) - 1 <= n && mx[x][i] <= v) x += 1 << i;
	return x;
}
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i), mx[i][0] = a[i];
	for (register int j = 1; j <= 18; ++j)
		for (register int i = 1; i <= n - (1 << j) + 1; ++i)
			mx[i][j] = std :: max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
	for (register int i = 1; i <= n; ++i){
		l[i] = getl(i - 1, a[i]), r[i] = getr(i + 1, a[i]);
		if (l[i] > 0){
			nl[i] = getl(l[i] - 1, a[i]);
			ans += 1ll * (l[i] - nl[i]) * (r[i] - i) * a[i];
		}
		if (r[i] <= n){
			nr[i] = getr(r[i] + 1, a[i]);
			ans += 1ll * (nr[i] - r[i]) * (i - l[i]) * a[i];
		}
	}
	printf("%lld\n", ans);
}