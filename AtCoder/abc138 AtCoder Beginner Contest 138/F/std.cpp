#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f ^= 1;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
#define P 1000000007
long long l, r;
int dp[65][2][2], ans; // 0 >= l 1 < l / 0 <= r 1 > r
void upd(int &x, int y){
	(x += y) >= P ? x -= P : 0;
}
int main(){
	scanf("%lld%lld", &l, &r);
	dp[0][0][0] = 1;
	for (register int i = 0; i <= 59; ++i){
		// 00
		upd(dp[i + 1][l >> i & 1][0], dp[i][0][0]);
		upd(dp[i + 1][l >> i & 1][!(r >> i & 1)], dp[i][0][1]);
		upd(dp[i + 1][1][0], dp[i][1][0]);
		upd(dp[i + 1][1][!(r >> i & 1)], dp[i][1][1]);
		// 11
		upd(dp[i + 1][0][!(r >> i & 1)], dp[i][0][0]);
		upd(dp[i + 1][l >> i & 1][!(r >> i & 1)], dp[i][1][0]);
		upd(dp[i + 1][0][1], dp[i][0][1]);
		upd(dp[i + 1][l >> i & 1][1], dp[i][1][1]);
		// 01
		upd(dp[i + 1][l >> i & 1][!(r >> i & 1)], dp[i][0][0]);
		upd(dp[i + 1][l >> i & 1][1], dp[i][0][1]);
		upd(dp[i + 1][1][!(r >> i & 1)], dp[i][1][0]);
		upd(dp[i + 1][1][1], dp[i][1][1]);
	}
	int kl = 60, kr = 60;
	while (!(l >> kl & 1)) --kl;
	while (!(r >> kr & 1)) --kr;
	if (kl == kr) ans = dp[kl][0][0];
	else{
		upd(ans, dp[kr][0][0]), upd(ans, dp[kr][1][0]);
		upd(ans, dp[kl][0][0]), upd(ans, dp[kl][0][1]);
		for (register int i = kr - 1; i > kl; --i)
			upd(ans, dp[i][0][0]), upd(ans, dp[i][0][1]), upd(ans, dp[i][1][0]), upd(ans, dp[i][1][1]);
	}
	printf("%d\n", ans);
}
