#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define P 100003
#define N 100005
int n, k, m, a[N], inv[N], dp[N], ans;
std :: vector<int> d[N];
int main(){
	n = read(), k = read();
	for (register int i = 1; i <= n; ++i) a[i] = read();
	for (register int i = 1; i <= n; ++i)
		for (register int j = i; j <= n; j += i)
			d[j].push_back(i);
	for (register int i = n; i; --i)
		if (a[i]){
			++m;
			for (register int j = 0; j < d[i].size(); ++j) a[d[i][j]] ^= 1;
		}
	inv[1] = 1;
	for (register int i = 2; i <= n; ++i) inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	dp[n] = 1;
	for (register int i = n - 1; i; --i)
		if (i > k) dp[i] = (1ll * (n - i) * dp[i + 1] + n) * inv[i] % P;
		else dp[i] = 1;
	for (register int i = 1; i <= m; ++i) ans = (ans + dp[i]) % P;
	for (register int i = 1; i <= n; ++i) ans = 1ll * ans * i % P;
	printf("%d\n", ans);
}