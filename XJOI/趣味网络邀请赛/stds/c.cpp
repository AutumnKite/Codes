#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2000;
const ll inf = 1e14;
int n, m;
int a[maxn + 10];
int pre[maxn + 10], nxt[maxn + 10];
ll sum[maxn + 10], f[maxn + 10][2];
ll g[maxn + 10];

ll solve(int l, int r) {
	if (r <= a[1]) return 0;
	int pl = nxt[l], pr = pre[r];
	if (pl > pr) return inf;
	ll ans = sum[pr] - sum[pl];
	ans += f[l][1]; ans += f[r][0];
	return ans;
}

ll calc(int l, int r) {
	if (r <= a[1]) return 0;
	ll ans = inf;
	for (int i = 1; i <= l - 1; ++i)
		ans = min(ans, solve(l - i, r - i) + g[i] * (r - l + 1));
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		memset(a, 0, sizeof a);
		memset(pre, 0, sizeof pre);
		memset(nxt, 0, sizeof nxt);
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		memset(sum, 0, sizeof sum);
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		for (int i = 1; i <= n; ++i)
			for (int j = a[i - 1] + 1; j <= a[i]; ++j) {
				pre[j] = i - 1; nxt[j] = i;
			}
		for (int i = 1; i <= a[n]; ++i) g[i] = inf;
		for (int i = 1; i <= m; ++i) {
			int v, c; scanf("%d%d", &v, &c);
			for (int j = c; j <= a[n]; ++j)
				g[j] = min(g[j], g[j - c] + v);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = a[i - 1] + 1; j <= a[i]; ++j)
				f[j][0] = calc(a[i - 1] + 1, j);
			for (int j = a[i - 1] + 1; j <= a[i]; ++j)
				f[j][1] = calc(j, a[i]);
			sum[i] = sum[i - 1] + f[a[i]][0];
		}
		if (sum[n] >= inf) printf("-1\n");
		else printf("%lld\n", sum[n]);
	}
}
