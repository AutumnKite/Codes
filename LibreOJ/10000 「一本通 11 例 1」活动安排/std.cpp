#include <cstdio>
#include <algorithm>
int n, dp[1005];
struct node{
	int l, r;
	bool operator < (const node &b) const {
		return l < b.l || l == b.l && r < b.r;
	}
}a[1005];
int main(){
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) scanf("%d%d", &a[i].l, &a[i].r);
	std :: sort(a + 1, a + 1 + n);
	for (register int i = 1; i <= n; ++i)
		for (register int j = 0; j <= i; ++j)
			if (a[j].r <= a[i].l) dp[i] = std :: max(dp[i], dp[j] + 1);
	int ans = 0;
	for (register int i = 1; i <= n; ++i) ans = std :: max(ans, dp[i]);
	printf("%d", ans);
}