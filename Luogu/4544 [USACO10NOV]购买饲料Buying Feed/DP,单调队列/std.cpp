#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = !f;
	for (; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch ^ '0');
	return f ? x : -x;
}
#define INF 0x3f3f3f3f3f3f3f3fll
int n, k, e, h, t;
std :: pair<long long, int> Q[10005];
long long dp[2][10005];
struct node{
	int x, f, c;
	bool operator < (const node &rhs) const {
		return x < rhs.x;
	}
}a[505];
long long val(int i, int j){
	return dp[i & 1 ^ 1][j] + 1ll * j * j * (a[i].x - a[i - 1].x) - 1ll * j * a[i].c;
}
int main(){
	k = read(), e = read(), n = read();
	for (register int i = 1; i <= n; ++i)
		a[i].x = read(), a[i].f = read(), a[i].c = read();
	std :: sort(a + 1, a + 1 + n);
	a[++n] = (node){e, 0, 0};
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = 0;
	for (register int i = 1; i <= n; ++i){
		h = 1, t = 0;
		for (register int j = 0; j <= k; ++j){
			if (dp[i & 1 ^ 1][j] < INF){
				std :: pair<long long, int> v = std :: make_pair(val(i, j), j);
				while (h <= t && v <= Q[t]) --t;
				Q[++t] = v;
			}
			if (Q[h].second < j - a[i].f) ++h;
			dp[i & 1][j] = h > t ? INF : Q[h].first + 1ll * j * a[i].c;
		}
	}
	printf("%lld\n", dp[n & 1][k]);
}