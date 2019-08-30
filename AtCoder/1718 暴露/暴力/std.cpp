#include <cstdio>
#include <algorithm>
int n, a[105], m, Sum, sum[105], num[105];
bool know[105][105];
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i)
		scanf("%d", a + i), know[i][i] = 1, Sum += a[i];
	for (register int i = 1; i <= n; ++i) sum[i] = Sum - a[i], num[i] = n - 1;
	scanf("%d", &m);
	for (register int i = 1, opt, x, y; i <= m; ++i){
		scanf("%d%d%d", &opt, &x, &y);
		if (opt == 0) know[x][y] = 1, sum[x] -= a[y], --num[x];
		else if (know[x][y]) printf("%d %d\n", a[y], a[y]);
		else printf("%d %d\n", std :: max(0, sum[x] - (num[x] - 1) * 100), std :: min(100, sum[x]));
	}
}

