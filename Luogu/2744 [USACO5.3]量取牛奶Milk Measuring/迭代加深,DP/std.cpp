#include <cstdio>
#include <algorithm>
#define N 105
#define M 20005
int n, m, a[N];
int main(){
	scanf("%d%d", &m, &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	std :: sort(a + 1, a + 1 + n);
	n = std :: unique(a + 1, a + 1 + n) - a - 1;
	for (register int d = 1; d <= n; ++d) dfs(1, d);
}