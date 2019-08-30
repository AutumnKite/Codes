#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 100005
int n, m, k, a[N], h, t, Q[N];
long long sum[N], mx[N];
void push(int x){
	while (h <= t && sum[Q[t]] <= sum[x]) --t;
	Q[++t] = x;
}
namespace Subtask1{
	int dp[N];
	void upd(int i, int j){
		if (i > n + 1) i = n + 1;
		dp[i] = std :: min(dp[i], j);
	}
	bool check(long long x){
		for (register int i = 1; i <= n + 1; ++i) dp[i] = 1e9;
		dp[1] = 0;
		for (register int i = 1; i <= n; ++i){
			long long Mx = 0;
			for (register int j = 0; j < k && i + j <= n; ++j){
				if (Mx <= x && mx[i + j] <= x) upd(i + j + k, dp[i] + 1);
				Mx = std :: max(Mx, sum[i + j]);
			}
			// if (x == 0) printf("%d %lld\n", i, Mx);
			if (Mx <= x) upd(i + k, dp[i]);
		}
		return dp[n + 1] <= m;
	}
	void Main(){
		long long l = 0, r = 1e14, md, ans;
		while (l <= r) if (check(md = (l + r) >> 1)) ans = md, r = md - 1; else l = md + 1;
		printf("%lld\n", ans);
	}
}
namespace Subtask2{
	long long dp[2][N];
	void Main(){
		long long Mx = 0;
		for (register int i = 1; i <= n; ++i){
			if (i > k) Mx = std :: max(Mx, sum[i - 1]);
			dp[1][i] = std :: max(Mx, mx[i]);
		}
		for (register int i = 2; i <= m; ++i){
			int t = i & 1;
			long long Mx = 0;
			for (register int j = 1; j <= n; ++j){
				if (j > k) Mx = std :: max(Mx, sum[j - 1]);
				if (j > k) Mx = std :: min(Mx, dp[!t][j - k]);
				dp[t][j] = std :: max(Mx, mx[j]);
			}
		}
		long long ans = 0x3f3f3f3f3f3f3f3fll;
		Mx = 0;
		for (register int i = n; i; --i){
			if (i + k <= n) Mx = std :: max(Mx, sum[i + k]);
			ans = std :: min(ans, std :: max(dp[m & 1][i], Mx));
		}
		printf("%lld\n", ans);
	}
}
int main(){
	scanf("%d%d%d", &n, &m, &k);
	m = std :: min(m, n / k + 1);
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	for (register int i = 1; i <= n; ++i)
		sum[i] = sum[i - 1] + a[i] - (i > k ? a[i - k] : 0);
	h = 1, t = 1, Q[t] = k;
	for (register int i = 1; i <= n; i + k <= n ? push(i + k) : void(0), ++i){
		if (Q[h] < i) ++h;
		mx[i] = sum[Q[h]] - a[i];
	}
	if (m <= 2005) return Subtask2 :: Main(), 0;
	if (k <= 55) return Subtask1 :: Main(), 0;
}
