#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
long long read(){
	register long long x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
long long n, m, k;
std :: pair<int, int> dp[60][2][2][2];
int P;
void add(int v, std :: pair<int, int> &x, std :: pair<int, int> y){
	x.second = (x.second + y.second) % P;
	x.first = (x.first + 1ll * v * y.second + y.first) % P;
}
std :: pair<int, int> DP(int i, int ex, int ey, int ek){
	if (i < 0) return std :: make_pair(0, 1);
	std :: pair<int, int> &ans = dp[i][ex][ey][ek];
	if (~ans.first) return ans;
	ans.first = ans.second = 0;
	int v = (1ll << i) % P;
	if (!ek || !(k >> i & 1))
		add(0, ans, DP(i - 1, ex & !(n >> i & 1), ey & !(m >> i & 1), ek));
	if (!ey || (m >> i & 1))
		add(v, ans, DP(i - 1, ex & !(n >> i & 1), ey, ek & (k >> i & 1)));
	if (!ex || (n >> i & 1))
		add(v, ans, DP(i - 1, ex, ey & !(m >> i & 1), ek & (k >> i & 1)));
	if ((!ek || !(k >> i & 1)) && (!ex || n >> i & 1) && (!ey || m >> i & 1))
		add(0, ans, DP(i - 1, ex, ey, ek));
	return ans;
}
void solve(){
	memset(dp, -1, sizeof dp);
	n = read() - 1, m = read() - 1, k = read(), P = read();
	std :: pair<int, int> res = DP(59, 1, 1, 1);
	int ans = (res.first + P - k % P * res.second % P) % P;
	printf("%d\n", ans);
}
int main(){
	int T = read();
	while (T--) solve();
}