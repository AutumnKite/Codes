#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
int m, n, a[200005];
int main() {
	scanf("%d%d", &m, &n);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	int ans = 0;
	for (register int i = 1; i < n; ++i)
		ans = std::max(ans, a[i + 1] - a[i]);
	ans = std::max(ans, a[1] + m - a[n]);
	printf("%d\n", m - ans);
}
